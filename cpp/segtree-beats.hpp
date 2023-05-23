#pragma once

/**
 * @file segtree-beats.hpp
 * @brief Segment Tree Beats
 */

#include <cassert>
#include <functional>
#include <limits>
#include <ostream>
#include <tuple>
#include <vector>

/**
 * @brief Segment Tree BeatsのCRTP基底クラス
 * 
 * @tparam S 値モノイドの型
 * @tparam F 作用素モノイドの型
 * @tparam ActualSegTree 派生クラス
 */
template <typename S, typename F, typename ActualSegTreeBeats>
class SegTreeBeatsBase {
    S op(const S& a, const S& b) const { return static_cast<const ActualSegTreeBeats&>(*this).op(a, b); }
    S e() const { return static_cast<const ActualSegTreeBeats&>(*this).e(); }
    std::pair<bool, S> mapping(const F& f, const S& x, int l, int r) const { return static_cast<const ActualSegTreeBeats&>(*this).mapping(f, x, l, r); }
    F composition(const F& f, const F& g) const { return static_cast<const ActualSegTreeBeats&>(*this).composition(f, g); }
    F id() const { return static_cast<const ActualSegTreeBeats&>(*this).id(); }

    int n, sz, height;
    std::vector<S> data;
    std::vector<int> fail;
    std::vector<F> lazy;

    void update(int k) {
        data[k] = op(data[2 * k], data[2 * k + 1]);
        fail[k] = false;
    }
    void apply_node(int k, int h, const F& f) {
        int l = (k << h) & (sz - 1);
        int r = l + (1 << h);
        std::tie(fail[k], data[k]) = mapping(f, data[k], l, r);
        if(k < sz) {
            lazy[k] = composition(f, lazy[k]);
            if(fail[k]) {
                push(k, h);
                update(k);
            }
        }
    }
    void push(int k, int h) {
        apply_node(2 * k, h-1, lazy[k]);
        apply_node(2 * k + 1, h-1, lazy[k]);
        lazy[k] = id();
    }

    class SegTreeBeatsReference {
        SegTreeBeatsBase& segtree;
        int k;
    public:
        SegTreeBeatsReference(SegTreeBeatsBase& segtree, int k) : segtree(segtree), k(k) {}
        SegTreeBeatsReference& operator=(const S& x) {
            segtree.set(k, x);
            return *this;
        }
        operator S() { return segtree.get(k); }
    };

protected:
    void construct_data() {
        sz = 1;
        height = 0;
        while (sz < n) {
            sz <<= 1;
            height++;
        }
        data.assign(sz * 2, e());
        fail.assign(sz * 2, false);
        lazy.assign(sz * 2, id());
    }
    void initialize(const std::vector<S>& v) {
        for (int i = 0; i < n; i++) data[sz + i] = v[i];
        for (int i = sz - 1; i > 0; i--) update(i);
    }

public:
    // Warning: 継承先のコンストラクタでconstruct_data()を必ず呼び出す！
    SegTreeBeatsBase(int n = 0) : n(n) {}

