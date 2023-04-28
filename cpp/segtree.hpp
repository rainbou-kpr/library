#pragma once

/**
 * @file segtree.hpp
 * @brief セグメント木
 */

#include <functional>
#include <limits>
#include <ostream>
#include <vector>

/**
 * @brief セグメント木のCRTP基底クラス
 * 
 * @tparam S モノイドの型
 * @tparam ActualSegTree 派生クラス
 */
template <typename S, typename ActualSegTree>
class SegTreeBase {
    int n, sz, height;
    std::vector<S> data;
    void update(int k) { data[k] = ActualSegTree::op(data[2 * k], data[2 * k + 1]); }

    class SegTreeReference {
        SegTreeBase& segtree;
        int k;
    public:
        SegTreeReference(SegTreeBase& segtree, int k) : segtree(segtree), k(k) {}
        SegTreeReference& operator=(const S& x) {
            segtree.set(k, x);
            return *this;
        }
        operator S() const { return segtree.get(k); }
    };

public:
    SegTreeBase(int n) : n(n) {
        sz = 1;
        height = 0;
        while (sz < n) {
            sz <<= 1;
            height++;
        }
        data.assign(sz * 2, ActualSegTree::e());
    }
    SegTreeBase(const std::vector<S>& v) : SegTreeBase(v.size()) {
        for (int i = 0; i < n; i++) data[sz + i] = v[i];
        for (int i = sz - 1; i > 0; i--) update(i);
    }

    /**
     * @brief 指定された要素の値を返す
     * 
     * @param k インデックス
     * @return S 値
     */
    S get(int k) const { return data[sz + k]; }
    /**
     * @brief 指定された要素の値を返す
     * 
     * @param k インデックス
     * @return S 値
     */
    S operator[] (int k) const { return get(k); }
    /**
     * @brief 指定された要素への参照を返す
     * 
     * @param k 
     * @return SegTreeReference 要素への参照 代入されるとset()が呼ばれる
     */
    SegTreeReference operator[] (int k) { return SegTreeReference(*this, k); }

    /**
     * @brief 内容を出力する
     * 
     * @tparam CharT 出力ストリームの文字型
     * @tparam Traits 出力ストリームの文字型特性
     * @param os 出力ストリーム
     * @param rhs セグメント木
     * @return std::basic_ostream<CharT, Traits>& 出力ストリーム 
     */
    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const SegTreeBase& rhs) {
        for(int i = 0; i < rhs.n; i++) {
            if(i != 0) os << CharT(' ');
            os << rhs[i];
        }
        return os;
    }

    /**
     * @brief 指定された要素の値をxに更新する
     * 
     * @param k インデックス
     * @param x 新しい値
     */
    void set(int k, const S& x) {
        k += sz;
        data[k] = x;
        for (int i = 1; i <= height; i++) update(k >> i);
    }
    /**
     * @brief 指定された要素の値にxを作用させる
     * 
     * @param k インデックス
     * @param x 作用素
     */
    void apply(int k, const S& x) { set(k, ActualSegTree::op(get(k), x)); }

    /**
     * @brief [l, r)の区間の総積を返す
     * 
     * @param l 半開区間の開始
     * @param r 半開区間の終端
     * @return S 総積
     */
    S prod(int l, int r) const {
        S left_prod = ActualSegTree::e(), right_prod = ActualSegTree::e();
        l += sz;
        r += sz;
        while (l < r) {
            if (l & 1) left_prod = ActualSegTree::op(left_prod, data[l++]);
            if (r & 1) right_prod = ActualSegTree::op(data[--r], right_prod);
            l >>= 1;
            r >>= 1;
        }
        return ActualSegTree::op(left_prod, right_prod);
    }
    /**
     * @brief すべての要素の総積を返す
     * 
     * @return S 総積
     */
    S all_prod() const { return data[1]; }

    /**
     * @brief f(prod([l, r))) = trueとなる最大のrを返す
     * 
     * @tparam F
     * @param l 半開区間の開始
     * @param f 判定関数
     * @return int 最大のr
     */
    template <typename F>
    int max_right(int l, F f) const {
        assert(f(ActualSegTree::e()));
        if (l == n) return n;
        l += sz;
        while (l % 2 == 0) l >>= 1;
        S sum = ActualSegTree::e();
        while(f(ActualSegTree::op(sum, data[l]))) {
            if (__builtin_clz(l) != __builtin_clz(l+1)) return n;
            sum = ActualSegTree::op(sum, data[l]);
            l++;
            while (l % 2 == 0) l >>= 1;
        }
        while (l < sz) {
            if (!f(ActualSegTree::op(sum, data[l * 2]))) l *= 2;
            else {
                sum = ActualSegTree::op(sum, data[l * 2]);
                l = l * 2 + 1;
            }
        }
        return l - sz;
    }
    /**
     * @brief f(prod([l, r))) = trueとなる最小のlを返す
     * 
     * @tparam F
     * @param r 半開区間の終端
     * @param f 判定関数
     * @return int 最小のl
     */
    template <typename F>
    int min_left(int r, F f) const {
        assert(f(ActualSegTree::e()));
        if (r == 0) return 0;
        r += sz - 1;
        while (r % 2 == 1) r >>= 1;
        S sum = ActualSegTree::e();
        while(f(ActualSegTree::op(sum, data[r]))) {
            if (__builtin_clz(r) != __builtin_clz(r-1)) return 0;
            sum = ActualSegTree::op(sum, data[r]);
            r--;
            while (r % 2 == 1) r >>= 1;
        }
        while (r < sz) {
            if (!f(ActualSegTree::op(data[r * 2 + 1], sum))) r = r * 2 + 1;
            else {
                sum = ActualSegTree::op(data[r * 2 + 1], sum);
                r *= 2;
            }
        }
        return r + 1 - sz;
    }
};

