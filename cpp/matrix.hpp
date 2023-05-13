#pragma once

#include <vector>
#include <string>
#include <algorithm>

/**
 * @brief 行列
 * @tparam T 型 行列(グリッド)の要素となるintやchar
 */
template<class T> struct Matrix {
    std::vector<std::vector<T>> v;
    int n, m;

    /**
     * @brief コンストラクタ
     * @param v 行列(グリッド)の元となる vector<string> や vector<vector<T>>
     * @return Matrix
     */
    template <typename Iterable>
    constexpr Matrix(const std::vector<Iterable>& v_) noexcept : n(v_.size()), m(v_.size() == 0 ? 0 : v_[0].size()) {
        v.resize(n);
        for(int i = 0; i < n; i++) {
            v[i].assign(v_[i].begin(), v_[i].end());
        }
    }

    /**
     * @brief コンストラクタ
     * @param _n 行列(グリッド)の行数
     * @param _m 行列(グリッド)の列数
     * @param _val 行列(グリッド)の要素の初期値
     * @return Matrix
     */
    constexpr Matrix(int _n, int _m, T _val = T()) : v(n, std::vector<T>(m, _val)) {}
    
    constexpr auto begin() noexcept {return v.begin();}
    constexpr auto end() noexcept {return v.end();}

    /**
     * @brief 行列(グリッド)の行数
     * @return size_t
     */
    constexpr size_t size() const {return v.size();}
    std::vector<T>& operator [] (int i) {return v[i];}
    const std::vector<T>& operator [] (int i) const {return v[i];}

    /**
     * @brief 転置
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix transpose() noexcept {
        if(n == 0) return Matrix(v);
        std::vector<std::vector<T>> ret(m);
        for(int i = 0; i < m; i ++) {
            ret[i].resize(n);
            for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];
        }
        return Matrix(ret);
    }

    /**
     * @brief 左右反転
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix rev_lr() noexcept {
        std::vector<std::vector<T>> ret = v;
        for(int i = 0; i < n; i ++) std::reverse(ret[i].begin(), ret[i].end());
        return Matrix(ret);
    }

    /**
     * @brief 上下反転
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix rev_ud() noexcept {
        std::vector<std::vector<T>> ret = v;
        reverse(ret.begin(), ret.end());
        return Matrix(ret);
    }

    /**
     * @brief 時計周りに90度回転
     * @param k 回転する回数
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix rotate(int k) noexcept {
        k %= 4;
        if(k == 0) return *this;
        if(k < 0) k += 4;
        if(k == 2) return this->rev_lr().rev_ud();
        std::vector<std::vector<T>> ret(m);
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
        return Matrix(ret);
    }

    /**
     * @brief (i, j)を((i + dy) mod n, (j + dx) mod m)に移動
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift(int dy, int dx) noexcept {
        std::vector<std::vector<T>> ret = v;
        for(int i = 0, ni = dy; i < n; i ++, ni ++) {
            if(ni >= n) ni = 0;
            for(int j = 0, nj = dx; j < m; j ++, nj ++) {
                if(nj >= m) nj = 0;
                ret[ni][nj] = v[i][j];
            }
        }
        return Matrix(ret);
    }

    /**
     * @brief 左にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_l(int k) noexcept {
        return this->shift(0, -k);
    }

    /**
     * @brief 右にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_r(int k) noexcept {
        return this->shift(0, k);
    }

    /**
     * @brief 上にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_u(int k) noexcept {
        return this->shift(-k, 0);
    }

    /**
     * @brief 下にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_d(int k) noexcept {
        return this->shift(k, 0);
    }

    /**
     * @brief グリッドをvector<string>で返す
     * @return std::vector<std::string>
     */
    [[nodiscard]]
    constexpr std::vector<std::string> vstr() noexcept {
        std::vector<std::string> ret(n);
        for(int i = 0; i < n; i ++) {
            ret[i].assign(v[i].begin(), v[i].end());
        }
        return ret;
    }

    /**
     * @brief グリッドのj列目を返す
     * @param j 返す列番号(0-indexed)
     * @return std::vector<T>
     */
    [[nodiscard]]
    constexpr std::vector<T> col(int j) noexcept {
        std::vector<T> ret(n);
        for(int i = 0; i < n; i ++) {
            ret[i] = v[i][j];
        }
        return ret;
    }

    /**
     * @brief グリッドのi行目をstringで返す
     * @param i 返す行番号(0-indexed)
     * @return std::string
     */
    [[nodiscard]]
    constexpr std::string str(int i) noexcept {
        std::string ret;
        ret.assign(v[i].begin(), v[i].end());
        return ret;
    }
};