    /**
     * @brief 指定された要素の値を返す
     * 
     * @param k インデックス
     * @return S 値
     */
    S get(int k) {
        k += sz;
        for(int h = height; h > 0; h--) {
            push(k >> h, h);
        }
        return data[k];
    }
    /**
     * @brief 指定された要素への参照を返す
     * 
     * @param k 
     * @return SegTreeReference 要素への参照 代入されるとset()が呼ばれる
     */
    SegTreeBeatsReference operator[] (int k) { return SegTreeBeatsReference(*this, k); }

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
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, SegTreeBeatsBase& rhs) {
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
        for(int h = height; h > 0; h--) {
            push(k >> h, h);
        }
        data[k] = x;
        while(k >>= 1) update(k);
    }

    /**
     * @brief [l, r)の区間の総積を返す
     * 
     * @param l 半開区間の開始
     * @param r 半開区間の終端
     * @return S 総積
     */
    S prod(int l, int r) {
        l += sz; r += sz;
        for(int h = height; h > 0; h--) {
            if(((l >> h) << h) != l) push(l >> h, h);
            if(((r >> h) << h) != r) push(r >> h, h);
        }
        S left_prod = e(), right_prod = e();
        while(l < r) {
            if(l & 1) left_prod = op(left_prod, data[l++]);
            if(r & 1) right_prod = op(data[--r], right_prod);
            l >>= 1; r >>= 1;
        }
        return op(left_prod, right_prod);
    }
    /**
     * @brief すべての要素の総積を返す
     * 
     * @return S 総積
     */
    S all_prod() const { return data[1]; }
    
    /**
     * @brief 指定された要素の値にxを作用させる
     * 
     * @param k インデックス
     * @param x 作用素
     */
    void apply(int k, const F& f) {
        k += sz;
        for(int h = height; h > 0; h--) {
            push(k >> h, h);
        }
        data[k] = mapping(f, data[k]);
        while(k >>= 1) update(k);
    }
    /**
     * @brief [l, r)の区間の値にxを作用させる
     * 
     * @param l 半開区間の開始
     * @param r 半開区間の終端
     * @param f 作用素
     */
    void apply(int l, int r, const F& f) {
        if(l == r) return;
        l += sz; r += sz;
        for(int h = height; h > 0; h--) {
            if(((l >> h) << h) != l) push(l >> h, h);
            if(((r >> h) << h) != r) push(r >> h, h);
        }
        {
            int l2 = l, r2 = r;
            int h = 0;
            while(l < r) {
                if(l & 1) apply_node(l++, h, f);
                if(r & 1) apply_node(--r, h, f);
                l >>= 1; r >>= 1;
                h++;
            }
            l = l2; r = r2;
        }
        for(int h = 1; h <= height; h++) {
            if(((l >> h) << h) != l) update(l >> h);
            if(((r >> h) << h) != r) update((r - 1) >> h);
        }
    }

    /**
     * @brief (r = l or g(prod([l, r))) = true) and (r = n or g(prod([l, r+1))) = false)となるrを返す
     * gが単調なら、g(prod([l, r))) = trueとなる最大のr
     * 
     * @tparam G
     * @param l 半開区間の開始
     * @param g 判定関数 g(e) = true
     * @return int
     */
    template <typename G>
    int max_right(int l, G g) const {
        assert(g(e()));
        if(l == n) return n;
        l += sz;
        for(int h = height; h > 0; h--) {
            push(l >> h, h);
        }
        S sum = e();
        int h = 0;
        while(g(op(sum, data[l]))) {
            if(__builtin_clz(l) != __builtin_clz(l+1)) return n;
            sum = op(sum, data[l]);
            l++;
            while(l % 2 == 0) {
                l >>= 1;
                h++;
            }
        }
        while(l < sz) {
            push(l, h);
            if(!g(op(sum, data[l*2]))) {
                l = l*2;
            } else {
                sum = op(sum, data[l*2]);
                l = l*2+1;
            }
            h--;
        }
        return l - sz;
    }
    /**
     * @brief (l = 0 or g(prod([l, r))) = true) and (l = r or g(prod([l-1, r))) = false)となる最小のlを返す
     * gが単調なら、g(prod([l, r))) = trueとなる最小のl
     * 
     * @tparam G
     * @param r 半開区間の終端
     * @param g 判定関数 g(e) = true
     * @return int
     */
    template <typename G>
    int min_left(int r, G g) const {
        assert(f(e()));
        if (r == 0) return 0;
        r += sz - 1;
        for(int h = height; h > 0; h--) {
            push(r >> h, h);
        }
        int h = 0;
        while(r % 2 == 1) {
            r >>= 1;
            h++;
        }
        S sum = e();
        while(g(op(data[r], sum))) {
            if(__builtin_clz(r) != __builtin_clz(r-1)) return 0;
            sum = op(data[r], sum);
            r--;
            while(r % 2 == 0) {
                r >>= 1;
                h++;
            }
        }
        while(r < sz) {
            push(r, h);
            if(!g(op(data[r*2+1], sum))) {
                r = r*2+1;
            } else {
                sum = op(data[r*2+1], sum);
                r = r*2;
            }
            h--;
        }
        return r - sz + 1;
    }
};

/**
 * @brief ファンクタが静的な場合のSegment Tree Beatsの実装
 * 
 * @tparam S 値モノイドの型
 * @tparam Op 値の積のファンクタ
 * @tparam E 積の単位元を返すファンクタ
 * @tparam F 作用素モノイドの型
 * @tparam Mapping 作用素を適用するファンクタ 引数は(作用素, 値)または(作用素, 値, サイズ)(作用素, 値, 左の子, 右の子) 戻り値は(失敗したか(bool), 値)のstd::pair
 * @tparam Composition 作用素の積のファンクタ
 * @tparam ID 作用素の単位元を返すファンクタ
 */
template <typename S, typename Op, typename E, typename F, typename Mapping, typename Composition, typename ID>
class StaticSegTreeBeats : public SegTreeBeatsBase<S, F, StaticSegTreeBeats<S, Op, E, F, Mapping, Composition, ID>> {
    using BaseType = SegTreeBeatsBase<S, F, StaticSegTreeBeats<S, Op, E, F, Mapping, Composition, ID>>;

