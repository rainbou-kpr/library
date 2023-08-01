#pragma once

/**
 * @file segtree-2d.hpp
 * @brief 2次元セグメント木
 */

#include <algorithm>
#include <limits>
#include <tuple>
#include <vector>

/**
 * @brief 2次元セグメント木のCRTP基底クラス
 *
 * @tparam S モノイドの型
 * @tparam ActualSegTree 派生クラス
 */
template <typename S, typename ActualSegTree>
class SegTree2DBase {
    S op(S a, S b) const { return static_cast<const ActualSegTree&>(*this).op(a, b); }
    S e() const { return static_cast<const ActualSegTree&>(*this).e(); }

    int h, w, sz_x, sz_y, height_x, height_y;
    std::vector<std::vector<int>> y_indices;
    std::vector<std::vector<S>> data_compressed;

    S get_y(int kx, int ky) {
        ky += sz_y;
        auto it = std::lower_bound(y_indices[kx].begin(), y_indices[kx].end(), ky);
        if(it == y_indices[kx].end() || *it != ky) return e();
        return data_compressed[kx][it - y_indices[kx].begin()];
    }

    S updated_y(int kx, int ky, int child_y_idx, bool child_y_right, const S& child_val) {
        if(!child_y_right && child_y_idx+1 < (int)y_indices[kx].size() && y_indices[kx][child_y_idx+1] == ky*2+1) {
            return op(child_val, data_compressed[kx][child_y_idx+1]);
        }
        if(child_y_right && child_y_idx-1 >= 0 && y_indices[kx][child_y_idx-1] == ky*2) {
            return op(data_compressed[kx][child_y_idx-1], child_val);
        }
        return child_val;
    }

    void update_tree_y(int kx, int ky, const S& val) {
        ky += sz_y;
        int y_idx = std::lower_bound(y_indices[kx].begin(), y_indices[kx].end(), ky) - y_indices[kx].begin();
        S tmp_val = val;
        data_compressed[kx][y_idx] = tmp_val;
        for(int i = 1; i <= height_y; i++) {
            int child_y_idx = y_idx;
            y_idx = std::lower_bound(y_indices[kx].begin(), y_indices[kx].begin() + child_y_idx, ky >> i) - y_indices[kx].begin();
            tmp_val = data_compressed[kx][y_idx] = updated_y(kx, ky >> i, child_y_idx, ky>>(i-1)&1, tmp_val);
        }
    }

    S updated_x(int kx, int ky, bool child_x_right, const S& child_val) {
        if(!child_x_right) {
            return op(child_val, get_y(kx*2+1, ky));
        } else {
            return op(get_y(kx*2, ky), child_val);
        }
    }

    void update_tree_x(int kx, int ky, const S& val) {
        kx += sz_x;
        S tmp_val = val;
        update_tree_y(kx, ky, tmp_val);
        for(int i = 1; i <= height_x; i++) {
            tmp_val = updated_x(kx >> i, ky, kx>>(i-1)&1, tmp_val);
            update_tree_y(kx >> i, ky, tmp_val);
        }
    }

    S prod_y(int kx, int ly, int ry) {
        S left_prod = e(), right_prod = e();
        ly += sz_y; ry += sz_y;
        auto itr = y_indices[kx].end();
        while(ly < ry) {
            if(ry & 1) {
                --ry;
                itr = std::lower_bound(y_indices[kx].begin(), itr, ry);
                right_prod = op(data_compressed[kx][itr - y_indices[kx].begin()], right_prod);
            }
            if(ly & 1) {
                itr = std::lower_bound(y_indices[kx].begin(), itr, ly);
                left_prod = op(left_prod, data_compressed[kx][itr - y_indices[kx].begin()]);
                ++ly;
            }
            ly >>= 1; ry >>= 1;
        }
        return op(left_prod, right_prod);
    }

    S prod_x(int lx, int rx, int ly, int ry) {
        S left_prod = e(), right_prod = e();
        lx += sz_x; rx += sz_x;
        while(lx < rx) {
            if(lx & 1) {
                left_prod = op(left_prod, prod_y(lx++, ly, ry));
            }
            if(rx & 1) {
                right_prod = op(prod_y(--rx, ly, ry), right_prod);
            }
            lx >>= 1; rx >>= 1;
        }
        return op(left_prod, right_prod);
    }

protected:
    void construct_data(const std::vector<std::tuple<int, int>>& set_query_indices, const std::vector<std::tuple<int, int, int, int>>& prod_query_indices) {
        sz_x = 1; height_x = 0;
        while(sz_x < h) { sz_x <<= 1; ++height_x; }
        sz_y = 1; height_y = 0;
        while(sz_y < w) { sz_y <<= 1; ++height_y; }
        data_compressed.resize(sz_x*2);
        y_indices.resize(sz_x*2);

        for(auto [x, y] : set_query_indices) {
            x += sz_x;
            std::vector<int> x_indices_tmp;
            for(int i = 0; i <= height_x; ++i) {
                x_indices_tmp.push_back(x);
                x >>= 1;
            }
            y += sz_y;
            std::vector<int> y_indices_tmp;
            for(int i = 0; i <= height_y; ++i) {
                y_indices_tmp.push_back(y);
                y >>= 1;
            }
            for(int x : x_indices_tmp) {
                for(int y : y_indices_tmp) {
                    y_indices[x].push_back(y);
                }
            }
        }
        for(auto [lx, rx, ly, ry] : prod_query_indices) {
            std::vector<int> x_indices_tmp;
            lx += sz_x; rx += sz_x;
            while(lx < rx) {
                if(lx & 1) x_indices_tmp.push_back(lx++);
                if(rx & 1) x_indices_tmp.push_back(--rx);
                lx >>= 1; rx >>= 1;
            }
            ly += sz_y; ry += sz_y;
            std::vector<int> y_indices_tmp;
            while(ly < ry) {
                if(ly & 1) y_indices_tmp.push_back(ly++);
                if(ry & 1) y_indices_tmp.push_back(--ry);
                ly >>= 1; ry >>= 1;
            }
            for(int x : x_indices_tmp) {
                for(int y : y_indices_tmp) {
                    y_indices[x].push_back(y);
                }
            }
        }

        for(int x = 1; x < sz_x*2; x++) {
            std::sort(y_indices[x].begin(), y_indices[x].end());
            y_indices[x].erase(std::unique(y_indices[x].begin(), y_indices[x].end()), y_indices[x].end());
        }
        for(int i = 1; i < sz_x*2; ++i) {
            data_compressed[i].assign(y_indices[i].size(), e());
        }
    }

public:
    // Warning: 継承先のコンストラクタでconstruct_data()を必ず呼び出す！
    SegTree2DBase(int h = 0, int w = 0) : h(h), w(w) {}

