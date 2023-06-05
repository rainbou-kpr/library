#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <valarray>

/**
 * @brief 行列
 * @tparam T 型 行列(グリッド)の要素となるintやchar
 */
template<class T> struct Matrix {
    int n, m;
    std::vector<std::vector<T>> v;

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
    constexpr Matrix(int _n, int _m, T _val = T()) : n(_n), m(_m), v(n, std::vector<T>(m, _val)) {}
    
    constexpr auto begin() noexcept {return v.begin();}
    constexpr auto end() noexcept {return v.end();}

    /**
     * @brief 行列(グリッド)の行数
     * @return size_t
     */
    [[nodiscard]]
    constexpr size_t size() const {return v.size();}

    std::vector<T>& operator [] (int i) {return v[i];}
    const std::vector<T>& operator [] (int i) const {return v[i];}
    constexpr Matrix<T>& operator = (const std::vector<std::vector<T>> &A) noexcept {
        n = A.size();
        m = (n == 0 ? 0 : A[0].size());
        v = A;
        return *this;
    }
    constexpr bool operator == (const Matrix<T> &A) noexcept {
        return this->v == A.v;
    }

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
    /**
     * @brief 保持している行列に行列Bを足す
     * @param B 足す行列
     * @return @c *this
    */
    constexpr Matrix &operator+=(const Matrix &B) {
        if(n == 0) return (*this);
        assert(n == B.size() && m == B[0].size());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
        return (*this);
    }
    /**
     * @brief 保持している行列から行列Bを引く
     * @param B 引く行列
     * @return @c *this
    */
    constexpr Matrix &operator-=(const Matrix &B) {
        if(n == 0) return (*this);
        assert(n == B.size() && m == B[0].size());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
        return (*this);
    }

    /**
     * @brief 保持している行列に行列Bを掛ける
     * @param B 掛ける行列
     * @return @c *this
    */
    constexpr Matrix &operator*=(const Matrix &B) {
        int p = B[0].size();
        Matrix<T> C(n, p);
        for(int i = 0; i < n; i ++) {
            for(int k = 0; k < p; k ++) {
                for(int j = 0; j < m; j ++) {
                    C[i][j] += (*this)[i][k] * B[k][j];
                }
            }
        }
        v.swap(C.v);
        m = p;
        return (*this);
    }

    /**
     * @brief 保持している行列のk乗を求める
     * @param k 指数
     * @return Matrix
    */
    [[nodiscard]]
    constexpr Matrix pow(long long k) {
        Matrix<T> A = *this, B(n, n);
        for(int i = 0; i < n; i ++) B[i][i] = 1;
        while(k > 0) {
            if(k & 1) B *= A;
            A *= A;
            k >>= 1;
        }
        return B;
    }

    [[nodiscard]]
    constexpr Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
    [[nodiscard]]
    constexpr Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
    [[nodiscard]]
    constexpr Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }

    /**
     * @brief 行列Aと列ベクトルBの積
     * @param A Matrix<T>
     * @param B vector<T>
     * @return vector<T> 列ベクトル
    */
    [[nodiscard]]
    constexpr friend std::vector<T> operator*(const Matrix &A, const std::vector<T> &B) {
        std::vector<T> ret(A.n, 0);
        for(int i = 0; i < A.n; i ++) {
            for(int j = 0; j < A.m; j ++) {
                ret[i] += A[i][j] * B[j];
            }
        }
        return ret;
    }

    /**
     * @brief 行ベクトルAと行列Bの積
     * @param A vector<T>
     * @param B Matrix<T>
     * @return vector<T> 行ベクトル
    */
    [[nodiscard]]
    constexpr friend std::vector<T> operator*(const std::vector<T> &A, const Matrix &B) {
        std::vector<T> ret(B.m, 0);
        for(int i = 0; i < B.n; i ++) {
            for(int j = 0; j < B.m; j ++) {
                ret[j] += A[i] * B[i][j];
            }
        }
        return ret;
    }

    /**
     * @brief 行列式
     * @tparam T modint
     * @return T modint
    */
    [[nodiscard]]
    T det() {
        assert(n == m);
        if(n == 0) return 1;
        T ans = 1;
        std::vector A(n, std::valarray(T(0), n));
        for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++) A[i][j] = this->v[i][j];
        for(int i = 0; i < n; i ++) {
            if(A[i][i].value() == 0) {
                for(int j = i + 1; j < n; j ++) if(A[j][i].value()) {
                    std::swap(A[i], A[j]);
                    ans *= -1;
                    break;
                }
                if(A[i][i].value() == 0) return 0;
            }
            ans *= A[i][i];
            A[i] *= A[i][i].inv();
            for(int j = i + 1; j < n; j ++) A[j] -= A[i] * A[j][i];
        }
        return ans;
    }
};