    inline static Op operator_object;
    inline static E identity_object;
    inline static Mapping mapping_object;
    inline static Composition lazy_operator_object;
    inline static ID lazy_identity_object;
public:
    S op(const S& a, const S& b) const { return operator_object(a, b); }
    S e() const { return identity_object(); }
    std::pair<bool, S> mapping(const F& f, const S& x, int l, int r) const {
        if constexpr(std::is_invocable_v<Mapping, F, S, int, int>) {
            return mapping_object(f, x, l, r);
        } else if constexpr(std::is_invocable_v<Mapping, F, S, int>) {
            return mapping_object(f, x, r - l);
        } else {
            return mapping_object(f, x);
        }
    }
    F composition(const F& f, const F& g) const {
        return lazy_operator_object(f, g);
    }
    F id() const { return lazy_identity_object(); }

    /**
     * @brief デフォルトコンストラクタ
     * 
    */
    StaticSegTreeBeats() = default;
    /**
     * @brief コンストラクタ
     * 
     * @param n 要素数
     */
    explicit StaticSegTreeBeats(int n) : BaseType(n) {
        this->construct_data();
    }
    /**
     * @brief コンストラクタ
     * 
     * @param v 初期の要素
     */
    explicit StaticSegTreeBeats(const std::vector<S>& v) : StaticSegTreeBeats(v.size()) {
        this->initialize(v);
    }
};

/**
 * @brief コンストラクタで関数オブジェクトを与えることで積を定義するSegment Tree Beatsの実装
 * テンプレート引数を省略することができ、ラムダ式が使える
 * 
 * @tparam S モノイドの型
 * @tparam Op 積の関数オブジェクトの型
 * @tparam F 作用素モノイドの型
 * @tparam Mapping 作用素を適用する関数オブジェクトの型
 * @tparam Composition 作用素の積の関数オブジェクトの型
 */
template <typename S, typename Op, typename F, typename Mapping, typename Composition>
class SegTreeBeats : public SegTreeBeatsBase<S, F, SegTreeBeats<S, Op, F, Mapping, Composition>> {
    using BaseType = SegTreeBeatsBase<S, F, SegTreeBeats<S, Op, F, Mapping, Composition>>;

    Op operator_object;
    S identity;
    Mapping mapping_object;
    Composition lazy_operator_object;
    F lazy_identity;

public:
    S op(const S& a, const S& b) const { return operator_object(a, b); }
    S e() const { return identity; }
    std::pair<bool, S> mapping(const F& f, const S& x, int l, int r) const {
        if constexpr(std::is_invocable_v<Mapping, F, S, int, int>) {
            return mapping_object(f, x, l, r);
        } else if constexpr(std::is_invocable_v<Mapping, F, S, int>) {
            return mapping_object(f, x, r - l);
        } else {
            return mapping_object(f, x);
        }
    }
    F composition(const F& f, const F& g) const {
        return lazy_operator_object(f, g);
    }
    F id() const { return lazy_identity; }

    /**
     * @brief デフォルトコンストラクタ
    */
    SegTreeBeats() = default;
    /**
     * @brief コンストラクタ
     * 
     * @param n 要素数
     * @param op 積の関数オブジェクト
     * @param identity 単位元
     * @param mapping 作用素を適用する関数オブジェクト
     * @param composition 作用素の積の関数オブジェクト
     * @param lazy_identity 作用素の単位元
     */
    explicit SegTreeBeats(int n, Op op, const S& identity, Mapping mapping, Composition composition, const F& lazy_identity)
        : BaseType(n), operator_object(std::move(op)), identity(identity), mapping_object(std::move(mapping)),
        lazy_operator_object(std::move(composition)), lazy_identity(lazy_identity) {
        this->construct_data();
    }
    /**
     * @brief コンストラクタ
     * 
     * @param v 初期の要素
     * @param op 積の関数オブジェクト
     * @param identity 単位元
     * @param mapping 作用素を適用する関数オブジェクト
     * @param composition 作用素の積の関数オブジェクト
     * @param lazy_identity 作用素の単位元
     */
    explicit SegTreeBeats(const std::vector<S>& v, Op op, const S& identity, Mapping mapping, Composition composition, const F& lazy_identity)
        : SegTreeBeats(v.size(), std::move(op), identity, std::move(mapping), std::move(composition), lazy_identity) {
        this->initialize(v);
    }
};
