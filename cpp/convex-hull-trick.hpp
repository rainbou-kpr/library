#pragma once

/**
 * @file convex-hull-tric.hpp
 * @brief Convex Hull Trick
 *
 * 一次関数で表される直線または線分の集合を管理し、あるxに対する最小値を求める
 */

#include <limits>
#include <type_traits>
#include <vector>

/**
 * @brief 追加される傾きが単調とは限らない場合のConvex Hull Trick
 *
 * @tparam T 値の型
 */
template <typename T, std::enable_if_t<std::is_scalar_v<T>, std::nullptr_t> = nullptr>
class LiChaoTree {
    int n, sz, height;
    std::vector<T> xs, as, bs;

    void update(T a, T b, int k, int h) {
        int l = (k << h) & (sz - 1);
        int r = l + (1 << h);
        
        while(1) {
            int m = (l + r) >> 1;
            T xl = xs[l], xm = xs[m];
            bool l_update = a*xl + b < as[k]*xl + bs[k];
            bool m_update = a*xm + b < as[k]*xm + bs[k];

            if(m_update) {
                std::swap(as[k], a);
                std::swap(bs[k], b);
            }
            if(h == 0) break;
            if(l_update != m_update) {
                k = k*2;
                r = m;
            } else {
                k = k*2+1;
                l = m;
            }
            h--;
        }
    }

public:
    /**
     * @brief コンストラクタ
     *
     * @param xs 最小値クエリのx座標や線分追加クエリの両端のx座標を先読みしてソートした配列
     */
    LiChaoTree(const std::vector<T>& xs) : n(xs.size()), xs(xs) {
        sz = 1, height = 0;
        while(sz < (int)xs.size()) {
            sz <<= 1;
            height++;
        }
        this->xs.resize(sz, xs.back());
        as.assign(sz*2, 0);
        bs.assign(sz*2, std::numeric_limits<T>::max());
    }

    /**
     * @brief 直線y=ax+bの追加
     *
     * @param a 傾き
     * @param b 切片
     */
    void add_line(T a, T b) {
        update(a, b, 1, height);
    }
    /**
     * @brief 線分y=ax+b , x∈[xs[l],xs[r])の追加
     *
     * @param a 傾き
     * @param b 切片
     * @param l 左端(xsのインデックス)
     * @param r xの上限(xsのインデックス)
     */
    void add_segment(T a, T b, int l, int r) {
        if(l == r) return;
        l += sz, r += sz;
        int h = 0;
        while(l < r) {
            if(l & 1) update(a, b, l++, h);
            if(r & 1) update(a, b, --r, h);
            l >>= 1, r >>= 1, h++;
        }
    }

    /**
     * @brief x=xs[i]における最小値を求める
     *
     * @param x x座標(xsのインデックス)
     * @return T 最小値
     */
    T get_min(int i) const {
        T x = xs[i];
        int k = i + sz;
        T res = as[k]*x + bs[k];
        while(k > 1) {
            k >>= 1;
            T tmp = as[k]*x + bs[k];
            if(tmp < res) res = tmp;
        }
        return res;
    }
};