/**
 * @brief 積のファンクタが静的な場合のセグメント木の実装
 * 
 * @tparam S モノイドの型
 * @tparam Op 積のファクタ
 * @tparam E 積の単位元を返すファンクタ
 */
template <typename S, typename Op, typename E>
class StaticSegTree : public SegTreeBase<S, StaticSegTree<S, Op, E>> {
    inline static Op operator_object;
    inline static E identity_object;
public:
    static S op(const S& a, const S& b) { return operator_object(a, b); }
    static S e() { return identity_object(); }

    /**
     * @brief デフォルトコンストラクタ
     * 
    */
    StaticSegTree() : SegTreeBase<S, StaticSegTree<S, Op, E>>(0) {}
    /**
     * @brief コンストラクタ
     * 
     * @param n 要素数
     */
    explicit StaticSegTree(int n) : SegTreeBase<S, StaticSegTree<S, Op, E>>(n) {}
    /**
     * @brief コンストラクタ
     * 
     * @param v 初期の要素
     */
    explicit StaticSegTree(const std::vector<S>& v) : SegTreeBase<S, StaticSegTree<S, Op, E>>(v) {}
};

/**
 * @brief 関数オブジェクトを与えることで積を定義するセグメント木の実装
 * ラムダ式が使えるが、std::functionにバインドするため遅い
 * 
 * @tparam S モノイドの型
 * @tparam ID 複数種類の積を使う場合に型を分けるためのID 1種類のみ使う場合は指定不要
 */
template <typename S, int ID=-1>
class SegTree : public SegTreeBase<S, SegTree<S, ID>> {
    inline static std::function<S(const S&, const S&)> operator_object;
    inline static std::function<S()> identity_object;

public:
    /**
     * @brief 積の関数オブジェクトをセットする
     * 
     * @param op 積の関数オブジェクト
     * @param id 単位元を返す関数オブジェクト
     */
    static void set_operator(const std::function<S(const S&, const S&)>& op, const std::function<S()>& id) {
        operator_object = op;
        identity_object = id;
    }
    /**
     * @brief 積の関数オブジェクトをセットする
     * 
     * @param op 積の関数オブジェクト
     * @param e 単位元の値
     */
    static void set_operator(const std::function<S(S, S)>& op, const S& e) {
        operator_object = op;
        identity_object = [&e](){ return e; };
    }
    static S op(const S& a, const S& b) { return operator_object(a, b); }
    static S e() { return identity_object(); }

    /**
     * @brief デフォルトコンストラクタ
     * 
    */
    SegTree() : SegTreeBase<S, SegTree<S, ID>>(0) {}
    /**
     * @brief コンストラクタ
     * 
     * @param n 要素数
     */
    explicit SegTree(int n) : SegTreeBase<S, SegTree<S, ID>>(n) {}
    /**
     * @brief コンストラクタ
     * 
     * @param v 初期の要素
     */
    explicit SegTree(const std::vector<S>& v) : SegTreeBase<S, SegTree<S, ID>>(v) {}
};

namespace segtree {
    template <typename S>
    struct Max {
        const S operator() (const S& a, const S& b) const { return std::max(a, b); }
    };
    template <typename S>
    struct Min {
        const S operator() (const S& a, const S& b) const { return std::min(a, b); }
    };
    template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>
    struct MaxLimit {
        constexpr S operator() () const { return std::numeric_limits<S>::max(); }
    };
    template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>
    struct MinLimit {
        constexpr S operator() () const { return std::numeric_limits<S>::min(); }
    };
    template <typename S>
    struct Zero {
        S operator() () const { return S(0); }
    };
}
/**
 * @brief RangeMaxQuery
 * 
 * @tparam S 型
 */
template <typename S>
using RMaxQ = StaticSegTree<S, segtree::Max<S>, segtree::MinLimit<S>>;
/**
 * @brief RangeMinQuery
 * 
 * @tparam S 型
 */
template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>
using RMinQ = StaticSegTree<S, segtree::Min<S>, segtree::MaxLimit<S>>;
/**
 * @brief RangeSumQuery
 * 
 * @tparam S 型
 */
template <typename S>
using RSumQ = StaticSegTree<S, std::plus<S>, segtree::Zero<S>>;
