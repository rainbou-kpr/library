#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <valarray>
#include <cassert>
#include <type_traits>

namespace matrix {
    template <typename T>
    struct OperatorPropertyDefault {
        constexpr static T zero() { return T(0); }
        constexpr static T add(const T &a, const T &b) { return a + b; }
        constexpr static T neg(const T &a) { return -a; }
        constexpr static T one() { return T(1); }
        constexpr static T mul(const T &a, const T &b) { return a * b; }
        constexpr static T inv(const T &a) { return T(1) / a; }
    };
}

/**
 * @brief 行列
 * @tparam T 型 行列(グリッド)の要素となるintやchar
 * @tparam OperatorProperty 行列の要素の演算を定義する構造体 0,1と+,*なら省略可
 *
 * @note
 * OperatorPropertyの例（整数のxorとandによる環）
 * @code
 * struct XorOperatorProperty {
 *     constexpr static int zero() { return 0; }
 *     constexpr static int add(const int &a, const int &b) { return a ^ b; }
 *     constexpr static int neg(const int &a) { return a; }
 *     constexpr static int one() { return 0; }
 *     constexpr static int mul(const int &a, const int &b) { return a & b; }
 * };
 * @endcode
 * constexprである必要はなく、またinvなど使わないものは定義しなくてもよい（必要なものがなかったらコンパイルエラーが発生する）
 */
