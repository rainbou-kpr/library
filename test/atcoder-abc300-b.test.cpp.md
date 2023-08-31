---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: cpp/matrix.hpp
    title: "\u884C\u5217"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc300/tasks/abc300_b
    links:
    - https://atcoder.jp/contests/abc300/tasks/abc300_b
  bundledCode: "#line 1 \"test/atcoder-abc300-b.test.cpp\"\n#define PROBLEM \"https://atcoder.jp/contests/abc300/tasks/abc300_b\"\
    \n\n#include <iostream>\n\n#line 2 \"cpp/matrix.hpp\"\n\n#include <vector>\n#include\
    \ <string>\n#include <algorithm>\n#include <valarray>\n#include <cassert>\n#include\
    \ <type_traits>\n\nnamespace matrix {\n    template <typename T>\n    struct OperatorPropertyDefault\
    \ {\n        constexpr static T zero = T(0);\n        inline constexpr static\
    \ T add(const T &a, const T &b) { return a + b; }\n        inline constexpr static\
    \ T neg(const T &a) { return -a; }\n        constexpr static T one = T(1);\n \
    \       inline constexpr static T mul(const T &a, const T &b) { return a * b;\
    \ }\n        inline constexpr static T inv(const T &a) { return T(1) / a; }\n\
    \    };\n}\n\n/**\n * @brief \u884C\u5217\n * @tparam T \u578B \u884C\u5217(\u30B0\
    \u30EA\u30C3\u30C9)\u306E\u8981\u7D20\u3068\u306A\u308Bint\u3084char\n * @tparam\
    \ OperatorProperty \u884C\u5217\u306E\u8981\u7D20\u306E\u6F14\u7B97\u3092\u5B9A\
    \u7FA9\u3059\u308B\u69CB\u9020\u4F53 0,1\u3068+,*\u306A\u3089\u7701\u7565\u53EF\
    \n *\n * @note\n * OperatorProperty\u306E\u4F8B\uFF08\u6574\u6570\u306Exor\u3068\
    and\u306B\u3088\u308B\u74B0\uFF09\n * @code\n * struct XorOperatorProperty {\n\
    \ *     constexpr static int zero = 0;\n *     inline constexpr static int add(const\
    \ int &a, const int &b) { return a ^ b; }\n *     inline constexpr static int\
    \ neg(const int &a) { return a; }\n *     constexpr static int one = 0;\n *  \
    \   inline constexpr static int mul(const int &a, const int &b) { return a & b;\
    \ }\n * };\n * @endcode\n * constexpr\u3067\u3042\u308B\u5FC5\u8981\u306F\u306A\
    \u304F\u3001\u307E\u305Finv\u306A\u3069\u4F7F\u308F\u306A\u3044\u3082\u306E\u306F\
    \u5B9A\u7FA9\u3057\u306A\u304F\u3066\u3082\u3088\u3044\uFF08\u5FC5\u8981\u306A\
    \u3082\u306E\u304C\u306A\u304B\u3063\u305F\u3089\u30B3\u30F3\u30D1\u30A4\u30EB\
    \u30A8\u30E9\u30FC\u304C\u767A\u751F\u3059\u308B\uFF09\n */\ntemplate<class T,\
    \ class OperatorProperty = matrix::OperatorPropertyDefault<T>> struct Matrix {\n\
    \    int n, m;\n    std::vector<std::vector<T>> v;\n\n    /**\n     * @brief \u30B3\
    \u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * @param v \u884C\u5217(\u30B0\u30EA\
    \u30C3\u30C9)\u306E\u5143\u3068\u306A\u308B vector<string> \u3084 vector<vector<T>>\n\
    \     * @return Matrix\n     */\n    template <typename Iterable>\n    Matrix(const\
    \ std::vector<Iterable>& v_) noexcept : n(v_.size()), m(v_.size() == 0 ? 0 : v_[0].size())\
    \ {\n        v.resize(n);\n        for(int i = 0; i < n; i++) {\n            v[i].assign(v_[i].begin(),\
    \ v_[i].end());\n        }\n    }\n\n    /**\n     * @brief \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * @param _n \u884C\u5217(\u30B0\u30EA\u30C3\u30C9\
    )\u306E\u884C\u6570\n     * @param _m \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\
    \u5217\u6570\n     * @param _val \u884C\u5217(\u30B0\u30EA\u30C3\u30C9)\u306E\u8981\
    \u7D20\u306E\u521D\u671F\u5024\n     * @return Matrix\n     */\n    Matrix(int\
    \ _n, int _m, T _val = OperatorProperty::zero) : n(_n), m(_m), v(n, std::vector<T>(m,\
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
    \ i < n; i ++) {\n            for(int k = 0; k < p; k ++) {\n                for(int\
    \ j = 0; j < m; j ++) {\n                    C[i][j] = OperatorProperty::add(C[i][j],\
    \ OperatorProperty::mul((*this)[i][k], B[k][j]));\n                }\n       \
    \     }\n        }\n        v.swap(C.v);\n        m = p;\n        return (*this);\n\
    \    }\n\n    /**\n     * @brief \u4FDD\u6301\u3057\u3066\u3044\u308B\u884C\u5217\
    \u306Ek\u4E57\u3092\u6C42\u3081\u308B\n     * @param k \u6307\u6570\n     * @return\
    \ Matrix\n    */\n    [[nodiscard]]\n    Matrix pow(long long k) {\n        Matrix<T>\
    \ A = *this, B(n, n);\n        for(int i = 0; i < n; i ++) B[i][i] = OperatorProperty::one;\n\
    \        while(k > 0) {\n            if(k & 1) B *= A;\n            A *= A;\n\
    \            k >>= 1;\n        }\n        return B;\n    }\n\n    [[nodiscard]]\n\
    \    Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }\n\
    \    [[nodiscard]]\n    Matrix operator-(const Matrix &B) const { return (Matrix(*this)\
    \ -= B); }\n    [[nodiscard]]\n    Matrix operator*(const Matrix &B) const { return\
    \ (Matrix(*this) *= B); }\n\n    /**\n     * @brief \u884C\u5217A\u3068\u5217\u30D9\
    \u30AF\u30C8\u30EBB\u306E\u7A4D\n     * @param A Matrix<T>\n     * @param B vector<T>\n\
    \     * @return vector<T> \u5217\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n\
    \    friend std::vector<T> operator*(const Matrix &A, const std::vector<T> &B)\
    \ {\n        std::vector<T> ret(A.n, 0);\n        for(int i = 0; i < A.n; i ++)\
    \ {\n            for(int j = 0; j < A.m; j ++) {\n                ret[i] = OperatorProperty::add(ret[i],\
    \ OperatorProperty::mul(A[i][j], B[j]));\n            }\n        }\n        return\
    \ ret;\n    }\n\n    /**\n     * @brief \u884C\u30D9\u30AF\u30C8\u30EBA\u3068\u884C\
    \u5217B\u306E\u7A4D\n     * @param A vector<T>\n     * @param B Matrix<T>\n  \
    \   * @return vector<T> \u884C\u30D9\u30AF\u30C8\u30EB\n    */\n    [[nodiscard]]\n\
    \    friend std::vector<T> operator*(const std::vector<T> &A, const Matrix &B)\
    \ {\n        std::vector<T> ret(B.m, 0);\n        for(int i = 0; i < B.n; i ++)\
    \ {\n            for(int j = 0; j < B.m; j ++) {\n                ret[j] = OperatorProperty::add(ret[j],\
    \ OperatorProperty::mul(A[i], B[i][j]));\n            }\n        }\n        return\
    \ ret;\n    }\n\n    /**\n     * @brief \u884C\u5217\u5F0F\n     * @return \u884C\
    \u5217\u5F0F\n     *\n     * @note\n     * OperatorProperty\u304C\u30C7\u30D5\u30A9\
    \u30EB\u30C8\u3067\u3042\u308B\u5834\u5408\u306E\u307F\u6709\u52B9\n    */\n \
    \   template <std::enable_if_t<std::is_same_v<OperatorProperty, matrix::OperatorPropertyDefault<T>>,\
    \ bool> = true>\n    [[nodiscard]]\n    T det() {\n        assert(n == m);\n \
    \       if(n == 0) return T(1);\n        T ans = T(1);\n        std::vector A(n,\
    \ std::valarray(T(0), n));\n        for(int i = 0; i < n; i ++) for(int j = 0;\
    \ j < n; j ++) A[i][j] = this->v[i][j];\n        for(int i = 0; i < n; i ++) {\n\
    \            if constexpr(std::is_floating_point_v<T>) {\n                int\
    \ pivot = i;\n                for(int j = i + 1; j < n; j ++) if(std::abs(A[j][i])\
    \ > std::abs(A[pivot][i])) pivot = j;\n                if(pivot != i) {\n    \
    \                std::swap(A[i], A[pivot]);\n                    ans *= -1;\n\
    \                }\n                if(std::abs(A[i][i]) < 1e-9) return 0;\n \
    \           } else {\n                if(A[i][i] == T(0)) {\n                \
    \    for(int j = i + 1; j < n; j ++) if(A[j][i] != T(0)) {\n                 \
    \       std::swap(A[i], A[j]);\n                        ans *= -T(1);\n      \
    \                  break;\n                    }\n                    if(A[i][i]\
    \ == T(0)) return 0;\n                }\n            }\n            ans *= A[i][i];\n\
    \            A[i] /= A[i][i];\n            for(int j = i + 1; j < n; j ++) A[j]\
    \ -= A[i] * A[j][i];\n        }\n        return ans;\n    }\n};\n#line 6 \"test/atcoder-abc300-b.test.cpp\"\
    \n\nint main(void) {\n    int h, w; std::cin >> h >> w;\n    std::vector<std::string>\
    \ a(h), b(h);\n    for(int i = 0; i < h; i ++) {\n        std::cin >> a[i];\n\
    \    }\n    for(int i = 0; i < h; i ++) {\n        std::cin >> b[i];\n    }\n\
    \    Matrix<char> A(a), B(b);\n    for(int i = 0; i < h; i ++) {\n        for(int\
    \ j = 0; j < w; j ++) {\n            if(A.shift(i, j) == B) {\n              \
    \  std::cout << \"Yes\" << std::endl;\n                return 0;\n           \
    \ }\n        }\n    }\n    std::cout << \"No\" << std::endl;\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc300/tasks/abc300_b\"\n\n\
    #include <iostream>\n\n#include \"../cpp/matrix.hpp\"\n\nint main(void) {\n  \
    \  int h, w; std::cin >> h >> w;\n    std::vector<std::string> a(h), b(h);\n \
    \   for(int i = 0; i < h; i ++) {\n        std::cin >> a[i];\n    }\n    for(int\
    \ i = 0; i < h; i ++) {\n        std::cin >> b[i];\n    }\n    Matrix<char> A(a),\
    \ B(b);\n    for(int i = 0; i < h; i ++) {\n        for(int j = 0; j < w; j ++)\
    \ {\n            if(A.shift(i, j) == B) {\n                std::cout << \"Yes\"\
    \ << std::endl;\n                return 0;\n            }\n        }\n    }\n\
    \    std::cout << \"No\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - cpp/matrix.hpp
  isVerificationFile: true
  path: test/atcoder-abc300-b.test.cpp
  requiredBy: []
  timestamp: '2023-08-28 17:11:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/atcoder-abc300-b.test.cpp
layout: document
redirect_from:
- /verify/test/atcoder-abc300-b.test.cpp
- /verify/test/atcoder-abc300-b.test.cpp.html
title: test/atcoder-abc300-b.test.cpp
---