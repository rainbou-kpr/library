---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: cpp/matrix.hpp
    title: "\u884C\u5217"
  - icon: ':question:'
    path: cpp/modint.hpp
    title: "\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod\
      \ \u3092\u53D6\u308B\u30AF\u30E9\u30B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1340
    links:
    - https://yukicoder.me/problems/no/1340
  bundledCode: "#line 1 \"test/yukicoder-search-oji.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/1340\"\n\n#line 2 \"cpp/matrix.hpp\"\n\n#include\
    \ <vector>\n#include <string>\n#include <algorithm>\n#include <valarray>\n#include\
    \ <cassert>\n#include <type_traits>\n\nnamespace matrix {\n    template <typename\
    \ T>\n    struct OperatorPropertyDefault {\n        constexpr static T zero()\
    \ { return T(0); }\n        constexpr static T add(const T &a, const T &b) { return\
    \ a + b; }\n        constexpr static T neg(const T &a) { return -a; }\n      \
    \  constexpr static T one() { return T(1); }\n        constexpr static T mul(const\
    \ T &a, const T &b) { return a * b; }\n        constexpr static T inv(const T\
    \ &a) { return T(1) / a; }\n    };\n}\n\n/**\n * @brief \u884C\u5217\n * @tparam\
    \ T \u578B \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u8981\u7D20\u3068\u306A\
    \u308Bint\u3084char\n * @tparam OperatorProperty \u884C\u5217\u306E\u8981\u7D20\
    \u306E\u6F14\u7B97\u3092\u5B9A\u7FA9\u3059\u308B\u69CB\u9020\u4F53 0,1\u3068+,*\u306A\
    \u3089\u7701\u7565\u53EF\n *\n * @note\n * OperatorProperty\u306E\u4F8B\uFF08\u6574\
    \u6570\u306Exor\u3068and\u306B\u3088\u308B\u74B0\uFF09\n * @code\n * struct XorOperatorProperty\
    \ {\n *     constexpr static int zero() { return 0; }\n *     constexpr static\
    \ int add(const int &a, const int &b) { return a ^ b; }\n *     constexpr static\
    \ int neg(const int &a) { return a; }\n *     constexpr static int one() { return\
    \ 0; }\n *     constexpr static int mul(const int &a, const int &b) { return a\
    \ & b; }\n * };\n * @endcode\n * constexpr\u3067\u3042\u308B\u5FC5\u8981\u306F\
    \u306A\u304F\u3001\u307E\u305Finv\u306A\u3069\u4F7F\u308F\u306A\u3044\u3082\u306E\
    \u306F\u5B9A\u7FA9\u3057\u306A\u304F\u3066\u3082\u3088\u3044\uFF08\u5FC5\u8981\
    \u306A\u3082\u306E\u304C\u306A\u304B\u3063\u305F\u3089\u30B3\u30F3\u30D1\u30A4\
    \u30EB\u30A8\u30E9\u30FC\u304C\u767A\u751F\u3059\u308B\uFF09\n */\ntemplate<class\
    \ T, class OperatorProperty = matrix::OperatorPropertyDefault<T>> struct Matrix\
    \ {\n    int n, m;\n    std::vector<std::vector<T>> v;\n\n    /**\n     * @brief\
    \ \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * @param v \u884C\u5217(\u30B0\
    \u30EA\u30C3\u30C9)\u306E\u5143\u3068\u306A\u308B vector<string> \u3084 vector<vector<T>>\n\
    \     * @return Matrix\n     */\n    template <typename Iterable>\n    Matrix(const\
    \ std::vector<Iterable>& v_) noexcept : n(v_.size()), m(v_.size() == 0 ? 0 : v_[0].size())\
    \ {\n        v.resize(n);\n        for(int i = 0; i < n; i++) {\n            v[i].assign(v_[i].begin(),\
    \ v_[i].end());\n        }\n    }\n\n    /**\n     * @brief \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * @param _n \u884C\u5217(\u30B0\u30EA\u30C3\u30C9\
    )\u306E\u884C\u6570\n     * @param _m \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\
    \u5217\u6570\n     * @param _val \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u8981\
    \u7D20\u306E\u521D\u671F\u5024\n     * @return Matrix\n     */\n    Matrix(int\
    \ _n, int _m, T _val = OperatorProperty::zero()) : n(_n), m(_m), v(n, std::vector<T>(m,\
    \ _val)) {}\n    \n    auto begin() noexcept {return v.begin();}\n    auto end()\
    \ noexcept {return v.end();}\n\n    /**\n     * @brief \u884C\u5217(\u30B0\u30EA\
    \u30C3\u30C9)\u306E\u884C\u6570\n     * @return size_t\n     */\n    [[nodiscard]]\n\
    \    size_t size() const {return v.size();}\n\n    std::vector<T>& operator []\
    \ (int i) {return v[i];}\n    const std::vector<T>& operator [] (int i) const\
    \ {return v[i];}\n    Matrix<T>& operator = (const std::vector<std::vector<T>>\
    \ &A) noexcept {\n        n = A.size();\n        m = (n == 0 ? 0 : A[0].size());\n\
    \        v = A;\n        return *this;\n    }\n    bool operator == (const Matrix<T>\
    \ &A) noexcept {\n        return this->v == A.v;\n    }\n\n    /**\n     * @brief\
    \ \u8EE2\u7F6E\n     * @return Matrix\n     */\n    [[nodiscard]]\n    Matrix\
    \ transpose() noexcept {\n        if(n == 0) return Matrix(v);\n        std::vector<std::vector<T>>\
    \ ret(m);\n        for(int i = 0; i < m; i ++) {\n            ret[i].resize(n);\n\
    \            for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];\n        }\n   \
    \     return Matrix(ret);\n    }\n\n    /**\n     * @brief \u5DE6\u53F3\u53CD\u8EE2\
    \n     * @return Matrix\n     */\n    [[nodiscard]]\n    Matrix rev_lr() noexcept\
    \ {\n        std::vector<std::vector<T>> ret = v;\n        for(int i = 0; i <\
    \ n; i ++) std::reverse(ret[i].begin(), ret[i].end());\n        return Matrix(ret);\n\
    \    }\n\n    /**\n     * @brief \u4E0A\u4E0B\u53CD\u8EE2\n     * @return Matrix\n\
    \     */\n    [[nodiscard]]\n    Matrix rev_ud() noexcept {\n        std::vector<std::vector<T>>\
    \ ret = v;\n        reverse(ret.begin(), ret.end());\n        return Matrix(ret);\n\
    \    }\n\n    /**\n     * @brief \u6642\u8A08\u5468\u308A\u306B90\u5EA6\u56DE\u8EE2\
    \n     * @param k \u56DE\u8EE2\u3059\u308B\u56DE\u6570\n     * @return Matrix\n\
    \     */\n    [[nodiscard]]\n    Matrix rotate(int k) noexcept {\n        k %=\
    \ 4;\n        if(k == 0) return *this;\n        if(k < 0) k += 4;\n        if(k\
    \ == 2) return this->rev_lr().rev_ud();\n        std::vector<std::vector<T>> ret(m);\n\
    \        if(k == 1) {\n            for(int i = 0; i < m; i ++) {\n           \
    \     ret[i].resize(n);\n                for(int j = 0; j < n; j ++) ret[i][j]\
    \ = v[n - j - 1][i];\n            }\n        } else {\n            for(int i =\
    \ 0; i < m; i ++) {\n                ret[i].resize(n);\n                for(int\
    \ j = 0; j < n; j ++) ret[i][j] = v[j][m - i - 1];\n            }\n        }\n\
    \        return Matrix(ret);\n    }\n\n    /**\n     * @brief (i, j)\u3092((i\
    \ + dy) mod n, (j + dx) mod m)\u306B\u79FB\u52D5\n     * @return Matrix\n    \
    \ */\n    [[nodiscard]]\n    Matrix shift(int dy, int dx) noexcept {\n       \
    \ std::vector<std::vector<T>> ret = v;\n        for(int i = 0, ni = dy; i < n;\
    \ i ++, ni ++) {\n            if(ni >= n) ni = 0;\n            for(int j = 0,\
    \ nj = dx; j < m; j ++, nj ++) {\n                if(nj >= m) nj = 0;\n      \
    \          ret[ni][nj] = v[i][j];\n            }\n        }\n        return Matrix(ret);\n\
    \    }\n\n    /**\n     * @brief \u5DE6\u306Bk\u56DE\u30B7\u30D5\u30C8\n     *\
    \ @return Matrix\n     */\n    [[nodiscard]]\n    Matrix shift_l(int k) noexcept\
    \ {\n        return this->shift(0, -k);\n    }\n\n    /**\n     * @brief \u53F3\
    \u306Bk\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n     */\n    [[nodiscard]]\n\
    \    Matrix shift_r(int k) noexcept {\n        return this->shift(0, k);\n   \
    \ }\n\n    /**\n     * @brief \u4E0A\u306Bk\u56DE\u30B7\u30D5\u30C8\n     * @return\
    \ Matrix\n     */\n    [[nodiscard]]\n    Matrix shift_u(int k) noexcept {\n \
    \       return this->shift(-k, 0);\n    }\n\n    /**\n     * @brief \u4E0B\u306B\
    k\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n     */\n    [[nodiscard]]\n\
    \    Matrix shift_d(int k) noexcept {\n        return this->shift(k, 0);\n   \
    \ }\n\n    /**\n     * @brief \u30B0\u30EA\u30C3\u30C9\u3092vector<string>\u3067\
    \u8FD4\u3059\n     * @return std::vector<std::string>\n     */\n    [[nodiscard]]\n\
    \    std::vector<std::string> vstr() noexcept {\n        std::vector<std::string>\
    \ ret(n);\n        for(int i = 0; i < n; i ++) {\n            ret[i].assign(v[i].begin(),\
    \ v[i].end());\n        }\n        return ret;\n    }\n\n    /**\n     * @brief\
    \ \u30B0\u30EA\u30C3\u30C9\u306Ej\u5217\u76EE\u3092\u8FD4\u3059\n     * @param\
    \ j \u8FD4\u3059\u5217\u756A\u53F7(0-indexed)\n     * @return std::vector<T>\n\
    \     */\n    [[nodiscard]]\n    std::vector<T> col(int j) noexcept {\n      \
    \  std::vector<T> ret(n);\n        for(int i = 0; i < n; i ++) {\n           \
    \ ret[i] = v[i][j];\n        }\n        return ret;\n    }\n\n    /**\n     *\
    \ @brief \u30B0\u30EA\u30C3\u30C9\u306Ei\u884C\u76EE\u3092string\u3067\u8FD4\u3059\
    \n     * @param i \u8FD4\u3059\u884C\u756A\u53F7(0-indexed)\n     * @return std::string\n\
    \     */\n    [[nodiscard]]\n    std::string str(int i) noexcept {\n        std::string\
    \ ret;\n        ret.assign(v[i].begin(), v[i].end());\n        return ret;\n \
    \   }\n    /**\n     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u884C\u5217\
    \u306B\u884C\u5217B\u3092\u8DB3\u3059\n     * @param B \u8DB3\u3059\u884C\u5217\
    \n     * @return @c *this\n    */\n    Matrix &operator+=(const Matrix &B) {\n\
    \        if(n == 0) return (*this);\n        assert(n == B.size() && m == B[0].size());\n\
    \        for(int i = 0; i < n; i++)\n            for(int j = 0; j < m; j++)\n\
    \                (*this)[i][j] = OperatorProperty::add((*this)[i][j], B[i][j]);\n\
    \        return (*this);\n    }\n    /**\n     * @brief \u4FDD\u6301\u3057\u3066\
    \u3044\u308B\u884C\u5217\u304B\u3089\u884C\u5217B\u3092\u5F15\u304F\n     * @param\
    \ B \u5F15\u304F\u884C\u5217\n     * @return @c *this\n    */\n    Matrix &operator-=(const\
    \ Matrix &B) {\n        if(n == 0) return (*this);\n        assert(n == B.size()\
    \ && m == B[0].size());\n        for(int i = 0; i < n; i++)\n            for(int\
    \ j = 0; j < m; j++) \n                (*this)[i][j] = OperatorProperty::add((*this)[i][j],\
    \ OperatorProperty::neg(B[i][j]));\n        return (*this);\n    }\n\n    /**\n\
    \     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u884C\u5217\u306B\u884C\u5217\
    B\u3092\u639B\u3051\u308B\n     * @param B \u639B\u3051\u308B\u884C\u5217\n  \
    \   * @return @c *this\n    */\n    Matrix &operator*=(const Matrix &B) {\n  \
    \      int p = B[0].size();\n        Matrix<T> C(n, p);\n        for(int i = 0;\
    \ i < n; i ++) {\n            for(int k = 0; k < m; k ++) {\n                for(int\
    \ j = 0; j < p; j ++) {\n                    C[i][j] = OperatorProperty::add(C[i][j],\
    \ OperatorProperty::mul((*this)[i][k], B[k][j]));\n                }\n       \
    \     }\n        }\n        v.swap(C.v);\n        m = p;\n        return (*this);\n\
    \    }\n\n    /**\n     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u884C\u5217\
    \u306Ek\u4E57\u3092\u6C42\u3081\u308B\n     * @param k \u6307\u6570\n     * @return\
    \ Matrix\n    */\n    [[nodiscard]]\n    Matrix pow(long long k) const {\n   \
    \     Matrix<T> A = *this, B(n, n);\n        for(int i = 0; i < n; i ++) B[i][i]\
    \ = OperatorProperty::one();\n        while(k > 0) {\n            if(k & 1) B\
    \ *= A;\n            A *= A;\n            k >>= 1;\n        }\n        return\
    \ B;\n    }\n\n    [[nodiscard]]\n    Matrix operator+(const Matrix &B) const\
    \ { return (Matrix(*this) += B); }\n    [[nodiscard]]\n    Matrix operator-(const\
    \ Matrix &B) const { return (Matrix(*this) -= B); }\n    [[nodiscard]]\n    Matrix\
    \ operator*(const Matrix &B) const { return (Matrix(*this) *= B); }\n\n    /**\n\
    \     * @brief \u884C\u5217A\u3068\u5217\u30D9\u30AF\u30C8\u30EBB\u306E\u7A4D\n\
    \     * @param A Matrix<T>\n     * @param B vector<T>\n     * @return vector<T>\
    \ \u5217\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n    friend std::vector<T>\
    \ operator*(const Matrix &A, const std::vector<T> &B) {\n        std::vector<T>\
    \ ret(A.n, 0);\n        for(int i = 0; i < A.n; i ++) {\n            for(int j\
    \ = 0; j < A.m; j ++) {\n                ret[i] = OperatorProperty::add(ret[i],\
    \ OperatorProperty::mul(A[i][j], B[j]));\n            }\n        }\n        return\
    \ ret;\n    }\n\n    /**\n     * @brief \u884C\u30D9\u30AF\u30C8\u30EBA\u3068\u884C\
    \u5217B\u306E\u7A4D\n     * @param A vector<T>\n     * @param B Matrix<T>\n  \
    \   * @return vector<T> \u884C\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n\
    \    friend std::vector<T> operator*(const std::vector<T> &A, const Matrix &B)\
    \ {\n        std::vector<T> ret(B.m, 0);\n        for(int i = 0; i < B.n; i ++)\
    \ {\n            for(int j = 0; j < B.m; j ++) {\n                ret[j] = OperatorProperty::add(ret[j],\
    \ OperatorProperty::mul(A[i], B[i][j]));\n            }\n        }\n        return\
    \ ret;\n    }\n\n    /**\n     * @brief \u884C\u5217\u5F0F\n     * @return \u884C\
    \u5217\u5F0F\n    */\n    [[nodiscard]]\n    T det() const {\n        assert(n\
    \ == m);\n        if(n == 0) return T(1);\n        if constexpr(std::is_same_v<OperatorProperty,\
    \ matrix::OperatorPropertyDefault<T>>) {\n            std::vector A(n, std::valarray(T(0),\
    \ n));\n            for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++) A[i][j]\
    \ = this->v[i][j];\n            return forward_elimination(A);\n        } else\
    \ {\n            auto A = this->v;\n            return forward_elimination(A);\n\
    \        }\n    }\n\n    /**\n     * @brief \u9006\u884C\u5217\n     * @return\
    \ \u9006\u884C\u5217\n     */\n    [[nodiscard]]\n    Matrix inv() const {\n \
    \       assert(n == m);\n        if(n == 0) return Matrix(n, n);\n        if constexpr(std::is_same_v<OperatorProperty,\
    \ matrix::OperatorPropertyDefault<T>>) {\n            std::vector A(n, std::valarray(T(0),\
    \ n+n));\n            for(int i = 0; i < n; i ++) {\n                for(int j\
    \ = 0; j < n; j ++) A[i][j] = this->v[i][j];\n                A[i][n+i] = T(1);\n\
    \            }\n            assert(forward_elimination(A) != T(0));\n        \
    \    for(int i = n - 1; i >= 0; i --) {\n                for(int j = i - 1; j\
    \ >= 0; j --) {\n                    A[j] -= A[i] * A[j][i];\n               \
    \ }\n            }\n            Matrix<T> ret(n, n);\n            for(int i =\
    \ 0; i < n; i ++) for(int j = 0; j < n; j ++) ret[i][j] = A[i][n+j];\n       \
    \     return ret;\n        } else {\n            std::vector A(n, std::vector<T>(n+n,\
    \ OperatorProperty::zero()));\n            for(int i = 0; i < n; i ++) {\n   \
    \             for(int j = 0; j < n; j ++) A[i][j] = this->v[i][j];\n         \
    \       A[i][n+i] = OperatorProperty::one();\n            }\n            assert(forward_elimination(A)\
    \ != T(0));\n            for(int i = n - 1; i >= 0; i --) {\n                for(int\
    \ j = i - 1; j >= 0; j --) {\n                    for(int k = n; k < n+n; k ++)\
    \ {\n                        A[j][k] = OperatorProperty::add(A[j][k], OperatorProperty::neg(OperatorProperty::mul(A[i][k],\
    \ A[j][i])));\n                    }\n                }\n            }\n     \
    \       Matrix<T> ret(n, n);\n            for(int i = 0; i < n; i ++) for(int\
    \ j = 0; j < n; j ++) ret[i][j] = A[i][n+j];\n            return ret;\n      \
    \  }\n    }\n\nprivate:\n    /**\n     * @brief \u30AC\u30A6\u30B9\u306E\u6D88\
    \u53BB\u6CD5\u306E\u524D\u9032\u6D88\u53BB\u3092\u884C\u3063\u3066\u4E0A\u4E09\
    \u89D2\u884C\u5217\u3092\u4F5C\u308A\u3001\u884C\u5217\u5F0F\u3092\u8FD4\u3059\
    \n     * @param A \u884C\u5217\n     * @return \u884C\u5217\u5F0F\n     * @note\n\
    \     * rank(A) < n\u306E\u5834\u5408\u306F0\u3092\u8FD4\u3059\n     * \u6B63\u65B9\
    \u884C\u5217\u3067\u306F\u306A\u3044\u5834\u5408\u30010\u4EE5\u5916\u304C\u6B8B\
    \u308B\u5DE6\u304B\u3089n\u500B\u306E\u5217\u3092\u4F7F\u3063\u3066\u884C\u5217\
    \u5F0F\u3092\u8A08\u7B97\u3059\u308B\n     */\n    T forward_elimination(std::vector<std::valarray<T>>&\
    \ A) const {\n        std::vector<int> pivot_col(n, 0);\n        T d(1);\n   \
    \     for(int i = 0; i < n; i ++) {\n            if(i - 1 >= 0) pivot_col[i] =\
    \ pivot_col[i - 1] + 1;\n            while(pivot_col[i] < m) {\n             \
    \   int pivot = i;\n                if constexpr(std::is_floating_point_v<T>)\
    \ {\n                    for(int j = i + 1; j < n; j ++) if(std::abs(A[j][pivot_col[i]])\
    \ > std::abs(A[pivot][pivot_col[i]])) pivot = j;\n                    if(std::abs(A[pivot][pivot_col[i]])\
    \ < 1e-9) {\n                        pivot_col[i] ++;\n                      \
    \  continue;\n                    }\n                } else {\n              \
    \      while(pivot < n && A[pivot][pivot_col[i]] == T(0)) pivot ++;\n        \
    \            if(A[pivot][pivot_col[i]] == T(0)) {\n                        pivot_col[i]\
    \ ++;\n                        continue;\n                    }\n            \
    \    }\n                if(pivot != i) {\n                    std::swap(A[i],\
    \ A[pivot]);\n                    d *= -T(1);\n                }\n           \
    \     break;\n            }\n            if(pivot_col[i] == m) return T(0);\n\
    \            T scale = A[i][pivot_col[i]];\n            d *= scale;\n        \
    \    A[i] /= scale;\n            for(int j = i + 1; j < n; j ++) A[j] -= A[i]\
    \ * A[j][pivot_col[i]];\n        }\n        return d;\n    }\n\n    /**\n    \
    \ * @brief \u30AC\u30A6\u30B9\u306E\u6D88\u53BB\u6CD5\u306E\u524D\u9032\u6D88\u53BB\
    \u3092\u884C\u3063\u3066\u4E0A\u4E09\u89D2\u884C\u5217\u3092\u4F5C\u308A\u3001\
    \u884C\u5217\u5F0F\u3092\u8FD4\u3059\n     * @param A \u884C\u5217\n     * @return\
    \ \u884C\u5217\u5F0F\n     * @note\n     * rank(A) < n\u306E\u5834\u5408\u306F\
    0\u3092\u8FD4\u3059\n     * \u6B63\u65B9\u884C\u5217\u3067\u306F\u306A\u3044\u5834\
    \u5408\u30010\u4EE5\u5916\u304C\u6B8B\u308B\u5DE6\u304B\u3089n\u500B\u306E\u5217\
    \u3092\u4F7F\u3063\u3066\u884C\u5217\u5F0F\u3092\u8A08\u7B97\u3059\u308B\n   \
    \  */\n    T forward_elimination(std::vector<std::vector<T>>& A) const {\n   \
    \     std::vector<int> pivot_col(n, 0);\n        T d = OperatorProperty::one();\n\
    \        for(int i = 0; i < n; i ++) {\n            if(i - 1 >= 0) pivot_col[i]\
    \ = pivot_col[i - 1] + 1;\n            while(pivot_col[i] < m) {\n           \
    \     int pivot = i;\n                while(pivot < n && A[pivot][pivot_col[i]]\
    \ == OperatorProperty::zero()) pivot ++;\n                if(A[pivot][pivot_col[i]]\
    \ == OperatorProperty::zero()) {\n                    pivot_col[i] ++;\n     \
    \               continue;\n                }\n                if(pivot != i) {\n\
    \                    std::swap(A[i], A[pivot]);\n                    d = OperatorProperty::neg(d);\n\
    \                }\n                break;\n            }\n            if(pivot_col[i]\
    \ == m) return T(0);\n            T scale = A[i][pivot_col[i]];\n            d\
    \ = OperatorProperty::mul(d, scale);\n            for(int j = pivot_col[i]; j\
    \ < m; j ++) A[i][j] = OperatorProperty::mul(A[i][j], OperatorProperty::inv(scale));\n\
    \            for(int j = i + 1; j < n; j ++) {\n                T scale = A[j][pivot_col[i]];\n\
    \                for(int k = pivot_col[i]; k < m; k ++) {\n                  \
    \  A[j][k] = OperatorProperty::add(A[j][k], OperatorProperty::neg(OperatorProperty::mul(A[i][k],\
    \ scale)));\n                }\n            }\n        }\n        return d;\n\
    \    }\n};\n#line 2 \"cpp/modint.hpp\"\n\n/**\n * @file modint.hpp\n * @brief\
    \ \u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod \u3092\
    \u53D6\u308B\u30AF\u30E9\u30B9\n */\n\n#include <iostream>\n#include <utility>\n\
    #include <limits>\n#line 12 \"cpp/modint.hpp\"\n#include <cstdint>\n#line 14 \"\
    cpp/modint.hpp\"\n\nnamespace detail {\n    static constexpr std::uint16_t prime32_bases[]\
    \ {\n        15591,  2018,  166, 7429,  8064, 16045, 10503,  4399,  1949,  1295,\
    \ 2776,  3620,   560,  3128,  5212,  2657,\n         2300,  2021, 4652, 1471,\
    \  9336,  4018,  2398, 20462, 10277,  8028, 2213,  6219,   620,  3763,  4852,\
    \  5012,\n         3185,  1333, 6227, 5298,  1074,  2391,  5113,  7061,   803,\
    \  1269, 3875,   422,   751,   580,  4729, 10239,\n          746,  2951,  556,\
    \ 2206,  3778,   481,  1522,  3476,   481,  2487, 3266,  5633,   488,  3373, \
    \ 6441,  3344,\n           17, 15105, 1490, 4154,  2036,  1882,  1813,   467,\
    \  3307, 14042, 6371,   658,  1005,   903,   737,  1887,\n         7447,  1888,\
    \ 2848, 1784,  7559,  3400,   951, 13969,  4304,   177,   41, 19875,  3110, 13221,\
    \  8726,   571,\n         7043,  6943, 1199,  352,  6435,   165,  1169,  3315,\
    \   978,   233, 3003,  2562,  2994, 10587, 10030,  2377,\n         1902,  5354,\
    \ 4447, 1555,   263, 27027,  2283,   305,   669,  1912,  601,  6186,   429,  1930,\
    \ 14873,  1784,\n         1661,   524, 3577,  236,  2360,  6146,  2850, 55637,\
    \  1753,  4178, 8466,   222,  2579,  2743,  2031,  2226,\n         2276,   374,\
    \ 2132,  813, 23788,  1610,  4422,  5159,  1725,  3597, 3366, 14336,   579,  \
    \ 165,  1375, 10018,\n        12616,  9816, 1371,  536,  1867, 10864,   857, \
    \ 2206,  5788,   434, 8085, 17618,   727,  3639,  1595,  4944,\n         2129,\
    \  2029, 8195, 8344,  6232,  9183,  8126,  1870,  3296,  7455, 8947, 25017,  \
    \ 541, 19115,   368,   566,\n         5674,   411,  522, 1027,  8215,  2050, \
    \ 6544, 10049,   614,   774, 2333,  3007, 35201,  4706,  1152,  1785,\n      \
    \   1028,  1540, 3743,  493,  4474,  2521, 26845,  8354,   864, 18915, 5465, \
    \ 2447,    42,  4511,  1660,   166,\n         1249,  6259, 2553,  304,   272,\
    \  7286,    73,  6554,   899,  2816, 5197, 13330,  7054,  2818,  3199,   811,\n\
    \          922,   350, 7514, 4452,  3449,  2663,  4708,   418,  1621,  1171, 3471,\
    \    88, 11345,   412,  1559,   194,\n    };\n\n    static constexpr bool is_SPRP(std::uint32_t\
    \ n, std::uint32_t a) noexcept {\n        std::uint32_t d = n - 1;\n        std::uint32_t\
    \ s = 0;\n        while ((d & 1) == 0) {\n            ++s;\n            d >>=\
    \ 1;\n        }\n        std::uint64_t cur = 1;\n        std::uint64_t pw = d;\n\
    \        while (pw) {\n            if (pw & 1) cur = (cur * a) % n;\n        \
    \    a = (static_cast<std::uint64_t>(a) * a) % n;\n            pw >>= 1;\n   \
    \     }\n        if (cur == 1) return true;\n        for (std::uint32_t r = 0;\
    \ r < s; ++r) {\n            if (cur == n - 1) return true;\n            cur =\
    \ (cur * cur) % n;\n        }\n        return false;\n    }\n\n    // 32\u30D3\
    \u30C3\u30C8\u7B26\u53F7\u306A\u3057\u6574\u6570\u306E\u7D20\u6570\u5224\u5B9A\
    \n    // \u53C2\u8003: M. Forisek and J. Jancina, \u201CFast Primality Testing\
    \ for Integers That Fit into a Machine Word,\u201D presented at the Conference\
    \ on Current Trends in Theory and Practice of Informatics, 2015.\n    [[nodiscard]]\n\
    \    static constexpr bool is_prime32(std::uint32_t x) noexcept {\n        if\
    \ (x == 2 || x == 3 || x == 5 || x == 7) return true;\n        if (x % 2 == 0\
    \ || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;\n        if (x < 121)\
    \ return (x > 1);\n        std::uint64_t h = x;\n        h = ((h >> 16) ^ h) *\
    \ 0x45d9f3b;\n        h = ((h >> 16) ^ h) * 0x45d9f3b;\n        h = ((h >> 16)\
    \ ^ h) & 0xff;\n        return is_SPRP(x, prime32_bases[h]);\n    }\n}\n\n///\
    \ @brief static_modint \u3068 dynamic_modint \u306E\u5B9F\u88C5\u3092 CRTP \u306B\
    \u3088\u3063\u3066\u884C\u3046\u305F\u3081\u306E\u30AF\u30E9\u30B9\u30C6\u30F3\
    \u30D7\u30EC\u30FC\u30C8\n/// @tparam Modint \u3053\u306E\u30AF\u30E9\u30B9\u30C6\
    \u30F3\u30D7\u30EC\u30FC\u30C8\u3092\u7D99\u627F\u3059\u308B\u30AF\u30E9\u30B9\
    \ntemplate <class Modint>\nclass modint_base {\npublic:\n    /// @brief \u4FDD\
    \u6301\u3059\u308B\u5024\u306E\u578B\n    using value_type = std::uint32_t;\n\n\
    \    /// @brief 0 \u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n    constexpr\
    \ modint_base() noexcept\n        : m_value{ 0 } {}\n\n    /// @brief @c value\
    \ \u306E\u5270\u4F59\u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n    ///\
    \ @param value \u521D\u671F\u5316\u306B\u4F7F\u3046\u5024\n    template <class\
    \ SignedIntegral, std::enable_if_t<std::is_integral_v<SignedIntegral> && std::is_signed_v<SignedIntegral>>*\
    \ = nullptr>\n    constexpr modint_base(SignedIntegral value) noexcept\n     \
    \   : m_value{ static_cast<value_type>((static_cast<long long>(value) % Modint::mod()\
    \ + Modint::mod()) % Modint::mod()) } {}\n\n    /// @brief @c value \u306E\u5270\
    \u4F59\u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n    /// @param value \u521D\
    \u671F\u5316\u306B\u4F7F\u3046\u5024\n    template <class UnsignedIntegral, std::enable_if_t<std::is_integral_v<UnsignedIntegral>\
    \ && std::is_unsigned_v<UnsignedIntegral>>* = nullptr>\n    constexpr modint_base(UnsignedIntegral\
    \ value) noexcept\n        : m_value{ static_cast<value_type>(value % Modint::mod())\
    \ } {}\n\n    /// @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\u3092\u53D6\
    \u5F97\u3057\u307E\u3059\u3002\n    /// @return \u4FDD\u6301\u3057\u3066\u3044\
    \u308B\u5024\n    [[nodiscard]]\n    constexpr value_type value() const noexcept\
    \ {\n        return m_value;\n    }\n\n    /// @brief \u4FDD\u6301\u3057\u3066\
    \u3044\u308B\u5024\u3092\u30A4\u30F3\u30AF\u30EA\u30E1\u30F3\u30C8\u3057\u3066\
    \u3001\u5270\u4F59\u3092\u53D6\u308A\u307E\u3059\u3002\n    /// @return @c *this\n\
    \    constexpr Modint& operator++() noexcept {\n        ++m_value;\n        if\
    \ (m_value == Modint::mod()) {\n            m_value = 0;\n        }\n        return\
    \ static_cast<Modint&>(*this);\n    }\n\n    /// @brief \u4FDD\u6301\u3057\u3066\
    \u3044\u308B\u5024\u3092\u30A4\u30F3\u30AF\u30EA\u30E1\u30F3\u30C8\u3057\u3066\
    \u3001\u5270\u4F59\u3092\u53D6\u308A\u307E\u3059\u3002\n    /// @return @c *this\n\
    \    constexpr Modint operator++(int) noexcept {\n        auto x = static_cast<const\
    \ Modint&>(*this);\n        ++*this;\n        return x;\n    }\n\n    /// @brief\
    \ \u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\u3092\u30C7\u30AF\u30EA\u30E1\u30F3\
    \u30C8\u3057\u3066\u3001\u5270\u4F59\u3092\u53D6\u308A\u307E\u3059\u3002\n   \
    \ /// @return @c *this\n    constexpr Modint& operator--() noexcept {\n      \
    \  if (m_value == 0) {\n            m_value = Modint::mod();\n        }\n    \
    \    --m_value;\n        return static_cast<Modint&>(*this);\n    }\n\n    ///\
    \ @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\u3092\u30C7\u30AF\u30EA\u30E1\
    \u30F3\u30C8\u3057\u3066\u3001\u5270\u4F59\u3092\u53D6\u308A\u307E\u3059\u3002\
    \n    /// @return @c *this\n    constexpr Modint operator--(int) noexcept {\n\
    \        auto x = static_cast<const Modint&>(*this);\n        --*this;\n     \
    \   return x;\n    }\n\n    /// @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\
    \u306B @c x \u306E\u6301\u3064\u5024\u3092\u8DB3\u3057\u3066\u3001\u5270\u4F59\
    \u3092\u53D6\u308A\u307E\u3059\u3002\n    /// @param x \u8DB3\u3059\u6570\n  \
    \  /// @return @c *this\n    constexpr Modint& operator+=(const Modint& x) noexcept\
    \ {\n        m_value += x.m_value;\n        if (m_value >= Modint::mod()) {\n\
    \            m_value -= Modint::mod();\n        }\n        return static_cast<Modint&>(*this);\n\
    \    }\n\n    /// @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\u304B\u3089\
    \ @c x \u306E\u6301\u3064\u5024\u3092\u5F15\u3044\u3066\u3001\u5270\u4F59\u3092\
    \u53D6\u308A\u307E\u3059\u3002\n    /// @param x \u5F15\u304F\u6570\n    /// @return\
    \ @c *this\n    constexpr Modint& operator-=(const Modint& x) noexcept {\n   \
    \     m_value -= x.m_value;\n        if (m_value >= Modint::mod()) {\n       \
    \     m_value += Modint::mod();\n        }\n        return static_cast<Modint&>(*this);\n\
    \    }\n\n    /// @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\u306B @c x\
    \ \u306E\u6301\u3064\u5024\u3092\u639B\u3051\u3066\u3001\u5270\u4F59\u3092\u53D6\
    \u308A\u307E\u3059\u3002\n    /// @param x \u639B\u3051\u308B\u6570\n    /// @return\
    \ @c *this\n    constexpr Modint& operator*=(const Modint& x) noexcept {\n   \
    \     m_value = static_cast<value_type>(static_cast<std::uint64_t>(m_value) *\
    \ x.m_value % Modint::mod());\n        return static_cast<Modint&>(*this);\n \
    \   }\n\n    /// @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\u3092 @c x\
    \ \u306E\u6301\u3064\u5024\u3067\u5272\u3063\u3066\u3001\u5270\u4F59\u3092\u53D6\
    \u308A\u307E\u3059\u3002\n    /// @remark \u6642\u9593\u8A08\u7B97\u91CF\uFF1A\
    \ @f$O(\\log x)@f$\n    /// @param x \u5272\u308B\u6570\n    /// @return @c *this\n\
    \    constexpr Modint& operator/=(const Modint& x) noexcept {\n        return\
    \ *this *= x.inv();\n    }\n\n    /// @brief \u81EA\u8EAB\u306E\u30B3\u30D4\u30FC\
    \u3092\u8FD4\u3057\u307E\u3059\u3002\n    /// @return @c *this\n    [[nodiscard]]\n\
    \    constexpr Modint operator+() const noexcept {\n        return static_cast<const\
    \ Modint&>(*this);\n    }\n\n    /// @brief \u81EA\u8EAB\u306E\u53CD\u6570\u3092\
    \u8FD4\u3057\u307E\u3059\u3002\n    /// @return \u81EA\u8EAB\u306E\u53CD\u6570\
    \n    [[nodiscard]]\n    constexpr Modint operator-() const noexcept {\n     \
    \   return 0 - static_cast<const Modint&>(*this);\n    }\n\n    /// @brief \u81EA\
    \u8EAB\u306E @c n \u4E57\u3092\u8FD4\u3057\u307E\u3059\u3002\n    /// @remark\
    \ \u6642\u9593\u8A08\u7B97\u91CF\uFF1A @f$O(\\log n)@f$\n    /// @param n \u6307\
    \u6570\n    /// @return \u81EA\u8EAB\u306E @c n \u4E57\n    [[nodiscard]]\n  \
    \  constexpr Modint pow(unsigned long long n) const noexcept {\n        Modint\
    \ x = 1;\n        Modint y = static_cast<const Modint&>(*this);\n        while\
    \ (n) {\n            if (n & 1) {\n                x *= y;\n            }\n  \
    \          y *= y;\n            n >>= 1;\n        }\n        return x;\n    }\n\
    \n    /// @brief \u81EA\u8EAB\u306E\u9006\u6570\u3092\u8FD4\u3057\u307E\u3059\u3002\
    \n    /// @remark \u6642\u9593\u8A08\u7B97\u91CF\uFF1A @f$O(\\log value)@f$\n\
    \    /// @return \u81EA\u8EAB\u306E\u9006\u6570\n    [[nodiscard]]\n    constexpr\
    \ Modint inv() const noexcept {\n        long long a = Modint::mod();\n      \
    \  long long b = m_value;\n        long long x = 0;\n        long long y = 1;\n\
    \        while (b) {\n            auto t = a / b;\n            auto u = a - t\
    \ * b;\n            a = b;\n            b = u;\n            u = x - t * y;\n \
    \           x = y;\n            y = u;\n        }\n        assert(a == 1 && \"\
    The inverse element does not exist.\");\n        x %= Modint::mod();\n       \
    \ if (x < 0) {\n            x += Modint::mod();\n        }\n        return x;\n\
    \    }\n\n    /// @brief @c x \u306B @c y \u3092\u8DB3\u3057\u305F\u30AA\u30D6\
    \u30B8\u30A7\u30AF\u30C8\u3092\u8FD4\u3057\u307E\u3059\u3002\n    /// @param x\
    \ \u8DB3\u3055\u308C\u308B\u6570\n    /// @param y \u8DB3\u3059\u6570\n    ///\
    \ @return @c x \u306B @c y \u3092\u8DB3\u3057\u305F\u30AA\u30D6\u30B8\u30A7\u30AF\
    \u30C8\n    [[nodiscard]]\n    friend constexpr Modint operator+(const Modint&\
    \ x, const Modint& y) noexcept {\n        return std::move(Modint{ x } += y);\n\
    \    }\n\n    /// @brief @c x \u304B\u3089 @c y \u3092\u5F15\u3044\u305F\u30AA\
    \u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u8FD4\u3057\u307E\u3059\u3002\n    /// @param\
    \ x \u5F15\u304B\u308C\u308B\u6570\n    /// @param y \u5F15\u304F\u6570\n    ///\
    \ @return @c x \u304B\u3089 @c y \u3092\u5F15\u3044\u305F\u30AA\u30D6\u30B8\u30A7\
    \u30AF\u30C8\n    [[nodiscard]]\n    friend constexpr Modint operator-(const Modint&\
    \ x, const Modint& y) noexcept {\n        return std::move(Modint{ x } -= y);\n\
    \    }\n\n    /// @brief @c x \u306B @c y \u3092\u639B\u3051\u305F\u30AA\u30D6\
    \u30B8\u30A7\u30AF\u30C8\u3092\u8FD4\u3057\u307E\u3059\u3002\n    /// @param x\
    \ \u639B\u3051\u3089\u308C\u308B\u6570\n    /// @param y \u639B\u3051\u308B\u6570\
    \n    /// @return @c x \u306B @c y \u3092\u639B\u3051\u305F\u30AA\u30D6\u30B8\u30A7\
    \u30AF\u30C8\n    [[nodiscard]]\n    friend constexpr Modint operator*(const Modint&\
    \ x, const Modint& y) noexcept {\n        return std::move(Modint{ x } *= y);\n\
    \    }\n\n    /// @brief @c x \u3092 @c y \u3067\u5272\u3063\u305F\u30AA\u30D6\
    \u30B8\u30A7\u30AF\u30C8\u3092\u8FD4\u3057\u307E\u3059\u3002\n    /// @param x\
    \ \u5272\u3089\u308C\u308B\u6570\n    /// @param y \u5272\u308B\u6570\n    ///\
    \ @return @c x \u3092 @c y \u3067\u5272\u3063\u305F\u30AA\u30D6\u30B8\u30A7\u30AF\
    \u30C8\n    [[nodiscard]]\n    friend constexpr Modint operator/(const Modint&\
    \ x, const Modint& y) noexcept {\n        return std::move(Modint{ x } /= y);\n\
    \    }\n\n    /// @brief @c x \u3068 @c y \u306E\u4FDD\u6301\u3059\u308B\u5024\
    \u304C\u7B49\u3057\u3044\u304B\u3069\u3046\u304B\u3092\u8ABF\u3079\u307E\u3059\
    \u3002\n    /// @return @c x \u3068 @c y \u306E\u4FDD\u6301\u3059\u308B\u5024\u304C\
    \u7B49\u3057\u3051\u308C\u3070 @c true \u3001\u305D\u3046\u3067\u306A\u3051\u308C\
    \u3070 @c false\n    [[nodiscard]]\n    friend constexpr bool operator==(const\
    \ Modint& x, const Modint& y) noexcept {\n        return x.m_value == y.m_value;\n\
    \    }\n\n    /// @brief @c x \u3068 @c y \u306E\u4FDD\u6301\u3059\u308B\u5024\
    \u304C\u7B49\u3057\u304F\u306A\u3044\u304B\u3069\u3046\u304B\u3092\u8ABF\u3079\
    \u307E\u3059\u3002\n    /// @return @c x \u3068 @c y \u306E\u4FDD\u6301\u3059\u308B\
    \u5024\u304C\u7B49\u3057\u3051\u308C\u3070 @c false \u3001\u305D\u3046\u3067\u306A\
    \u3051\u308C\u3070 @c true\n    [[nodiscard]]\n    friend constexpr bool operator!=(const\
    \ Modint& x, const Modint& y) noexcept {\n        return not (x == y);\n    }\n\
    \n    /// @brief \u5165\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u304B\u3089\u7B26\u53F7\
    \u4ED8\u304D\u6574\u6570\u3092\u8AAD\u307F\u53D6\u308A\u3001 @c x \u306B\u683C\
    \u7D0D\u3057\u307E\u3059\u3002\n    /// @tparam CharT \u5165\u529B\u30B9\u30C8\
    \u30EA\u30FC\u30E0\u306E\u6587\u5B57\u578B\n    /// @tparam Traits \u5165\u529B\
    \u30B9\u30C8\u30EA\u30FC\u30E0\u306E\u6587\u5B57\u30C8\u30EC\u30A4\u30C8\n   \
    \ /// @param is \u5165\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\n    /// @param x \u5165\
    \u529B\u3092\u53D7\u3051\u53D6\u308B\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n   \
    \ /// @return @c is\n    template <class CharT, class Traits>\n    friend std::basic_istream<CharT,\
    \ Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Modint& x) {\n  \
    \      long long tmp;\n        is >> tmp;\n        x = tmp;\n        return is;\n\
    \    }\n\n    /// @brief \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u306B @c x\
    \ \u306E\u4FDD\u6301\u3059\u308B\u5024\u3092\u51FA\u529B\u3057\u307E\u3059\u3002\
    \n    /// @tparam CharT \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u306E\u6587\
    \u5B57\u578B\n    /// @tparam Traits \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\
    \u306E\u6587\u5B57\u30C8\u30EC\u30A4\u30C8\n    /// @param os \u51FA\u529B\u30B9\
    \u30C8\u30EA\u30FC\u30E0\n    /// @param x \u51FA\u529B\u3059\u308B\u30AA\u30D6\
    \u30B8\u30A7\u30AF\u30C8\n    /// @return @c os\n    template <class CharT, class\
    \ Traits>\n    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT,\
    \ Traits>& os, const Modint& x) {\n        os << x.value();\n        return os;\n\
    \    }\n\nprotected:\n    value_type m_value;\n};\n\n/// @brief \u30B3\u30F3\u30D1\
    \u30A4\u30EB\u6642\u306B\u6CD5\u304C\u6C7A\u307E\u308B\u3068\u304D\u3001\u56DB\
    \u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod \u3092\u53D6\u308B\
    \u30AF\u30E9\u30B9\n/// @tparam Mod \u6CD5\ntemplate <std::uint32_t Mod>\nclass\
    \ static_modint : public modint_base<static_modint<Mod>> {\n    static_assert(Mod\
    \ > 0 && Mod <= std::numeric_limits<std::uint32_t>::max() / 2);\n\nprivate:\n\
    \    using base_type = modint_base<static_modint<Mod>>;\n\npublic:\n    using\
    \ typename base_type::value_type;\n\n    /// @brief \u6CD5\u3092\u53D6\u5F97\u3057\
    \u307E\u3059\u3002\n    /// @return \u6CD5\n    [[nodiscard]]\n    static constexpr\
    \ value_type mod() noexcept {\n        return Mod;\n    }\n\n    /// @brief 0\
    \ \u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n    constexpr static_modint()\
    \ noexcept\n        : base_type{} {}\n\n    /// @brief @c value \u306E\u5270\u4F59\
    \u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n    /// @param value \u521D\u671F\
    \u5316\u306B\u4F7F\u3046\u5024\n    template <class SignedIntegral, std::enable_if_t<std::is_integral_v<SignedIntegral>>*\
    \ = nullptr>\n    constexpr static_modint(SignedIntegral value) noexcept\n   \
    \     : base_type{value} {}\n\n    /// @brief \u81EA\u8EAB\u306E\u9006\u6570\u3092\
    \u8FD4\u3057\u307E\u3059\u3002\n    /// @remark \u6642\u9593\u8A08\u7B97\u91CF\
    \uFF1A @f$O(\\log value)@f$\n    /// @return \u81EA\u8EAB\u306E\u9006\u6570\n\
    \    [[nodiscard]]\n    constexpr static_modint inv() const noexcept {\n     \
    \   if constexpr (detail::is_prime32(Mod)) {\n            assert(this->m_value\
    \ != 0 && \"The inverse element of zero does not exist.\");\n            return\
    \ this->pow(Mod - 2);\n        }\n        else {\n            return base_type::inv();\n\
    \        }\n    }\n};\n\n/// @brief \u5B9F\u884C\u6642\u306B\u6CD5\u304C\u6C7A\
    \u307E\u308B\u3068\u304D\u3001\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\
    \u81EA\u52D5\u3067 mod \u3092\u53D6\u308B\u30AF\u30E9\u30B9\n/// @tparam ID \u3053\
    \u306EID\u3054\u3068\u306B\u6CD5\u3092\u8A2D\u5B9A\u3059\u308B\u3053\u3068\u304C\
    \u3067\u304D\u307E\u3059\ntemplate <int ID>\nclass dynamic_modint : public modint_base<dynamic_modint<ID>>\
    \ {\nprivate:\n    using base_type = modint_base<dynamic_modint<ID>>;\n\npublic:\n\
    \    using typename base_type::value_type;\n\n    /// @brief \u6CD5\u3092\u53D6\
    \u5F97\u3057\u307E\u3059\u3002\n    /// @return \u6CD5\n    [[nodiscard]]\n  \
    \  static value_type mod() noexcept {\n        return modulus;\n    }\n\n    ///\
    \ @brief \u6CD5\u3092\u8A2D\u5B9A\u3057\u307E\u3059\u3002\n    /// @param m \u65B0\
    \u3057\u3044\u6CD5\n    static void set_mod(value_type m) noexcept {\n       \
    \ assert(m > 0 && m <= std::numeric_limits<value_type>::max() / 2);\n        modulus\
    \ = m;\n    }\n\n    /// @brief 0 \u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\
    \n    constexpr dynamic_modint() noexcept\n        : base_type{} {}\n\n    ///\
    \ @brief @c value \u306E\u5270\u4F59\u3067\u521D\u671F\u5316\u3057\u307E\u3059\
    \u3002\n    /// @param value \u521D\u671F\u5316\u306B\u4F7F\u3046\u5024\n    template\
    \ <class SignedIntegral, std::enable_if_t<std::is_integral_v<SignedIntegral>>*\
    \ = nullptr>\n    constexpr dynamic_modint(SignedIntegral value) noexcept\n  \
    \      : base_type{value} {}\n\nprivate:\n    inline static value_type modulus\
    \ = 998244353;\n};\n\nusing modint998244353 = static_modint<998244353>;\nusing\
    \ modint1000000007 = static_modint<1000000007>;\nusing modint = dynamic_modint<-1>;\n\
    #line 6 \"test/yukicoder-search-oji.test.cpp\"\n\nusing mint3 = static_modint<57>;\n\
    \nint main() {\n    long long n, m, t;\n    std::cin >> n >> m >> t;\n    \n \
    \   Matrix<modint1000000007> mat1(n, n, 0);\n    Matrix<modint998244353> mat2(n,\
    \ n, 0);\n    Matrix<mint3> mat3(n, n, 0);\n\n    for(int i = 0; i < m; i ++)\
    \ {\n        int a, b;\n        std::cin >> a >> b;\n        mat1[b][a] = 1;\n\
    \        mat2[b][a] = 1;\n        mat3[b][a] = 1;\n    }\n    \n    std::vector<modint1000000007>\
    \ v1(n, 0);\n    std::vector<modint998244353> v2(n, 0);\n    std::vector<mint3>\
    \ v3(n, 0);\n    v1[0] = 1;\n    v2[0] = 1;\n    v3[0] = 1;\n\n    v1 = mat1.pow(t)\
    \ * v1;\n    v2 = mat2.pow(t) * v2;\n    v3 = mat3.pow(t) * v3;\n\n    int ans\
    \ = 0;\n    for(int i = 0; i < n; i ++) {\n        if(v1[i].value() || v2[i].value()\
    \ || v3[i].value()) ans ++;\n    }\n    std::cout << ans << std::endl;\n\n   \
    \ return 0;\n}\n\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1340\"\n\n#include \"\
    ../cpp/matrix.hpp\"\n#include \"../cpp/modint.hpp\"\n#include <iostream>\n\nusing\
    \ mint3 = static_modint<57>;\n\nint main() {\n    long long n, m, t;\n    std::cin\
    \ >> n >> m >> t;\n    \n    Matrix<modint1000000007> mat1(n, n, 0);\n    Matrix<modint998244353>\
    \ mat2(n, n, 0);\n    Matrix<mint3> mat3(n, n, 0);\n\n    for(int i = 0; i < m;\
    \ i ++) {\n        int a, b;\n        std::cin >> a >> b;\n        mat1[b][a]\
    \ = 1;\n        mat2[b][a] = 1;\n        mat3[b][a] = 1;\n    }\n    \n    std::vector<modint1000000007>\
    \ v1(n, 0);\n    std::vector<modint998244353> v2(n, 0);\n    std::vector<mint3>\
    \ v3(n, 0);\n    v1[0] = 1;\n    v2[0] = 1;\n    v3[0] = 1;\n\n    v1 = mat1.pow(t)\
    \ * v1;\n    v2 = mat2.pow(t) * v2;\n    v3 = mat3.pow(t) * v3;\n\n    int ans\
    \ = 0;\n    for(int i = 0; i < n; i ++) {\n        if(v1[i].value() || v2[i].value()\
    \ || v3[i].value()) ans ++;\n    }\n    std::cout << ans << std::endl;\n\n   \
    \ return 0;\n}\n\n"
  dependsOn:
  - cpp/matrix.hpp
  - cpp/modint.hpp
  isVerificationFile: true
  path: test/yukicoder-search-oji.test.cpp
  requiredBy: []
  timestamp: '2023-09-27 09:30:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yukicoder-search-oji.test.cpp
layout: document
redirect_from:
- /verify/test/yukicoder-search-oji.test.cpp
- /verify/test/yukicoder-search-oji.test.cpp.html
title: test/yukicoder-search-oji.test.cpp
---
