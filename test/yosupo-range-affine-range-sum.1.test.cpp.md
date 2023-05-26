---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/lazy-segtree.hpp
    title: "\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
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
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"test/yosupo-range-affine-range-sum.1.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n#include\
    \ <iostream>\n\n#line 2 \"cpp/modint.hpp\"\n\n/**\n * @file modint.hpp\n * @brief\
    \ \u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod \u3092\
    \u53D6\u308B\u30AF\u30E9\u30B9\n */\n\n#line 9 \"cpp/modint.hpp\"\n#include <utility>\n\
    #include <limits>\n#include <type_traits>\n#include <cstdint>\n#include <cassert>\n\
    \nnamespace detail {\n    static constexpr std::uint16_t prime32_bases[] {\n \
    \       15591,  2018,  166, 7429,  8064, 16045, 10503,  4399,  1949,  1295, 2776,\
    \  3620,   560,  3128,  5212,  2657,\n         2300,  2021, 4652, 1471,  9336,\
    \  4018,  2398, 20462, 10277,  8028, 2213,  6219,   620,  3763,  4852,  5012,\n\
    \         3185,  1333, 6227, 5298,  1074,  2391,  5113,  7061,   803,  1269, 3875,\
    \   422,   751,   580,  4729, 10239,\n          746,  2951,  556, 2206,  3778,\
    \   481,  1522,  3476,   481,  2487, 3266,  5633,   488,  3373,  6441,  3344,\n\
    \           17, 15105, 1490, 4154,  2036,  1882,  1813,   467,  3307, 14042, 6371,\
    \   658,  1005,   903,   737,  1887,\n         7447,  1888, 2848, 1784,  7559,\
    \  3400,   951, 13969,  4304,   177,   41, 19875,  3110, 13221,  8726,   571,\n\
    \         7043,  6943, 1199,  352,  6435,   165,  1169,  3315,   978,   233, 3003,\
    \  2562,  2994, 10587, 10030,  2377,\n         1902,  5354, 4447, 1555,   263,\
    \ 27027,  2283,   305,   669,  1912,  601,  6186,   429,  1930, 14873,  1784,\n\
    \         1661,   524, 3577,  236,  2360,  6146,  2850, 55637,  1753,  4178, 8466,\
    \   222,  2579,  2743,  2031,  2226,\n         2276,   374, 2132,  813, 23788,\
    \  1610,  4422,  5159,  1725,  3597, 3366, 14336,   579,   165,  1375, 10018,\n\
    \        12616,  9816, 1371,  536,  1867, 10864,   857,  2206,  5788,   434, 8085,\
    \ 17618,   727,  3639,  1595,  4944,\n         2129,  2029, 8195, 8344,  6232,\
    \  9183,  8126,  1870,  3296,  7455, 8947, 25017,   541, 19115,   368,   566,\n\
    \         5674,   411,  522, 1027,  8215,  2050,  6544, 10049,   614,   774, 2333,\
    \  3007, 35201,  4706,  1152,  1785,\n         1028,  1540, 3743,  493,  4474,\
    \  2521, 26845,  8354,   864, 18915, 5465,  2447,    42,  4511,  1660,   166,\n\
    \         1249,  6259, 2553,  304,   272,  7286,    73,  6554,   899,  2816, 5197,\
    \ 13330,  7054,  2818,  3199,   811,\n          922,   350, 7514, 4452,  3449,\
    \  2663,  4708,   418,  1621,  1171, 3471,    88, 11345,   412,  1559,   194,\n\
    \    };\n\n    static constexpr bool is_SPRP(std::uint32_t n, std::uint32_t a)\
    \ noexcept {\n        std::uint32_t d = n - 1;\n        std::uint32_t s = 0;\n\
    \        while ((d & 1) == 0) {\n            ++s;\n            d >>= 1;\n    \
    \    }\n        std::uint64_t cur = 1;\n        std::uint64_t pw = d;\n      \
    \  while (pw) {\n            if (pw & 1) cur = (cur * a) % n;\n            a =\
    \ (static_cast<std::uint64_t>(a) * a) % n;\n            pw >>= 1;\n        }\n\
    \        if (cur == 1) return true;\n        for (std::uint32_t r = 0; r < s;\
    \ ++r) {\n            if (cur == n - 1) return true;\n            cur = (cur *\
    \ cur) % n;\n        }\n        return false;\n    }\n\n    // 32\u30D3\u30C3\u30C8\
    \u7B26\u53F7\u306A\u3057\u6574\u6570\u306E\u7D20\u6570\u5224\u5B9A\n    // \u53C2\
    \u8003: M. Forisek and J. Jancina, \u201CFast Primality Testing for Integers That\
    \ Fit into a Machine Word,\u201D presented at the Conference on Current Trends\
    \ in Theory and Practice of Informatics, 2015.\n    [[nodiscard]]\n    static\
    \ constexpr bool is_prime32(std::uint32_t x) noexcept {\n        if (x == 2 ||\
    \ x == 3 || x == 5 || x == 7) return true;\n        if (x % 2 == 0 || x % 3 ==\
    \ 0 || x % 5 == 0 || x % 7 == 0) return false;\n        if (x < 121) return (x\
    \ > 1);\n        std::uint64_t h = x;\n        h = ((h >> 16) ^ h) * 0x45d9f3b;\n\
    \        h = ((h >> 16) ^ h) * 0x45d9f3b;\n        h = ((h >> 16) ^ h) & 0xff;\n\
    \        return is_SPRP(x, prime32_bases[h]);\n    }\n}\n\n/// @brief static_modint\
    \ \u3068 dynamic_modint \u306E\u5B9F\u88C5\u3092 CRTP \u306B\u3088\u3063\u3066\
    \u884C\u3046\u305F\u3081\u306E\u30AF\u30E9\u30B9\u30C6\u30F3\u30D7\u30EC\u30FC\
    \u30C8\n/// @tparam Modint \u3053\u306E\u30AF\u30E9\u30B9\u30C6\u30F3\u30D7\u30EC\
    \u30FC\u30C8\u3092\u7D99\u627F\u3059\u308B\u30AF\u30E9\u30B9\ntemplate <class\
    \ Modint>\nclass modint_base {\npublic:\n    /// @brief \u4FDD\u6301\u3059\u308B\
    \u5024\u306E\u578B\n    using value_type = std::uint32_t;\n\n    /// @brief 0\
    \ \u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n    constexpr modint_base()\
    \ noexcept\n        : m_value{ 0 } {}\n\n    /// @brief @c value \u306E\u5270\u4F59\
    \u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n    /// @param value \u521D\u671F\
    \u5316\u306B\u4F7F\u3046\u5024\n    template <class SignedIntegral, std::enable_if_t<std::is_integral_v<SignedIntegral>\
    \ && std::is_signed_v<SignedIntegral>>* = nullptr>\n    constexpr modint_base(SignedIntegral\
    \ value) noexcept\n        : m_value{ static_cast<value_type>((static_cast<long\
    \ long>(value) % Modint::mod() + Modint::mod()) % Modint::mod()) } {}\n\n    ///\
    \ @brief @c value \u306E\u5270\u4F59\u3067\u521D\u671F\u5316\u3057\u307E\u3059\
    \u3002\n    /// @param value \u521D\u671F\u5316\u306B\u4F7F\u3046\u5024\n    template\
    \ <class UnsignedIntegral, std::enable_if_t<std::is_integral_v<UnsignedIntegral>\
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
    \ value_type mod() noexcept {\n        return Mod;\n    }\n\n    using base_type::modint_base;\n\
    \n    /// @brief \u81EA\u8EAB\u306E\u9006\u6570\u3092\u8FD4\u3057\u307E\u3059\u3002\
    \n    /// @remark \u6642\u9593\u8A08\u7B97\u91CF\uFF1A @f$O(\\log value)@f$\n\
    \    /// @return \u81EA\u8EAB\u306E\u9006\u6570\n    [[nodiscard]]\n    constexpr\
    \ static_modint inv() const noexcept {\n        if constexpr (detail::is_prime32(Mod))\
    \ {\n            assert(this->m_value != 0 && \"The inverse element of zero does\
    \ not exist.\");\n            return this->pow(Mod - 2);\n        }\n        else\
    \ {\n            return base_type::inv();\n        }\n    }\n};\n\n/// @brief\
    \ \u5B9F\u884C\u6642\u306B\u6CD5\u304C\u6C7A\u307E\u308B\u3068\u304D\u3001\u56DB\
    \u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod \u3092\u53D6\u308B\
    \u30AF\u30E9\u30B9\n/// @tparam ID \u3053\u306EID\u3054\u3068\u306B\u6CD5\u3092\
    \u8A2D\u5B9A\u3059\u308B\u3053\u3068\u304C\u3067\u304D\u307E\u3059\ntemplate <int\
    \ ID>\nclass dynamic_modint : public modint_base<dynamic_modint<ID>> {\nprivate:\n\
    \    using base_type = modint_base<dynamic_modint<ID>>;\n\npublic:\n    using\
    \ typename base_type::value_type;\n\n    /// @brief \u6CD5\u3092\u53D6\u5F97\u3057\
    \u307E\u3059\u3002\n    /// @return \u6CD5\n    [[nodiscard]]\n    static value_type\
    \ mod() noexcept {\n        return modulus;\n    }\n\n    /// @brief \u6CD5\u3092\
    \u8A2D\u5B9A\u3057\u307E\u3059\u3002\n    /// @param m \u65B0\u3057\u3044\u6CD5\
    \n    static void set_mod(value_type m) noexcept {\n        assert(m > 0 && m\
    \ <= std::numeric_limits<value_type>::max() / 2);\n        modulus = m;\n    }\n\
    \n    using base_type::modint_base;\n\nprivate:\n    inline static value_type\
    \ modulus = 998244353;\n};\n\nusing modint998244353 = static_modint<998244353>;\n\
    using modint1000000007 = static_modint<1000000007>;\nusing modint = dynamic_modint<-1>;\n\
    #line 2 \"cpp/lazy-segtree.hpp\"\n\n/**\n * @file segtree.hpp\n * @brief \u9045\
    \u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n */\n\n#line 9 \"cpp/lazy-segtree.hpp\"\
    \n#include <functional>\n#line 11 \"cpp/lazy-segtree.hpp\"\n#include <ostream>\n\
    #include <vector>\n\n/**\n * @brief \u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\u306ECRTP\u57FA\u5E95\u30AF\u30E9\u30B9\n * \n * @tparam S\
    \ \u5024\u30E2\u30CE\u30A4\u30C9\u306E\u578B\n * @tparam F \u4F5C\u7528\u7D20\u30E2\
    \u30CE\u30A4\u30C9\u306E\u578B\n * @tparam ActualSegTree \u6D3E\u751F\u30AF\u30E9\
    \u30B9\n */\ntemplate <typename S, typename F, typename ActualLazySegTree>\nclass\
    \ LazySegTreeBase {\n    S op(const S& a, const S& b) const { return static_cast<const\
    \ ActualLazySegTree&>(*this).op(a, b); }\n    S e() const { return static_cast<const\
    \ ActualLazySegTree&>(*this).e(); }\n    S mapping(const F& f, const S& x, int\
    \ l, int r) const { return static_cast<const ActualLazySegTree&>(*this).mapping(f,\
    \ x, l, r); }\n    F composition(const F& f, const F& g) const { return static_cast<const\
    \ ActualLazySegTree&>(*this).composition(f, g); }\n    F id() const { return static_cast<const\
    \ ActualLazySegTree&>(*this).id(); }\n\n    int n, sz, height;\n    std::vector<S>\
    \ data;\n    std::vector<F> lazy;\n\n    void update(int k) { data[k] = op(data[2\
    \ * k], data[2 * k + 1]); }\n    void apply_node(int k, int h, const F& f) {\n\
    \        int l = (k << h) & (sz - 1);\n        int r = l + (1 << h);\n       \
    \ data[k] = mapping(f, data[k], l, r);\n        if(k < sz) lazy[k] = composition(f,\
    \ lazy[k]);\n    }\n    void push(int k, int h) {\n        apply_node(2 * k, h-1,\
    \ lazy[k]);\n        apply_node(2 * k + 1, h-1, lazy[k]);\n        lazy[k] = id();\n\
    \    }\n\n    class LazySegTreeReference {\n        LazySegTreeBase& segtree;\n\
    \        int k;\n    public:\n        LazySegTreeReference(LazySegTreeBase& segtree,\
    \ int k) : segtree(segtree), k(k) {}\n        LazySegTreeReference& operator=(const\
    \ S& x) {\n            segtree.set(k, x);\n            return *this;\n       \
    \ }\n        operator S() { return segtree.get(k); }\n    };\n\nprotected:\n \
    \   void construct_data() {\n        sz = 1;\n        height = 0;\n        while\
    \ (sz < n) {\n            sz <<= 1;\n            height++;\n        }\n      \
    \  data.assign(sz * 2, e());\n        lazy.assign(sz * 2, id());\n    }\n    void\
    \ initialize(const std::vector<S>& v) {\n        for (int i = 0; i < n; i++) data[sz\
    \ + i] = v[i];\n        for (int i = sz - 1; i > 0; i--) update(i);\n    }\n\n\
    public:\n    // Warning: \u7D99\u627F\u5148\u306E\u30B3\u30F3\u30B9\u30C8\u30E9\
    \u30AF\u30BF\u3067construct_data()\u3092\u5FC5\u305A\u547C\u3073\u51FA\u3059\uFF01\
    \n    LazySegTreeBase(int n = 0) : n(n) {}\n\n    /**\n     * @brief \u6307\u5B9A\
    \u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u3092\u8FD4\u3059\n     * \n     *\
    \ @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @return S \u5024\n   \
    \  */\n    S get(int k) {\n        k += sz;\n        for(int h = height; h > 0;\
    \ h--) {\n            push(k >> h, h);\n        }\n        return data[k];\n \
    \   }\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u3078\
    \u306E\u53C2\u7167\u3092\u8FD4\u3059\n     * \n     * @param k \n     * @return\
    \ SegTreeReference \u8981\u7D20\u3078\u306E\u53C2\u7167 \u4EE3\u5165\u3055\u308C\
    \u308B\u3068set()\u304C\u547C\u3070\u308C\u308B\n     */\n    LazySegTreeReference\
    \ operator[] (int k) { return LazySegTreeReference(*this, k); }\n\n    /**\n \
    \    * @brief \u5185\u5BB9\u3092\u51FA\u529B\u3059\u308B\n     * \n     * @tparam\
    \ CharT \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u306E\u6587\u5B57\u578B\n \
    \    * @tparam Traits \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u306E\u6587\u5B57\
    \u578B\u7279\u6027\n     * @param os \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\
    \n     * @param rhs \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n     * @return std::basic_ostream<CharT,\
    \ Traits>& \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0 \n     */\n    template\
    \ <class CharT, class Traits>\n    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT,\
    \ Traits>& os, LazySegTreeBase& rhs) {\n        for(int i = 0; i < rhs.n; i++)\
    \ {\n            if(i != 0) os << CharT(' ');\n            os << rhs[i];\n   \
    \     }\n        return os;\n    }\n\n    /**\n     * @brief \u6307\u5B9A\u3055\
    \u308C\u305F\u8981\u7D20\u306E\u5024\u3092x\u306B\u66F4\u65B0\u3059\u308B\n  \
    \   * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @param x\
    \ \u65B0\u3057\u3044\u5024\n     */\n    void set(int k, const S& x) {\n     \
    \   k += sz;\n        for(int h = height; h > 0; h--) {\n            push(k >>\
    \ h, h);\n        }\n        data[k] = x;\n        while(k >>= 1) update(k);\n\
    \    }\n\n    /**\n     * @brief [l, r)\u306E\u533A\u9593\u306E\u7DCF\u7A4D\u3092\
    \u8FD4\u3059\n     * \n     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\
    \n     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @return S\
    \ \u7DCF\u7A4D\n     */\n    S prod(int l, int r) {\n        l += sz; r += sz;\n\
    \        for(int h = height; h > 0; h--) {\n            if(((l >> h) << h) !=\
    \ l) push(l >> h, h);\n            if(((r >> h) << h) != r) push(r >> h, h);\n\
    \        }\n        S left_prod = e(), right_prod = e();\n        while(l < r)\
    \ {\n            if(l & 1) left_prod = op(left_prod, data[l++]);\n           \
    \ if(r & 1) right_prod = op(data[--r], right_prod);\n            l >>= 1; r >>=\
    \ 1;\n        }\n        return op(left_prod, right_prod);\n    }\n    /**\n \
    \    * @brief \u3059\u3079\u3066\u306E\u8981\u7D20\u306E\u7DCF\u7A4D\u3092\u8FD4\
    \u3059\n     * \n     * @return S \u7DCF\u7A4D\n     */\n    S all_prod() const\
    \ { return data[1]; }\n    \n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\
    \u8981\u7D20\u306E\u5024\u306Bx\u3092\u4F5C\u7528\u3055\u305B\u308B\n     * \n\
    \     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @param x \u4F5C\u7528\
    \u7D20\n     */\n    void apply(int k, const F& f) {\n        k += sz;\n     \
    \   for(int h = height; h > 0; h--) {\n            push(k >> h, h);\n        }\n\
    \        data[k] = mapping(f, data[k]);\n        while(k >>= 1) update(k);\n \
    \   }\n    /**\n     * @brief [l, r)\u306E\u533A\u9593\u306E\u5024\u306Bx\u3092\
    \u4F5C\u7528\u3055\u305B\u308B\n     * \n     * @param l \u534A\u958B\u533A\u9593\
    \u306E\u958B\u59CB\n     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\
    \n     * @param f \u4F5C\u7528\u7D20\n     */\n    void apply(int l, int r, const\
    \ F& f) {\n        if(l == r) return;\n        l += sz; r += sz;\n        for(int\
    \ h = height; h > 0; h--) {\n            if(((l >> h) << h) != l) push(l >> h,\
    \ h);\n            if(((r >> h) << h) != r) push(r >> h, h);\n        }\n    \
    \    {\n            int l2 = l, r2 = r;\n            int h = 0;\n            while(l\
    \ < r) {\n                if(l & 1) apply_node(l++, h, f);\n                if(r\
    \ & 1) apply_node(--r, h, f);\n                l >>= 1; r >>= 1;\n           \
    \     h++;\n            }\n            l = l2; r = r2;\n        }\n        for(int\
    \ h = 1; h <= height; h++) {\n            if(((l >> h) << h) != l) update(l >>\
    \ h);\n            if(((r >> h) << h) != r) update((r - 1) >> h);\n        }\n\
    \    }\n\n    /**\n     * @brief (r = l or g(prod([l, r))) = true) and (r = n\
    \ or g(prod([l, r+1))) = false)\u3068\u306A\u308Br\u3092\u8FD4\u3059\n     * g\u304C\
    \u5358\u8ABF\u306A\u3089\u3001g(prod([l, r))) = true\u3068\u306A\u308B\u6700\u5927\
    \u306Er\n     * \n     * @tparam G\n     * @param l \u534A\u958B\u533A\u9593\u306E\
    \u958B\u59CB\n     * @param g \u5224\u5B9A\u95A2\u6570 g(e) = true\n     * @return\
    \ int\n     */\n    template <typename G>\n    int max_right(int l, G g) const\
    \ {\n        assert(g(e()));\n        if(l == n) return n;\n        l += sz;\n\
    \        for(int h = height; h > 0; h--) {\n            push(l >> h, h);\n   \
    \     }\n        S sum = e();\n        int h = 0;\n        while(g(op(sum, data[l])))\
    \ {\n            if(__builtin_clz(l) != __builtin_clz(l+1)) return n;\n      \
    \      sum = op(sum, data[l]);\n            l++;\n            while(l % 2 == 0)\
    \ {\n                l >>= 1;\n                h++;\n            }\n        }\n\
    \        while(l < sz) {\n            push(l, h);\n            if(!g(op(sum, data[l*2])))\
    \ {\n                l = l*2;\n            } else {\n                sum = op(sum,\
    \ data[l*2]);\n                l = l*2+1;\n            }\n            h--;\n \
    \       }\n        return l - sz;\n    }\n    /**\n     * @brief (l = 0 or g(prod([l,\
    \ r))) = true) and (l = r or g(prod([l-1, r))) = false)\u3068\u306A\u308Bl\u3092\
    \u8FD4\u3059\n     * g\u304C\u5358\u8ABF\u306A\u3089\u3001g(prod([l, r))) = true\u3068\
    \u306A\u308B\u6700\u5C0F\u306El\n     * \n     * @tparam G\n     * @param r \u534A\
    \u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @param g \u5224\u5B9A\u95A2\u6570\
    \ g(e) = true\n     * @return int\n     */\n    template <typename G>\n    int\
    \ min_left(int r, G g) const {\n        assert(f(e()));\n        if (r == 0) return\
    \ 0;\n        r += sz - 1;\n        for(int h = height; h > 0; h--) {\n      \
    \      push(r >> h, h);\n        }\n        int h = 0;\n        while(r % 2 ==\
    \ 1) {\n            r >>= 1;\n            h++;\n        }\n        S sum = e();\n\
    \        while(g(op(data[r], sum))) {\n            if(__builtin_clz(r) != __builtin_clz(r-1))\
    \ return 0;\n            sum = op(data[r], sum);\n            r--;\n         \
    \   while(r % 2 == 0) {\n                r >>= 1;\n                h++;\n    \
    \        }\n        }\n        while(r < sz) {\n            push(r, h);\n    \
    \        if(!g(op(data[r*2+1], sum))) {\n                r = r*2+1;\n        \
    \    } else {\n                sum = op(data[r*2+1], sum);\n                r\
    \ = r*2;\n            }\n            h--;\n        }\n        return r - sz +\
    \ 1;\n    }\n};\n\n/**\n * @brief \u30D5\u30A1\u30F3\u30AF\u30BF\u304C\u9759\u7684\
    \u306A\u5834\u5408\u306E\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\
    \u6728\u306E\u5B9F\u88C5\n * \n * @tparam S \u5024\u30E2\u30CE\u30A4\u30C9\u306E\
    \u578B\n * @tparam Op \u5024\u306E\u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n\
    \ * @tparam E \u7A4D\u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\
    \u30AF\u30BF\n * @tparam F \u4F5C\u7528\u7D20\u30E2\u30CE\u30A4\u30C9\u306E\u578B\
    \n * @tparam Mapping \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\u308B\u30D5\u30A1\
    \u30F3\u30AF\u30BF \u5F15\u6570\u306F(\u4F5C\u7528\u7D20, \u5024)\u307E\u305F\u306F\
    (\u4F5C\u7528\u7D20, \u5024, \u30B5\u30A4\u30BA)(\u4F5C\u7528\u7D20, \u5024, \u5DE6\
    \u306E\u5B50, \u53F3\u306E\u5B50)\n * @tparam Composition \u4F5C\u7528\u7D20\u306E\
    \u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam ID \u4F5C\u7528\u7D20\u306E\
    \u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n */\ntemplate\
    \ <typename S, typename Op, typename E, typename F, typename Mapping, typename\
    \ Composition, typename ID>\nclass StaticLazySegTree : public LazySegTreeBase<S,\
    \ F, StaticLazySegTree<S, Op, E, F, Mapping, Composition, ID>> {\n    using BaseType\
    \ = LazySegTreeBase<S, F, StaticLazySegTree<S, Op, E, F, Mapping, Composition,\
    \ ID>>;\n\n    inline static Op operator_object;\n    inline static E identity_object;\n\
    \    inline static Mapping mapping_object;\n    inline static Composition lazy_operator_object;\n\
    \    inline static ID lazy_identity_object;\npublic:\n    S op(const S& a, const\
    \ S& b) const { return operator_object(a, b); }\n    S e() const { return identity_object();\
    \ }\n    S mapping(const F& f, const S& x, int l, int r) const {\n        if constexpr(std::is_invocable_v<Mapping,\
    \ F, S, int, int>) {\n            return mapping_object(f, x, l, r);\n       \
    \ } else if constexpr(std::is_invocable_v<Mapping, F, S, int>) {\n           \
    \ return mapping_object(f, x, r - l);\n        } else {\n            return mapping_object(f,\
    \ x);\n        }\n    }\n    F composition(const F& f, const F& g) const {\n \
    \       return lazy_operator_object(f, g);\n    }\n    F id() const { return lazy_identity_object();\
    \ }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * \n    */\n    StaticLazySegTree() = default;\n\
    \    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n\
    \     * @param n \u8981\u7D20\u6570\n     */\n    explicit StaticLazySegTree(int\
    \ n) : BaseType(n) {\n        this->construct_data();\n    }\n    /**\n     *\
    \ @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param v\
    \ \u521D\u671F\u306E\u8981\u7D20\n     */\n    explicit StaticLazySegTree(const\
    \ std::vector<S>& v) : StaticLazySegTree(v.size()) {\n        this->initialize(v);\n\
    \    }\n};\n\n/**\n * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067\u95A2\
    \u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u4E0E\u3048\u308B\u3053\u3068\
    \u3067\u7A4D\u3092\u5B9A\u7FA9\u3059\u308B\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728\u306E\u5B9F\u88C5\n * \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\
    \u5F15\u6570\u3092\u7701\u7565\u3059\u308B\u3053\u3068\u304C\u3067\u304D\u3001\
    \u30E9\u30E0\u30C0\u5F0F\u304C\u4F7F\u3048\u308B\n * \n * @tparam S \u30E2\u30CE\
    \u30A4\u30C9\u306E\u578B\n * @tparam Op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\u306E\u578B\n * @tparam F \u4F5C\u7528\u7D20\u30E2\u30CE\u30A4\
    \u30C9\u306E\u578B\n * @tparam Mapping \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\
    \u308B\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u306E\u578B\n * @tparam\
    \ Composition \u4F5C\u7528\u7D20\u306E\u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\u306E\u578B\n */\ntemplate <typename S, typename Op, typename\
    \ F, typename Mapping, typename Composition>\nclass LazySegTree : public LazySegTreeBase<S,\
    \ F, LazySegTree<S, Op, F, Mapping, Composition>> {\n    using BaseType = LazySegTreeBase<S,\
    \ F, LazySegTree<S, Op, F, Mapping, Composition>>;\n\n    Op operator_object;\n\
    \    S identity;\n    Mapping mapping_object;\n    Composition lazy_operator_object;\n\
    \    F lazy_identity;\n\npublic:\n    S op(const S& a, const S& b) const { return\
    \ operator_object(a, b); }\n    S e() const { return identity; }\n    S mapping(const\
    \ F& f, const S& x, int l, int r) const {\n        if constexpr(std::is_invocable_v<Mapping,\
    \ F, S, int, int>) {\n            return mapping_object(f, x, l, r);\n       \
    \ } else if constexpr(std::is_invocable_v<Mapping, F, S, int>) {\n           \
    \ return mapping_object(f, x, r - l);\n        } else {\n            return mapping_object(f,\
    \ x);\n        }\n    }\n    F composition(const F& f, const F& g) const {\n \
    \       return lazy_operator_object(f, g);\n    }\n    F id() const { return lazy_identity;\
    \ }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n    */\n    LazySegTree() = default;\n    /**\n    \
    \ * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param\
    \ n \u8981\u7D20\u6570\n     * @param op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\n     * @param identity \u5358\u4F4D\u5143\n     * @param mapping\
    \ \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\u308B\u95A2\u6570\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\n     * @param composition \u4F5C\u7528\u7D20\u306E\u7A4D\u306E\
    \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param lazy_identity\
    \ \u4F5C\u7528\u7D20\u306E\u5358\u4F4D\u5143\n     */\n    explicit LazySegTree(int\
    \ n, Op op, const S& identity, Mapping mapping, Composition composition, const\
    \ F& lazy_identity)\n        : BaseType(n), operator_object(std::move(op)), identity(identity),\
    \ mapping_object(std::move(mapping)),\n        lazy_operator_object(std::move(composition)),\
    \ lazy_identity(lazy_identity) {\n        this->construct_data();\n    }\n   \
    \ /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n   \
    \  * @param v \u521D\u671F\u306E\u8981\u7D20\n     * @param op \u7A4D\u306E\u95A2\
    \u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param identity \u5358\u4F4D\
    \u5143\n     * @param mapping \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\u308B\
    \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param composition \u4F5C\
    \u7528\u7D20\u306E\u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\
    \n     * @param lazy_identity \u4F5C\u7528\u7D20\u306E\u5358\u4F4D\u5143\n   \
    \  */\n    explicit LazySegTree(const std::vector<S>& v, Op op, const S& identity,\
    \ Mapping mapping, Composition composition, const F& lazy_identity)\n        :\
    \ LazySegTree(v.size(), std::move(op), identity, std::move(mapping), std::move(composition),\
    \ lazy_identity) {\n        this->initialize(v);\n    }\n};\n\nnamespace lazy_segtree\
    \ {\n    template <typename S>\n    struct Max {\n        const S operator() (const\
    \ S& a, const S& b) const { return std::max(a, b); }\n    };\n    template <typename\
    \ S>\n    struct Min {\n        const S operator() (const S& a, const S& b) const\
    \ { return std::min(a, b); }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MaxLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::max(); }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MinLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::lowest(); }\n    };\n    template <typename S>\n\
    \    struct AddWithSize {\n        S operator() (const S& f, const S& x, int sz)\
    \ const { return x + f * sz; }\n    };\n    template <typename S>\n    struct\
    \ Zero {\n        S operator() () const { return S(0); }\n    };\n    template\
    \ <typename S, S ID>\n    struct Update {\n        S operator() (const S& f, const\
    \ S& x) const { return f == ID ? x : f; }\n    };\n    template <typename S, S\
    \ ID>\n    struct UpdateWithSize {\n        S operator() (const S& f, const S&\
    \ x, int sz) const { return f == ID ? x : f * sz; }\n    };\n    template <typename\
    \ S, S ID>\n    struct UpdateComposition {\n        S operator() (const S& f,\
    \ const S& g) const { return f == ID ? g : f; }\n    };\n}\n\n/**\n * @brief \u533A\
    \u9593\u6700\u5C0F\u5024\u66F4\u65B0\u3001\u533A\u9593\u6700\u5C0F\u5024\n * \n\
    \ * @tparam S \u578B\n */\ntemplate <typename S>\nusing RChminMinQ = StaticLazySegTree<\n\
    \    S,\n    lazy_segtree::Min<S>,\n    lazy_segtree::MaxLimit<S>,\n    S,\n \
    \   lazy_segtree::Min<S>,\n    lazy_segtree::Min<S>,\n    lazy_segtree::MaxLimit<S>\n\
    >;\n/**\n * @brief \u533A\u9593\u6700\u5927\u5024\u66F4\u65B0\u3001\u533A\u9593\
    \u6700\u5927\u5024\n * \n * @tparam S \u578B\n */\ntemplate <typename S>\nusing\
    \ RChmaxMaxQ = StaticLazySegTree<\n    S,\n    lazy_segtree::Max<S>,\n    lazy_segtree::MinLimit<S>,\n\
    \    S, // F\n    lazy_segtree::Max<S>,\n    lazy_segtree::Max<S>,\n    lazy_segtree::MinLimit<S>\n\
    >;\n/**\n * @brief \u533A\u9593\u52A0\u7B97\u3001\u533A\u9593\u6700\u5C0F\u5024\
    \n * \n * @tparam S \u578B\n */\ntemplate <typename S>\nusing RAddMinQ = StaticLazySegTree<\n\
    \    S, // S\n    lazy_segtree::Min<S>,\n    lazy_segtree::MaxLimit<S>,\n    S,\n\
    \    std::plus<S>,\n    std::plus<S>,\n    lazy_segtree::Zero<S>\n>;\n/**\n *\
    \ @brief \u533A\u9593\u52A0\u7B97\u3001\u533A\u9593\u6700\u5927\u5024\n * \n *\
    \ @tparam S \u578B\n */\ntemplate <typename S>\nusing RAddMaxQ = StaticLazySegTree<\n\
    \    S,\n    lazy_segtree::Max<S>,\n    lazy_segtree::MinLimit<S>,\n    S,\n \
    \   std::plus<S>,\n    std::plus<S>,\n    lazy_segtree::Zero<S>\n>;\n/**\n * @brief\
    \ \u533A\u9593\u52A0\u7B97\u3001\u533A\u9593\u548C\n * \n * @tparam S \u578B\n\
    \ */\ntemplate <typename S>\nusing RAddSumQ = StaticLazySegTree<\n    S,\n   \
    \ std::plus<S>,\n    lazy_segtree::Zero<S>,\n    S,\n    lazy_segtree::AddWithSize<S>,\n\
    \    std::plus<S>,\n    lazy_segtree::Zero<S>\n>;\n/**\n * @brief \u533A\u9593\
    \u5909\u66F4\u3001\u533A\u9593\u6700\u5C0F\u5024\n * \u6CE8\u610F: numeric_limits<S>::max()\u3067\
    \u306E\u66F4\u65B0\u304C\u306A\u3044\u3053\u3068\u3092\u304C\u8981\u4EF6\n * \n\
    \ * @tparam S \u578B\n */\ntemplate <typename S>\nusing RUpdateMinQ = StaticLazySegTree<\n\
    \    S,\n    lazy_segtree::Min<S>,\n    lazy_segtree::MaxLimit<S>,\n    S,\n \
    \   lazy_segtree::Update<S, lazy_segtree::MaxLimit<S>{}()>,\n    lazy_segtree::UpdateComposition<S,\
    \ lazy_segtree::MaxLimit<S>{}()>,\n    lazy_segtree::MaxLimit<S>\n>;\n/**\n *\
    \ @brief \u533A\u9593\u5909\u66F4\u3001\u533A\u9593\u6700\u5927\u5024\n * \u6CE8\
    \u610F: numeric_limits<S>::max()\u3067\u306E\u66F4\u65B0\u304C\u306A\u3044\u3053\
    \u3068\u3092\u304C\u8981\u4EF6\n * \n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RUpdateMaxQ = StaticLazySegTree<\n    S,\n    lazy_segtree::Max<S>,\n\
    \    lazy_segtree::MinLimit<S>,\n    S,\n    lazy_segtree::Update<S, lazy_segtree::MaxLimit<S>{}()>,\n\
    \    lazy_segtree::UpdateComposition<S, lazy_segtree::MaxLimit<S>{}()>,\n    lazy_segtree::MaxLimit<S>\n\
    >;\n/**\n * @brief \u533A\u9593\u5909\u66F4\u3001\u533A\u9593\u548C\n * \u6CE8\
    \u610F: numeric_limits<S>::max()\u3067\u306E\u66F4\u65B0\u304C\u306A\u3044\u3053\
    \u3068\u3092\u304C\u8981\u4EF6\n * \n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RUpdateSumQ = StaticLazySegTree<\n    S,\n    std::plus<S>,\n    lazy_segtree::Zero<S>,\n\
    \    S,\n    lazy_segtree::UpdateWithSize<S, lazy_segtree::MaxLimit<S>{}()>,\n\
    \    lazy_segtree::UpdateComposition<S, lazy_segtree::MaxLimit<S>{}()>,\n    lazy_segtree::MaxLimit<S>\n\
    >;\n#line 7 \"test/yosupo-range-affine-range-sum.1.test.cpp\"\n\nint main(void)\
    \ {\n    int n, q; std::cin >> n >> q;\n    using MI = modint998244353;\n    std::vector<MI>\
    \ a(n);\n    for(int i = 0; i < n; i++) std::cin >> a[i];\n    struct Affine {\
    \ MI a, b; };\n    struct Mapping {\n        MI operator() (const Affine& f, MI\
    \ x, int sz) {\n            return f.a * x + f.b * MI(sz);\n        }\n    };\n\
    \    struct Composition {\n        Affine operator() (const Affine& f, const Affine&\
    \ g) {\n            return {f.a * g.a, f.a * g.b + f.b};\n        }\n    };\n\
    \    struct Id {\n        Affine operator() () {\n            return {1, 0};\n\
    \        }\n    };\n    StaticLazySegTree<MI, std::plus<MI>, lazy_segtree::Zero<MI>,\
    \ Affine, Mapping, Composition, Id> seg(a);\n    while(q--) {\n        int op;\
    \ std::cin >> op;\n        if(op == 0) {\n            int l, r; MI b, c; std::cin\
    \ >> l >> r >> b >> c;\n            seg.apply(l, r, {b, c});\n        } else {\n\
    \            int l, r; std::cin >> l >> r;\n            std::cout << seg.prod(l,\
    \ r) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include <iostream>\n\n#include \"../cpp/modint.hpp\"\n#include \"../cpp/lazy-segtree.hpp\"\
    \n\nint main(void) {\n    int n, q; std::cin >> n >> q;\n    using MI = modint998244353;\n\
    \    std::vector<MI> a(n);\n    for(int i = 0; i < n; i++) std::cin >> a[i];\n\
    \    struct Affine { MI a, b; };\n    struct Mapping {\n        MI operator()\
    \ (const Affine& f, MI x, int sz) {\n            return f.a * x + f.b * MI(sz);\n\
    \        }\n    };\n    struct Composition {\n        Affine operator() (const\
    \ Affine& f, const Affine& g) {\n            return {f.a * g.a, f.a * g.b + f.b};\n\
    \        }\n    };\n    struct Id {\n        Affine operator() () {\n        \
    \    return {1, 0};\n        }\n    };\n    StaticLazySegTree<MI, std::plus<MI>,\
    \ lazy_segtree::Zero<MI>, Affine, Mapping, Composition, Id> seg(a);\n    while(q--)\
    \ {\n        int op; std::cin >> op;\n        if(op == 0) {\n            int l,\
    \ r; MI b, c; std::cin >> l >> r >> b >> c;\n            seg.apply(l, r, {b, c});\n\
    \        } else {\n            int l, r; std::cin >> l >> r;\n            std::cout\
    \ << seg.prod(l, r) << '\\n';\n        }\n    }\n}"
  dependsOn:
  - cpp/modint.hpp
  - cpp/lazy-segtree.hpp
  isVerificationFile: true
  path: test/yosupo-range-affine-range-sum.1.test.cpp
  requiredBy: []
  timestamp: '2023-05-24 09:10:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-range-affine-range-sum.1.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-range-affine-range-sum.1.test.cpp
- /verify/test/yosupo-range-affine-range-sum.1.test.cpp.html
title: test/yosupo-range-affine-range-sum.1.test.cpp
---
