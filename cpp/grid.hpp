#pragma once

#include <vector>
#include <algorithm>

/**
 * @brief 幾何学としてのベクトル
 *
 * @tparam T 型 stringまたはvector<N> Nはintやlong longなどの整数型
 */
template<class T> struct Grid {
    std::vector<T> v;
    int n, m;
    /**
     * @brief コンストラクタ
     * @param v グリッドの元となる vector<string> や vector<vector<int>>などの配列
     * @return Grid
     */
    constexpr Grid(std::vector<T> v) noexcept : v(v), n(v.size()) { m = (n ? (int)v[0].size() : 0); }

    /**
     * @brief 転置
     * @return Grid
     */
    constexpr Grid transpose() noexcept {
        if(n == 0) return *this;
        std::vector<T> ret(m);
        for(int i = 0; i < m; i ++) {
            ret[i].resize(n);
            for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];
        }
        return Grid(ret);
    }

    /**
     * @brief 左右反転
     * @return Grid
     */
    constexpr Grid rev_lr() noexcept {
        std::vector<T> ret = v;
        for(int i = 0; i < n; i ++) reverse(ret[i].begin(), ret[i].end());
        return Grid(ret);
    }

    /**
     * @brief 上下反転
     * @return Grid
     */
    constexpr Grid rev_ud() noexcept {
        std::vector<T> ret = v;
        reverse(ret.begin(), ret.end());
        return Grid(ret);
    }

    /**
     * @brief 時計周りに90度回転
     * @return Grid
     */
    constexpr Grid rotate(int k) noexcept {
        k %= 4;
        if(k == 0) return *this;
        if(k < 0) k += 4;
        if(k == 2) return this->rev_lr().rev_ud();
        std::vector<T> ret(m);
        if(k == 1) {
            for(int i = 0; i < m; i ++) {
                ret[i].resize(n);
                for(int j = 0; j < n; j ++) ret[i][j] = v[n - j - 1][i];
            }
        } else {
            for(int i = 0; i < m; i ++) {
                ret[i].resize(n);
                for(int j = 0; j < n; j ++) ret[i][j] = v[j][m - i - 1];
            }
        }
        return Grid(ret);
    }

    /**
     * @brief 割った余りを[0, mod-1]の範囲で求める
     * @param x 割られる数
     * @param mod modをとる数
     * @return int
     */
    constexpr int safe_mod(int x, int mod) noexcept {
        x %= mod;
        if (x < 0) x += mod;
        return x;
    }

    /**
     * @brief (i, j)を((i + dy) mod n, (j + dx) mod m)に移動
     * @return Grid
     */
    constexpr Grid shift(int dy, int dx) noexcept {
        std::vector<T> ret = v;
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                ret[safe_mod(i + dy, n)][safe_mod(j + dx, m)] = v[i][j];
            }
        }
        return Grid(ret);
    }

    /**
     * @brief 左にk回シフト
     * @return Grid
     */
    constexpr Grid shift_l(int k) noexcept {
        return this->shift(0, -k);
    }

    /**
     * @brief 右にk回シフト
     * @return Grid
     */
    constexpr Grid shift_r(int k) noexcept {
        return this->shift(0, k);
    }

    /**
     * @brief 上にk回シフト
     * @return Grid
     */
    constexpr Grid shift_u(int k) noexcept {
        return this->shift(-k, 0);
    }

    /**
     * @brief 下にk回シフト
     * @return Grid
     */
    constexpr Grid shift_d(int k) noexcept {
        return this->shift(k, 0);
    }
};