    /**
     * @brief 指定された要素の値を返す
     * @param kx x座標
     * @param ky y座標
     * @return 要素の値
     */
    S get(int kx, int ky) {
        kx += sz_x;
        return get_y(kx, ky);
    }

    /**
     * @brief 指定された要素の値をxに更新する
     * @param kx x座標
     * @param ky y座標
     * @param x 代入する値
     */
    void set(int kx, int ky, const S& x) {
        update_tree_x(kx, ky, x);
    }

    /**
     * @brief 指定された要素の値にxを作用させる
     *
     * @param kx x座標
     * @param ky y座標
     * @param x 作用素
     */
    void apply(int kx, int ky, const S& x) {
        set(kx, ky, op(get(kx, ky), x));
    }

    /**
     * @brief [lx, rx)x[ly, ry)の範囲の要素の総積を返す
     *
     * @param lx x座標の半開区間の開始
     * @param rx x座標の半開区間の終端
     * @param ly y座標の半開区間の開始
     * @param ry y座標の半開区間の終端
     */
    S prod(int lx, int rx, int ly, int ry) {
        return prod_x(lx, rx, ly, ry);
    }
};

/**
 * @brief 積のファンクタが静的な場合の2次元セグメント木の実装
 *
 * @tparam S モノイドの型
 * @tparam Op 積のファンクタ
 * @tparam E 積の単位元を返すファンクタ
 */
template <typename S, typename Op, typename E>
class StaticSegTree2D : public SegTree2DBase<S, StaticSegTree2D<S, Op, E>> {
    using BaseType = SegTree2DBase<S, StaticSegTree2D<S, Op, E>>;

    inline static Op operator_object;
    inline static E identity;
public:
    S op(const S& a, const S& b) const { return operator_object(a, b); }
    S e() const { return identity(); }

    /**
     * @brief デフォルトコンストラクタ
     */
    StaticSegTree2D() = default;

    /**
     * @brief コンストラクタ
     *
     * @param h 高さ(x∈[0,h))となる値
     * @param w 幅(y∈[0,w))となる値
     * @param set_query_indices 要素の更新で指定するx座標とy座標のペアの列
     * @param prod_query_indices 総積のクエリで指定するx座標とy座標のペアの列
     */
    explicit StaticSegTree2D(int h, int w, const std::vector<std::tuple<int, int>>& set_query_indices, const std::vector<std::tuple<int, int, int, int>>& prod_query_indices) : BaseType(h, w) {
        this->construct_data(set_query_indices, prod_query_indices);
    }
};

/**
 * @brief コンストラクタで関数オブジェクトを与えることで積を定義する2次元セグメント木の実装
 * テンプレート引数を省略することができ、ラムダ式が使える
 *
 * @tparam S モノイドの型
 * @tparam Op 積の関数オブジェクトの型
 */
template <typename S, typename Op>
class SegTree2D : public SegTree2DBase<S, SegTree2D<S, Op>> {
    using BaseType = SegTree2DBase<S, SegTree2D<S, Op>>;

    Op operator_object;
    S identity;

public:
    S op(const S& a, const S& b) const { return operator_object(a, b); }
    S e() const { return identity; }

    /**
     * @brief デフォルトコンストラクタ
     */
    SegTree2D() = default;

    /**
     * @brief コンストラクタ
     *
     * @param h 高さ(x∈[0,h))となる値
     * @param w 幅(y∈[0,w))となる値
     * @param set_query_indices 要素の更新で指定するx座標とy座標のペアの列
     * @param prod_query_indices 総積のクエリで指定するx座標とy座標のペアの列
     */
    explicit SegTree2D(int h, int w, const std::vector<std::tuple<int, int>>& set_query_indices, const std::vector<std::tuple<int, int, int, int>>& prod_query_indices, Op op, const S& identity) : BaseType(h, w), operator_object(std::move(op)), identity(identity) {
        this->construct_data(set_query_indices, prod_query_indices);
    }
};

namespace segtree2d {
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
        constexpr S operator() () const { return std::numeric_limits<S>::lowest(); }
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
using RMaxQ2D = StaticSegTree2D<S, segtree2d::Max<S>, segtree2d::MinLimit<S>>;
/**
 * @brief RangeMinQuery
 *
 * @tparam S 型
 */
template <typename S>
using RMinQ2D = StaticSegTree2D<S, segtree2d::Min<S>, segtree2d::MaxLimit<S>>;
/**
 * @brief RangeSumQuery
 *
 * @tparam S 型
 */
template <typename S>
using RSumQ2D = StaticSegTree2D<S, std::plus<S>, segtree2d::Zero<S>>;