template<class T, class OperatorProperty = matrix::OperatorPropertyDefault<T>> struct Matrix {
    int n, m;
    std::vector<std::vector<T>> v;

    /**
     * @brief コンストラクタ
     * @param v 行列(グリッド)の元となる vector<string> や vector<vector<T>>
     * @return Matrix
     */
    template <typename Iterable>
    Matrix(const std::vector<Iterable>& v_) noexcept : n(v_.size()), m(v_.size() == 0 ? 0 : v_[0].size()) {
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
    Matrix(int _n, int _m, T _val = OperatorProperty::zero()) : n(_n), m(_m), v(n, std::vector<T>(m, _val)) {}
    
    auto begin() noexcept {return v.begin();}
    auto end() noexcept {return v.end();}

    /**
     * @brief 行列(グリッド)の行数
     * @return size_t
     */
    [[nodiscard]]
    size_t size() const {return v.size();}

    std::vector<T>& operator [] (int i) {return v[i];}
    const std::vector<T>& operator [] (int i) const {return v[i];}
    Matrix<T>& operator = (const std::vector<std::vector<T>> &A) noexcept {
        n = A.size();
        m = (n == 0 ? 0 : A[0].size());
        v = A;
        return *this;
    }
    bool operator == (const Matrix<T> &A) noexcept {
        return this->v == A.v;
    }

    /**
     * @brief 転置
     * @return Matrix
     */
    [[nodiscard]]
    Matrix transpose() noexcept {
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
    Matrix rev_lr() noexcept {
        std::vector<std::vector<T>> ret = v;
        for(int i = 0; i < n; i ++) std::reverse(ret[i].begin(), ret[i].end());
        return Matrix(ret);
    }

    /**
     * @brief 上下反転
     * @return Matrix
     */
    [[nodiscard]]
    Matrix rev_ud() noexcept {
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
    Matrix rotate(int k) noexcept {
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
    Matrix shift(int dy, int dx) noexcept {
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
    Matrix shift_l(int k) noexcept {
        return this->shift(0, -k);
    }

    /**
     * @brief 右にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    Matrix shift_r(int k) noexcept {
        return this->shift(0, k);
    }

    /**
     * @brief 上にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    Matrix shift_u(int k) noexcept {
        return this->shift(-k, 0);
    }

    /**
     * @brief 下にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    Matrix shift_d(int k) noexcept {
        return this->shift(k, 0);
    }

    /**
     * @brief グリッドをvector<string>で返す
     * @return std::vector<std::string>
     */
    [[nodiscard]]
    std::vector<std::string> vstr() noexcept {
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
    std::vector<T> col(int j) noexcept {
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
    std::string str(int i) noexcept {
        std::string ret;
        ret.assign(v[i].begin(), v[i].end());
        return ret;
    }
    /**
     * @brief 保持している行列に行列Bを足す
     * @param B 足す行列
     * @return @c *this
    */
    Matrix &operator+=(const Matrix &B) {
        if(n == 0) return (*this);
        assert(n == B.size() && m == B[0].size());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                (*this)[i][j] = OperatorProperty::add((*this)[i][j], B[i][j]);
        return (*this);
    }
    /**
     * @brief 保持している行列から行列Bを引く
     * @param B 引く行列
     * @return @c *this
    */
    Matrix &operator-=(const Matrix &B) {
        if(n == 0) return (*this);
        assert(n == B.size() && m == B[0].size());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) 
                (*this)[i][j] = OperatorProperty::add((*this)[i][j], OperatorProperty::neg(B[i][j]));
        return (*this);
    }

    /**
     * @brief 保持している行列に行列Bを掛ける
     * @param B 掛ける行列
     * @return @c *this
    */
    Matrix &operator*=(const Matrix &B) {
        int p = B[0].size();
        Matrix<T> C(n, p);
        for(int i = 0; i < n; i ++) {
            for(int k = 0; k < m; k ++) {
                for(int j = 0; j < p; j ++) {
                    C[i][j] = OperatorProperty::add(C[i][j], OperatorProperty::mul((*this)[i][k], B[k][j]));
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
    Matrix pow(long long k) const {
        Matrix<T> A = *this, B(n, n);
        for(int i = 0; i < n; i ++) B[i][i] = OperatorProperty::one();
        while(k > 0) {
            if(k & 1) B *= A;
            A *= A;
            k >>= 1;
        }
        return B;
    }

    [[nodiscard]]
    Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
    [[nodiscard]]
    Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
    [[nodiscard]]
    Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }

    /**
     * @brief 行列Aと列ベクトルBの積
     * @param A Matrix<T>
     * @param B vector<T>
     * @return vector<T> 列ベクトル
    */
    [[nodiscard]]
    friend std::vector<T> operator*(const Matrix &A, const std::vector<T> &B) {
        std::vector<T> ret(A.n, 0);
        for(int i = 0; i < A.n; i ++) {
            for(int j = 0; j < A.m; j ++) {
                ret[i] = OperatorProperty::add(ret[i], OperatorProperty::mul(A[i][j], B[j]));
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
    friend std::vector<T> operator*(const std::vector<T> &A, const Matrix &B) {
        std::vector<T> ret(B.m, 0);
        for(int i = 0; i < B.n; i ++) {
            for(int j = 0; j < B.m; j ++) {
                ret[j] = OperatorProperty::add(ret[j], OperatorProperty::mul(A[i], B[i][j]));
            }
        }
        return ret;
    }

    /**
     * @brief 行列式
     * @return 行列式
    */
    [[nodiscard]]
    T det() const {
        assert(n == m);
        if(n == 0) return T(1);
        if constexpr(std::is_same_v<OperatorProperty, matrix::OperatorPropertyDefault<T>>) {
            std::vector A(n, std::valarray(T(0), n));
            for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++) A[i][j] = this->v[i][j];
            return forward_elimination(A);
        } else {
            auto A = this->v;
            return forward_elimination(A);
        }
    }

    /**
     * @brief 逆行列
     * @return 逆行列
     */
    [[nodiscard]]
    Matrix inv() const {
        assert(n == m);
        if(n == 0) return Matrix(n, n);
        if constexpr(std::is_same_v<OperatorProperty, matrix::OperatorPropertyDefault<T>>) {
            std::vector A(n, std::valarray(T(0), n+n));
            for(int i = 0; i < n; i ++) {
                for(int j = 0; j < n; j ++) A[i][j] = this->v[i][j];
                A[i][n+i] = T(1);
            }
            assert(forward_elimination(A) != T(0));
            for(int i = n - 1; i >= 0; i --) {
                for(int j = i - 1; j >= 0; j --) {
                    A[j] -= A[i] * A[j][i];
                }
            }
            Matrix<T> ret(n, n);
            for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++) ret[i][j] = A[i][n+j];
            return ret;
        } else {
            std::vector A(n, std::vector<T>(n+n, OperatorProperty::zero()));
            for(int i = 0; i < n; i ++) {
                for(int j = 0; j < n; j ++) A[i][j] = this->v[i][j];
                A[i][n+i] = OperatorProperty::one();
            }
            assert(forward_elimination(A) != T(0));
            for(int i = n - 1; i >= 0; i --) {
                for(int j = i - 1; j >= 0; j --) {
                    for(int k = n; k < n+n; k ++) {
                        A[j][k] = OperatorProperty::add(A[j][k], OperatorProperty::neg(OperatorProperty::mul(A[i][k], A[j][i])));
                    }
                }
            }
            Matrix<T> ret(n, n);
            for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++) ret[i][j] = A[i][n+j];
            return ret;
        }
    }

private:
    /**
     * @brief ガウスの消去法の前進消去を行って上三角行列を作り、行列式を返す
     * @param A 行列
     * @return 行列式
     * @note
     * rank(A) < nの場合は0を返す
     * 正方行列ではない場合、0以外が残る左からn個の列を使って行列式を計算する
     */
    T forward_elimination(std::vector<std::valarray<T>>& A) const {
        std::vector<int> pivot_col(n, 0);
        T d(1);
        for(int i = 0; i < n; i ++) {
            if(i - 1 >= 0) pivot_col[i] = pivot_col[i - 1] + 1;
            while(pivot_col[i] < m) {
                int pivot = i;
                if constexpr(std::is_floating_point_v<T>) {
                    for(int j = i + 1; j < n; j ++) if(std::abs(A[j][pivot_col[i]]) > std::abs(A[pivot][pivot_col[i]])) pivot = j;
                    if(std::abs(A[pivot][pivot_col[i]]) < 1e-9) {
                        pivot_col[i] ++;
                        continue;
                    }
                } else {
                    while(pivot < n && A[pivot][pivot_col[i]] == T(0)) pivot ++;
                    if(A[pivot][pivot_col[i]] == T(0)) {
                        pivot_col[i] ++;
                        continue;
                    }
                }
                if(pivot != i) {
                    std::swap(A[i], A[pivot]);
                    d *= -T(1);
                }
                break;
            }
            if(pivot_col[i] == m) return T(0);
            T scale = A[i][pivot_col[i]];
            d *= scale;
            A[i] /= scale;
            for(int j = i + 1; j < n; j ++) A[j] -= A[i] * A[j][pivot_col[i]];
        }
        return d;
    }

    /**
     * @brief ガウスの消去法の前進消去を行って上三角行列を作り、行列式を返す
     * @param A 行列
     * @return 行列式
     * @note
     * rank(A) < nの場合は0を返す
     * 正方行列ではない場合、0以外が残る左からn個の列を使って行列式を計算する
     */
    T forward_elimination(std::vector<std::vector<T>>& A) const {
        std::vector<int> pivot_col(n, 0);
        T d = OperatorProperty::one();
        for(int i = 0; i < n; i ++) {
            if(i - 1 >= 0) pivot_col[i] = pivot_col[i - 1] + 1;
            while(pivot_col[i] < m) {
                int pivot = i;
                while(pivot < n && A[pivot][pivot_col[i]] == OperatorProperty::zero()) pivot ++;
                if(A[pivot][pivot_col[i]] == OperatorProperty::zero()) {
                    pivot_col[i] ++;
                    continue;
                }
                if(pivot != i) {
                    std::swap(A[i], A[pivot]);
                    d = OperatorProperty::neg(d);
                }
                break;
            }
            if(pivot_col[i] == m) return T(0);
            T scale = A[i][pivot_col[i]];
            d = OperatorProperty::mul(d, scale);
            for(int j = pivot_col[i]; j < m; j ++) A[i][j] = OperatorProperty::mul(A[i][j], OperatorProperty::inv(scale));
            for(int j = i + 1; j < n; j ++) {
                T scale = A[j][pivot_col[i]];
                for(int k = pivot_col[i]; k < m; k ++) {
                    A[j][k] = OperatorProperty::add(A[j][k], OperatorProperty::neg(OperatorProperty::mul(A[i][k], scale)));
                }
            }
        }
        return d;
    }
};
