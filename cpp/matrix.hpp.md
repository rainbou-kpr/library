---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yukicoder-rotate-enlarge_1.test.cpp
    title: test/yukicoder-rotate-enlarge_1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder-rotate-enlarge_2.test.cpp
    title: test/yukicoder-rotate-enlarge_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder-search-oji.test.cpp
    title: test/yukicoder-search-oji.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u884C\u5217"
    links: []
  bundledCode: "#line 2 \"cpp/matrix.hpp\"\n\n#include <vector>\n#include <string>\n\
    #include <algorithm>\n\n/**\n * @brief \u884C\u5217\n * @tparam T \u578B \u884C\
    \u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u8981\u7D20\u3068\u306A\u308Bint\u3084\
    char\n */\ntemplate<class T> struct Matrix {\n    int n, m;\n    std::vector<std::vector<T>>\
    \ v;\n\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n  \
    \   * @param v \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u5143\u3068\u306A\u308B\
    \ vector<string> \u3084 vector<vector<T>>\n     * @return Matrix\n     */\n  \
    \  template <typename Iterable>\n    constexpr Matrix(const std::vector<Iterable>&\
    \ v_) noexcept : n(v_.size()), m(v_.size() == 0 ? 0 : v_[0].size()) {\n      \
    \  v.resize(n);\n        for(int i = 0; i < n; i++) {\n            v[i].assign(v_[i].begin(),\
    \ v_[i].end());\n        }\n    }\n\n    /**\n     * @brief \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * @param _n \u884C\u5217(\u30B0\u30EA\u30C3\u30C9\
    )\u306E\u884C\u6570\n     * @param _m \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\
    \u5217\u6570\n     * @param _val \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u8981\
    \u7D20\u306E\u521D\u671F\u5024\n     * @return Matrix\n     */\n    constexpr\
    \ Matrix(int _n, int _m, T _val = T()) : n(_n), m(_m), v(n, std::vector<T>(m,\
    \ _val)) {}\n    \n    constexpr auto begin() noexcept {return v.begin();}\n \
    \   constexpr auto end() noexcept {return v.end();}\n\n    /**\n     * @brief\
    \ \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u884C\u6570\n     * @return size_t\n\
    \     */\n    [[nodiscard]]\n    constexpr size_t size() const {return v.size();}\n\
    \n    std::vector<T>& operator [] (int i) {return v[i];}\n    const std::vector<T>&\
    \ operator [] (int i) const {return v[i];}\n    constexpr Matrix<T>& operator\
    \ = (const std::vector<std::vector<T>> &A) noexcept {\n        n = A.size();\n\
    \        m = (n == 0 ? 0 : A[0].size());\n        v = A;\n        return *this;\n\
    \    }\n\n    /**\n     * @brief \u8EE2\u7F6E\n     * @return Matrix\n     */\n\
    \    [[nodiscard]]\n    constexpr Matrix transpose() noexcept {\n        if(n\
    \ == 0) return Matrix(v);\n        std::vector<std::vector<T>> ret(m);\n     \
    \   for(int i = 0; i < m; i ++) {\n            ret[i].resize(n);\n           \
    \ for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];\n        }\n        return\
    \ Matrix(ret);\n    }\n\n    /**\n     * @brief \u5DE6\u53F3\u53CD\u8EE2\n   \
    \  * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr Matrix rev_lr()\
    \ noexcept {\n        std::vector<std::vector<T>> ret = v;\n        for(int i\
    \ = 0; i < n; i ++) std::reverse(ret[i].begin(), ret[i].end());\n        return\
    \ Matrix(ret);\n    }\n\n    /**\n     * @brief \u4E0A\u4E0B\u53CD\u8EE2\n   \
    \  * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr Matrix rev_ud()\
    \ noexcept {\n        std::vector<std::vector<T>> ret = v;\n        reverse(ret.begin(),\
    \ ret.end());\n        return Matrix(ret);\n    }\n\n    /**\n     * @brief \u6642\
    \u8A08\u5468\u308A\u306B90\u5EA6\u56DE\u8EE2\n     * @param k \u56DE\u8EE2\u3059\
    \u308B\u56DE\u6570\n     * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr\
    \ Matrix rotate(int k) noexcept {\n        k %= 4;\n        if(k == 0) return\
    \ *this;\n        if(k < 0) k += 4;\n        if(k == 2) return this->rev_lr().rev_ud();\n\
    \        std::vector<std::vector<T>> ret(m);\n        if(k == 1) {\n         \
    \   for(int i = 0; i < m; i ++) {\n                ret[i].resize(n);\n       \
    \         for(int j = 0; j < n; j ++) ret[i][j] = v[n - j - 1][i];\n         \
    \   }\n        } else {\n            for(int i = 0; i < m; i ++) {\n         \
    \       ret[i].resize(n);\n                for(int j = 0; j < n; j ++) ret[i][j]\
    \ = v[j][m - i - 1];\n            }\n        }\n        return Matrix(ret);\n\
    \    }\n\n    /**\n     * @brief (i, j)\u3092((i + dy) mod n, (j + dx) mod m)\u306B\
    \u79FB\u52D5\n     * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr\
    \ Matrix shift(int dy, int dx) noexcept {\n        std::vector<std::vector<T>>\
    \ ret = v;\n        for(int i = 0, ni = dy; i < n; i ++, ni ++) {\n          \
    \  if(ni >= n) ni = 0;\n            for(int j = 0, nj = dx; j < m; j ++, nj ++)\
    \ {\n                if(nj >= m) nj = 0;\n                ret[ni][nj] = v[i][j];\n\
    \            }\n        }\n        return Matrix(ret);\n    }\n\n    /**\n   \
    \  * @brief \u5DE6\u306Bk\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n   \
    \  */\n    [[nodiscard]]\n    constexpr Matrix shift_l(int k) noexcept {\n   \
    \     return this->shift(0, -k);\n    }\n\n    /**\n     * @brief \u53F3\u306B\
    k\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n     */\n    [[nodiscard]]\n\
    \    constexpr Matrix shift_r(int k) noexcept {\n        return this->shift(0,\
    \ k);\n    }\n\n    /**\n     * @brief \u4E0A\u306Bk\u56DE\u30B7\u30D5\u30C8\n\
    \     * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr Matrix shift_u(int\
    \ k) noexcept {\n        return this->shift(-k, 0);\n    }\n\n    /**\n     *\
    \ @brief \u4E0B\u306Bk\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n     */\n\
    \    [[nodiscard]]\n    constexpr Matrix shift_d(int k) noexcept {\n        return\
    \ this->shift(k, 0);\n    }\n\n    /**\n     * @brief \u30B0\u30EA\u30C3\u30C9\
    \u3092vector<string>\u3067\u8FD4\u3059\n     * @return std::vector<std::string>\n\
    \     */\n    [[nodiscard]]\n    constexpr std::vector<std::string> vstr() noexcept\
    \ {\n        std::vector<std::string> ret(n);\n        for(int i = 0; i < n; i\
    \ ++) {\n            ret[i].assign(v[i].begin(), v[i].end());\n        }\n   \
    \     return ret;\n    }\n\n    /**\n     * @brief \u30B0\u30EA\u30C3\u30C9\u306E\
    j\u5217\u76EE\u3092\u8FD4\u3059\n     * @param j \u8FD4\u3059\u5217\u756A\u53F7\
    (0-indexed)\n     * @return std::vector<T>\n     */\n    [[nodiscard]]\n    constexpr\
    \ std::vector<T> col(int j) noexcept {\n        std::vector<T> ret(n);\n     \
    \   for(int i = 0; i < n; i ++) {\n            ret[i] = v[i][j];\n        }\n\
    \        return ret;\n    }\n\n    /**\n     * @brief \u30B0\u30EA\u30C3\u30C9\
    \u306Ei\u884C\u76EE\u3092string\u3067\u8FD4\u3059\n     * @param i \u8FD4\u3059\
    \u884C\u756A\u53F7(0-indexed)\n     * @return std::string\n     */\n    [[nodiscard]]\n\
    \    constexpr std::string str(int i) noexcept {\n        std::string ret;\n \
    \       ret.assign(v[i].begin(), v[i].end());\n        return ret;\n    }\n  \
    \  /**\n     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u884C\u5217\u306B\u884C\
    \u5217B\u3092\u8DB3\u3059\n     * @param B \u8DB3\u3059\u884C\u5217\n     * @return\
    \ @c *this\n    */\n    constexpr Matrix &operator+=(const Matrix &B) {\n    \
    \    if(n == 0) return (*this);\n        assert(n == B.size() && m == B[0].size());\n\
    \        for(int i = 0; i < n; i++)\n            for(int j = 0; j < m; j++) (*this)[i][j]\
    \ += B[i][j];\n        return (*this);\n    }\n    /**\n     * @brief \u4FDD\u6301\
    \u3057\u3066\u3044\u308B\u884C\u5217\u304B\u3089\u884C\u5217B\u3092\u5F15\u304F\
    \n     * @param B \u5F15\u304F\u884C\u5217\n     * @return @c *this\n    */\n\
    \    constexpr Matrix &operator-=(const Matrix &B) {\n        if(n == 0) return\
    \ (*this);\n        assert(n == B.size() && m == B[0].size());\n        for(int\
    \ i = 0; i < n; i++)\n            for(int j = 0; j < m; j++) (*this)[i][j] -=\
    \ B[i][j];\n        return (*this);\n    }\n\n    /**\n     * @brief \u4FDD\u6301\
    \u3057\u3066\u3044\u308B\u884C\u5217\u306B\u884C\u5217B\u3092\u639B\u3051\u308B\
    \n     * @param B \u639B\u3051\u308B\u884C\u5217\n     * @return @c *this\n  \
    \  */\n    constexpr Matrix &operator*=(const Matrix &B) {\n        int p = B[0].size();\n\
    \        Matrix<T> C(n, p);\n        for(int i = 0; i < n; i ++) {\n         \
    \   for(int k = 0; k < p; k ++) {\n                for(int j = 0; j < m; j ++)\
    \ {\n                    C[i][j] += (*this)[i][k] * B[k][j];\n               \
    \ }\n            }\n        }\n        v.swap(C.v);\n        m = p;\n        return\
    \ (*this);\n    }\n\n    /**\n     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\
    \u884C\u5217\u306Ek\u4E57\u3092\u6C42\u3081\u308B\n     * @param k \u6307\u6570\
    \n     * @return Matrix\n    */\n    [[nodiscard]]\n    constexpr Matrix pow(long\
    \ long k) {\n        Matrix<T> A = *this, B(n, n);\n        for(int i = 0; i <\
    \ n; i ++) B[i][i] = 1;\n        while(k > 0) {\n            if(k & 1) B *= A;\n\
    \            A *= A;\n            k >>= 1;\n        }\n        return B;\n   \
    \ }\n\n    [[nodiscard]]\n    constexpr Matrix operator+(const Matrix &B) const\
    \ { return (Matrix(*this) += B); }\n    [[nodiscard]]\n    constexpr Matrix operator-(const\
    \ Matrix &B) const { return (Matrix(*this) -= B); }\n    [[nodiscard]]\n    constexpr\
    \ Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }\n\n\
    \    /**\n     * @brief \u884C\u5217A\u3068\u5217\u30D9\u30AF\u30C8\u30EBB\u306E\
    \u7A4D\n     * @param A Matrix<T>\n     * @param B vector<T>\n     * @return vector<T>\
    \ \u5217\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n    constexpr friend\
    \ std::vector<T> operator*(const Matrix &A, const std::vector<T> &B) {\n     \
    \   std::vector<T> ret(A.n, 0);\n        for(int i = 0; i < A.n; i ++) {\n   \
    \         for(int j = 0; j < A.m; j ++) {\n                ret[i] += A[i][j] *\
    \ B[j];\n            }\n        }\n        return ret;\n    }\n\n    /**\n   \
    \  * @brief \u884C\u30D9\u30AF\u30C8\u30EBA\u3068\u884C\u5217B\u306E\u7A4D\n \
    \    * @param A vector<T>\n     * @param B Matrix<T>\n     * @return vector<T>\
    \ \u884C\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n    constexpr friend\
    \ std::vector<T> operator*(const std::vector<T> &A, const Matrix &B) {\n     \
    \   std::vector<T> ret(B.m, 0);\n        for(int i = 0; i < B.n; i ++) {\n   \
    \         for(int j = 0; j < B.m; j ++) {\n                ret[j] += A[i] * B[i][j];\n\
    \            }\n        }\n        return ret;\n    }\n};\n"
  code: "#pragma once\n\n#include <vector>\n#include <string>\n#include <algorithm>\n\
    \n/**\n * @brief \u884C\u5217\n * @tparam T \u578B \u884C\u5217(\u30B0\u30EA\u30C3\
    \u30C9)\u306E\u8981\u7D20\u3068\u306A\u308Bint\u3084char\n */\ntemplate<class\
    \ T> struct Matrix {\n    int n, m;\n    std::vector<std::vector<T>> v;\n\n  \
    \  /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * @param\
    \ v \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u5143\u3068\u306A\u308B vector<string>\
    \ \u3084 vector<vector<T>>\n     * @return Matrix\n     */\n    template <typename\
    \ Iterable>\n    constexpr Matrix(const std::vector<Iterable>& v_) noexcept :\
    \ n(v_.size()), m(v_.size() == 0 ? 0 : v_[0].size()) {\n        v.resize(n);\n\
    \        for(int i = 0; i < n; i++) {\n            v[i].assign(v_[i].begin(),\
    \ v_[i].end());\n        }\n    }\n\n    /**\n     * @brief \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * @param _n \u884C\u5217(\u30B0\u30EA\u30C3\u30C9\
    )\u306E\u884C\u6570\n     * @param _m \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\
    \u5217\u6570\n     * @param _val \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u8981\
    \u7D20\u306E\u521D\u671F\u5024\n     * @return Matrix\n     */\n    constexpr\
    \ Matrix(int _n, int _m, T _val = T()) : n(_n), m(_m), v(n, std::vector<T>(m,\
    \ _val)) {}\n    \n    constexpr auto begin() noexcept {return v.begin();}\n \
    \   constexpr auto end() noexcept {return v.end();}\n\n    /**\n     * @brief\
    \ \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u884C\u6570\n     * @return size_t\n\
    \     */\n    [[nodiscard]]\n    constexpr size_t size() const {return v.size();}\n\
    \n    std::vector<T>& operator [] (int i) {return v[i];}\n    const std::vector<T>&\
    \ operator [] (int i) const {return v[i];}\n    constexpr Matrix<T>& operator\
    \ = (const std::vector<std::vector<T>> &A) noexcept {\n        n = A.size();\n\
    \        m = (n == 0 ? 0 : A[0].size());\n        v = A;\n        return *this;\n\
    \    }\n\n    /**\n     * @brief \u8EE2\u7F6E\n     * @return Matrix\n     */\n\
    \    [[nodiscard]]\n    constexpr Matrix transpose() noexcept {\n        if(n\
    \ == 0) return Matrix(v);\n        std::vector<std::vector<T>> ret(m);\n     \
    \   for(int i = 0; i < m; i ++) {\n            ret[i].resize(n);\n           \
    \ for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];\n        }\n        return\
    \ Matrix(ret);\n    }\n\n    /**\n     * @brief \u5DE6\u53F3\u53CD\u8EE2\n   \
    \  * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr Matrix rev_lr()\
    \ noexcept {\n        std::vector<std::vector<T>> ret = v;\n        for(int i\
    \ = 0; i < n; i ++) std::reverse(ret[i].begin(), ret[i].end());\n        return\
    \ Matrix(ret);\n    }\n\n    /**\n     * @brief \u4E0A\u4E0B\u53CD\u8EE2\n   \
    \  * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr Matrix rev_ud()\
    \ noexcept {\n        std::vector<std::vector<T>> ret = v;\n        reverse(ret.begin(),\
    \ ret.end());\n        return Matrix(ret);\n    }\n\n    /**\n     * @brief \u6642\
    \u8A08\u5468\u308A\u306B90\u5EA6\u56DE\u8EE2\n     * @param k \u56DE\u8EE2\u3059\
    \u308B\u56DE\u6570\n     * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr\
    \ Matrix rotate(int k) noexcept {\n        k %= 4;\n        if(k == 0) return\
    \ *this;\n        if(k < 0) k += 4;\n        if(k == 2) return this->rev_lr().rev_ud();\n\
    \        std::vector<std::vector<T>> ret(m);\n        if(k == 1) {\n         \
    \   for(int i = 0; i < m; i ++) {\n                ret[i].resize(n);\n       \
    \         for(int j = 0; j < n; j ++) ret[i][j] = v[n - j - 1][i];\n         \
    \   }\n        } else {\n            for(int i = 0; i < m; i ++) {\n         \
    \       ret[i].resize(n);\n                for(int j = 0; j < n; j ++) ret[i][j]\
    \ = v[j][m - i - 1];\n            }\n        }\n        return Matrix(ret);\n\
    \    }\n\n    /**\n     * @brief (i, j)\u3092((i + dy) mod n, (j + dx) mod m)\u306B\
    \u79FB\u52D5\n     * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr\
    \ Matrix shift(int dy, int dx) noexcept {\n        std::vector<std::vector<T>>\
    \ ret = v;\n        for(int i = 0, ni = dy; i < n; i ++, ni ++) {\n          \
    \  if(ni >= n) ni = 0;\n            for(int j = 0, nj = dx; j < m; j ++, nj ++)\
    \ {\n                if(nj >= m) nj = 0;\n                ret[ni][nj] = v[i][j];\n\
    \            }\n        }\n        return Matrix(ret);\n    }\n\n    /**\n   \
    \  * @brief \u5DE6\u306Bk\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n   \
    \  */\n    [[nodiscard]]\n    constexpr Matrix shift_l(int k) noexcept {\n   \
    \     return this->shift(0, -k);\n    }\n\n    /**\n     * @brief \u53F3\u306B\
    k\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n     */\n    [[nodiscard]]\n\
    \    constexpr Matrix shift_r(int k) noexcept {\n        return this->shift(0,\
    \ k);\n    }\n\n    /**\n     * @brief \u4E0A\u306Bk\u56DE\u30B7\u30D5\u30C8\n\
    \     * @return Matrix\n     */\n    [[nodiscard]]\n    constexpr Matrix shift_u(int\
    \ k) noexcept {\n        return this->shift(-k, 0);\n    }\n\n    /**\n     *\
    \ @brief \u4E0B\u306Bk\u56DE\u30B7\u30D5\u30C8\n     * @return Matrix\n     */\n\
    \    [[nodiscard]]\n    constexpr Matrix shift_d(int k) noexcept {\n        return\
    \ this->shift(k, 0);\n    }\n\n    /**\n     * @brief \u30B0\u30EA\u30C3\u30C9\
    \u3092vector<string>\u3067\u8FD4\u3059\n     * @return std::vector<std::string>\n\
    \     */\n    [[nodiscard]]\n    constexpr std::vector<std::string> vstr() noexcept\
    \ {\n        std::vector<std::string> ret(n);\n        for(int i = 0; i < n; i\
    \ ++) {\n            ret[i].assign(v[i].begin(), v[i].end());\n        }\n   \
    \     return ret;\n    }\n\n    /**\n     * @brief \u30B0\u30EA\u30C3\u30C9\u306E\
    j\u5217\u76EE\u3092\u8FD4\u3059\n     * @param j \u8FD4\u3059\u5217\u756A\u53F7\
    (0-indexed)\n     * @return std::vector<T>\n     */\n    [[nodiscard]]\n    constexpr\
    \ std::vector<T> col(int j) noexcept {\n        std::vector<T> ret(n);\n     \
    \   for(int i = 0; i < n; i ++) {\n            ret[i] = v[i][j];\n        }\n\
    \        return ret;\n    }\n\n    /**\n     * @brief \u30B0\u30EA\u30C3\u30C9\
    \u306Ei\u884C\u76EE\u3092string\u3067\u8FD4\u3059\n     * @param i \u8FD4\u3059\
    \u884C\u756A\u53F7(0-indexed)\n     * @return std::string\n     */\n    [[nodiscard]]\n\
    \    constexpr std::string str(int i) noexcept {\n        std::string ret;\n \
    \       ret.assign(v[i].begin(), v[i].end());\n        return ret;\n    }\n  \
    \  /**\n     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u884C\u5217\u306B\u884C\
    \u5217B\u3092\u8DB3\u3059\n     * @param B \u8DB3\u3059\u884C\u5217\n     * @return\
    \ @c *this\n    */\n    constexpr Matrix &operator+=(const Matrix &B) {\n    \
    \    if(n == 0) return (*this);\n        assert(n == B.size() && m == B[0].size());\n\
    \        for(int i = 0; i < n; i++)\n            for(int j = 0; j < m; j++) (*this)[i][j]\
    \ += B[i][j];\n        return (*this);\n    }\n    /**\n     * @brief \u4FDD\u6301\
    \u3057\u3066\u3044\u308B\u884C\u5217\u304B\u3089\u884C\u5217B\u3092\u5F15\u304F\
    \n     * @param B \u5F15\u304F\u884C\u5217\n     * @return @c *this\n    */\n\
    \    constexpr Matrix &operator-=(const Matrix &B) {\n        if(n == 0) return\
    \ (*this);\n        assert(n == B.size() && m == B[0].size());\n        for(int\
    \ i = 0; i < n; i++)\n            for(int j = 0; j < m; j++) (*this)[i][j] -=\
    \ B[i][j];\n        return (*this);\n    }\n\n    /**\n     * @brief \u4FDD\u6301\
    \u3057\u3066\u3044\u308B\u884C\u5217\u306B\u884C\u5217B\u3092\u639B\u3051\u308B\
    \n     * @param B \u639B\u3051\u308B\u884C\u5217\n     * @return @c *this\n  \
    \  */\n    constexpr Matrix &operator*=(const Matrix &B) {\n        int p = B[0].size();\n\
    \        Matrix<T> C(n, p);\n        for(int i = 0; i < n; i ++) {\n         \
    \   for(int k = 0; k < p; k ++) {\n                for(int j = 0; j < m; j ++)\
    \ {\n                    C[i][j] += (*this)[i][k] * B[k][j];\n               \
    \ }\n            }\n        }\n        v.swap(C.v);\n        m = p;\n        return\
    \ (*this);\n    }\n\n    /**\n     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\
    \u884C\u5217\u306Ek\u4E57\u3092\u6C42\u3081\u308B\n     * @param k \u6307\u6570\
    \n     * @return Matrix\n    */\n    [[nodiscard]]\n    constexpr Matrix pow(long\
    \ long k) {\n        Matrix<T> A = *this, B(n, n);\n        for(int i = 0; i <\
    \ n; i ++) B[i][i] = 1;\n        while(k > 0) {\n            if(k & 1) B *= A;\n\
    \            A *= A;\n            k >>= 1;\n        }\n        return B;\n   \
    \ }\n\n    [[nodiscard]]\n    constexpr Matrix operator+(const Matrix &B) const\
    \ { return (Matrix(*this) += B); }\n    [[nodiscard]]\n    constexpr Matrix operator-(const\
    \ Matrix &B) const { return (Matrix(*this) -= B); }\n    [[nodiscard]]\n    constexpr\
    \ Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }\n\n\
    \    /**\n     * @brief \u884C\u5217A\u3068\u5217\u30D9\u30AF\u30C8\u30EBB\u306E\
    \u7A4D\n     * @param A Matrix<T>\n     * @param B vector<T>\n     * @return vector<T>\
    \ \u5217\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n    constexpr friend\
    \ std::vector<T> operator*(const Matrix &A, const std::vector<T> &B) {\n     \
    \   std::vector<T> ret(A.n, 0);\n        for(int i = 0; i < A.n; i ++) {\n   \
    \         for(int j = 0; j < A.m; j ++) {\n                ret[i] += A[i][j] *\
    \ B[j];\n            }\n        }\n        return ret;\n    }\n\n    /**\n   \
    \  * @brief \u884C\u30D9\u30AF\u30C8\u30EBA\u3068\u884C\u5217B\u306E\u7A4D\n \
    \    * @param A vector<T>\n     * @param B Matrix<T>\n     * @return vector<T>\
    \ \u884C\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n    constexpr friend\
    \ std::vector<T> operator*(const std::vector<T> &A, const Matrix &B) {\n     \
    \   std::vector<T> ret(B.m, 0);\n        for(int i = 0; i < B.n; i ++) {\n   \
    \         for(int j = 0; j < B.m; j ++) {\n                ret[j] += A[i] * B[i][j];\n\
    \            }\n        }\n        return ret;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: cpp/matrix.hpp
  requiredBy: []
  timestamp: '2023-05-24 13:53:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder-search-oji.test.cpp
  - test/yukicoder-rotate-enlarge_1.test.cpp
  - test/yukicoder-rotate-enlarge_2.test.cpp
documentation_of: cpp/matrix.hpp
layout: document
redirect_from:
- /library/cpp/matrix.hpp
- /library/cpp/matrix.hpp.html
title: "\u884C\u5217"
---
