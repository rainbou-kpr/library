---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: cpp/modint.hpp
    title: "\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod\
      \ \u3092\u53D6\u308B\u30AF\u30E9\u30B9"
  - icon: ':heavy_check_mark:'
    path: cpp/number-theory.hpp
    title: "a^(-1) mod MOD\u3092\u8FD4\u3059"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"test/yosupo-convolution-mod.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#line 2 \"cpp/number-theory.hpp\"\
    \n\n#include <vector>\n#line 2 \"cpp/modint.hpp\"\n\n/**\n * @file modint.hpp\n\
    \ * @brief \u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067\
    \ mod \u3092\u53D6\u308B\u30AF\u30E9\u30B9\n */\n\n#include <iostream>\n#include\
    \ <utility>\n#include <limits>\n#include <type_traits>\n#include <cstdint>\n#include\
    \ <cassert>\n\nnamespace detail {\n    static constexpr std::uint16_t prime32_bases[]\
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
    #line 5 \"cpp/number-theory.hpp\"\n\n/**\n * @brief a^(-1) mod MOD\u3092\u8FD4\
    \u3059\n * @param a long long\n * @param MOD long long\n * @return long long\n\
    \ */\nlong long modinv(long long a, long long MOD) {\n    long long b = MOD, u\
    \ = 1, v = 0;\n    while (b) {\n        long long t = a / b;\n        a -= t *\
    \ b; std::swap(a, b);\n        u -= t * v; std::swap(u, v);\n    }\n    u %= MOD;\
    \ \n    if (u < 0) u += MOD;\n    return u;\n}\n\n/**\n * @brief a^n mod MOD\u3092\
    \u8FD4\u3059\n * @param a long long\n * @param n long long\n * @param MOD long\
    \ long\n * @return long long\n */\nlong long modpow(long long a, long long n,\
    \ long long MOD) {\n    long long res = 1;\n    a %= MOD;\n    if(n < 0) {\n \
    \       n = -n;\n        a = modinv(a, MOD);\n    }\n    while (n > 0) {\n   \
    \     if (n & 1) res = res * a % MOD;\n        a = a * a % MOD;\n        n >>=\
    \ 1;\n    }\n    return res;\n}\n\n/**\n * @brief \u7573\u307F\u8FBC\u307F\n */\n\
    namespace NTT {\n    /**\n     * @brief \u539F\u5B50\u6839\n     * @param MOD\
    \ int\n     * @return int\n     */\n    int calc_primitive_root(int MOD) {\n \
    \       if (MOD == 2) return 1;\n        if (MOD == 167772161) return 3;\n   \
    \     if (MOD == 469762049) return 3;\n        if (MOD == 754974721) return 11;\n\
    \        if (MOD == 998244353) return 3;\n        int divs[20] = {};\n       \
    \ divs[0] = 2;\n        int cnt = 1;\n        long long x = (MOD - 1) >> 1;\n\
    \        while (x % 2 == 0) x >>= 1;\n        for (long long i = 3; i * i <= x;\
    \ i += 2) {\n            if (x % i == 0) {\n                divs[cnt ++] = i;\n\
    \                while (x % i == 0) x /= i;\n            }\n        }\n      \
    \  if (x > 1) divs[cnt++] = x;\n        for (int g = 2;; ++ g) {\n           \
    \ bool ok = true;\n            for (int i = 0; i < cnt; i++) {\n             \
    \   if (modpow(g, (MOD - 1) / divs[i], MOD) == 1) {\n                    ok =\
    \ false;\n                    break;\n                }\n            }\n     \
    \       if (ok) return g;\n        }\n    }\n\n    /**\n     * @brief \u7573\u307F\
    \u8FBC\u307F\u306E\u30B5\u30A4\u30BA\u30922\u306E\u3079\u304D\u4E57\u306B\u3059\
    \u308B\n     */\n    int get_fft_size(int N, int M) {\n        int size_a = 1,\
    \ size_b = 1;\n        while (size_a < N) size_a <<= 1;\n        while (size_b\
    \ < M) size_b <<= 1;\n        return std::max(size_a, size_b) << 1;\n    }\n\n\
    \    /**\n     * @brief NTT\n     */\n    template<class mint> void trans(std::vector<mint>&\
    \ v, bool inv = false) {\n        if (v.empty()) return;\n        int N = (int)\
    \ v.size();\n        int MOD = v[0].mod();\n        int PR = calc_primitive_root(MOD);\n\
    \        static bool first = true;\n        static std::vector<long long> vbw(30),\
    \ vibw(30);\n        if (first) {\n            first = false;\n            for\
    \ (int k = 0; k < 30; ++ k) {\n                vbw[k] = modpow(PR, (MOD - 1) >>\
    \ (k + 1), MOD);\n                vibw[k] = modinv(vbw[k], MOD);\n           \
    \ }\n        }\n        for (int i = 0, j = 1; j < N - 1; ++ j) {\n          \
    \  for (int k = N >> 1; k > (i ^= k); k >>= 1);\n            if (i > j) std::swap(v[i],\
    \ v[j]);\n        }\n        for (int k = 0, t = 2; t <= N; ++ k, t <<= 1) {\n\
    \            long long bw = vbw[k];\n            if (inv) bw = vibw[k];\n    \
    \        for (int i = 0; i < N; i += t) {\n                mint w = 1;\n     \
    \           for (int j = 0; j < (t >> 1); ++ j) {\n                    int j1\
    \ = i + j, j2 = i + j + (t >> 1);\n                    mint c1 = v[j1], c2 = v[j2]\
    \ * w;\n                    v[j1] = c1 + c2;\n                    v[j2] = c1 -\
    \ c2;\n                    w *= bw;\n                }\n            }\n      \
    \  }\n        if (inv) {\n            long long invN = modinv(N, MOD);\n     \
    \       for (int i = 0; i < N; ++ i) v[i] = v[i] * invN;\n        }\n    }\n\n\
    \    static constexpr int MOD0 = 754974721;\n    static constexpr int MOD1 = 167772161;\n\
    \    static constexpr int MOD2 = 469762049;\n    using mint0 = static_modint<MOD0>;\n\
    \    using mint1 = static_modint<MOD1>;\n    using mint2 = static_modint<MOD2>;\n\
    \    static const mint1 imod0 = 95869806; // modinv(MOD0, MOD1);\n    static const\
    \ mint2 imod1 = 104391568; // modinv(MOD1, MOD2);\n    static const mint2 imod01\
    \ = 187290749; // imod1 / MOD0;\n\n    /**\n     * @brief \u914D\u5217\u306E\u30B5\
    \u30A4\u30BA\u304C\u5C0F\u3055\u3044\u3068\u304D\u306E\u7573\u307F\u8FBC\u307F\
    \n     * @param T mint, long long\n     * @param A vector<T>\n     * @param B\
    \ vector<T>\n     * @return vector<T>\n     */\n    template<class T> std::vector<T>\
    \ naive_mul \n    (const std::vector<T>& A, const std::vector<T>& B) {\n     \
    \   if (A.empty() || B.empty()) return {};\n        int N = (int) A.size(), M\
    \ = (int) B.size();\n        std::vector<T> res(N + M - 1);\n        for (int\
    \ i = 0; i < N; ++ i)\n            for (int j = 0; j < M; ++ j)\n            \
    \    res[i + j] += A[i] * B[j];\n        return res;\n    }\n};\n\n/**\n * @brief\
    \ modint\u306E\u7573\u307F\u8FBC\u307F\n * @param A vector<mint>\n * @param B\
    \ vector<mint>\n * @return vector<mint>\n */\ntemplate<class mint> std::vector<mint>\
    \ convolution\n(const std::vector<mint>& A, const std::vector<mint>& B) {\n  \
    \  if (A.empty() || B.empty()) return {};\n    int N = (int) A.size(), M = (int)\
    \ B.size();\n    if (std::min(N, M) < 30) return NTT::naive_mul(A, B);\n    int\
    \ MOD = A[0].mod();\n    int size_fft = NTT::get_fft_size(N, M);\n    if (MOD\
    \ == 998244353) {\n        std::vector<mint> a(size_fft), b(size_fft), c(size_fft);\n\
    \        for (int i = 0; i < N; ++i) a[i] = A[i];\n        for (int i = 0; i <\
    \ M; ++i) b[i] = B[i];\n        NTT::trans(a), NTT::trans(b);\n        std::vector<mint>\
    \ res(size_fft);\n        for (int i = 0; i < size_fft; ++i) res[i] = a[i] * b[i];\n\
    \        NTT::trans(res, true);\n        res.resize(N + M - 1);\n        return\
    \ res;\n    }\n    std::vector<NTT::mint0> a0(size_fft, 0), b0(size_fft, 0), c0(size_fft,\
    \ 0);\n    std::vector<NTT::mint1> a1(size_fft, 0), b1(size_fft, 0), c1(size_fft,\
    \ 0);\n    std::vector<NTT::mint2> a2(size_fft, 0), b2(size_fft, 0), c2(size_fft,\
    \ 0);\n    for (int i = 0; i < N; ++ i) {\n        a0[i] = A[i].value();\n   \
    \     a1[i] = A[i].value();\n        a2[i] = A[i].value();\n    }\n    for (int\
    \ i = 0; i < M; ++ i) {\n        b0[i] = B[i].value();\n        b1[i] = B[i].value();\n\
    \        b2[i] = B[i].value();\n    }\n    NTT::trans(a0), NTT::trans(a1), NTT::trans(a2),\
    \ \n    NTT::trans(b0), NTT::trans(b1), NTT::trans(b2);\n    for (int i = 0; i\
    \ < size_fft; ++i) {\n        c0[i] = a0[i] * b0[i];\n        c1[i] = a1[i] *\
    \ b1[i];\n        c2[i] = a2[i] * b2[i];\n    }\n    NTT::trans(c0, true), NTT::trans(c1,\
    \ true), NTT::trans(c2, true);\n    static const mint mod0 = NTT::MOD0, mod01\
    \ = mod0 * NTT::MOD1;\n    std::vector<mint> res(N + M - 1);\n    for (int i =\
    \ 0; i < N + M - 1; ++ i) {\n        int y0 = c0[i].value();\n        int y1 =\
    \ (NTT::imod0 * (c1[i] - y0)).value();\n        int y2 = (NTT::imod01 * (c2[i]\
    \ - y0) - NTT::imod1 * y1).value();\n        res[i] = mod01 * y2 + mod0 * y1 +\
    \ y0;\n    }\n    return res;\n}\n\n/**\n * @brief long long\u306E\u7573\u307F\
    \u8FBC\u307F\n * @param A vector<long long>\n * @param B vector<long long>\n *\
    \ @return vector<long long>\n */\nstd::vector<long long> convolution_ll\n(const\
    \ std::vector<long long>& A, const std::vector<long long>& B) {\n    if (A.empty()\
    \ || B.empty()) return {};\n    int N = (int) A.size(), M = (int) B.size();\n\
    \    if (std::min(N, M) < 30) return NTT::naive_mul(A, B);\n    int size_fft =\
    \ NTT::get_fft_size(N, M);\n    std::vector<NTT::mint0> a0(size_fft, 0), b0(size_fft,\
    \ 0), c0(size_fft, 0);\n    std::vector<NTT::mint1> a1(size_fft, 0), b1(size_fft,\
    \ 0), c1(size_fft, 0);\n    std::vector<NTT::mint2> a2(size_fft, 0), b2(size_fft,\
    \ 0), c2(size_fft, 0);\n    for (int i = 0; i < N; ++ i) {\n        a0[i] = A[i];\n\
    \        a1[i] = A[i];\n        a2[i] = A[i];\n    }\n    for (int i = 0; i <\
    \ M; ++ i) {\n        b0[i] = B[i];\n        b1[i] = B[i];\n        b2[i] = B[i];\n\
    \    }\n    NTT::trans(a0), NTT::trans(a1), NTT::trans(a2), \n    NTT::trans(b0),\
    \ NTT::trans(b1), NTT::trans(b2);\n    for (int i = 0; i < size_fft; ++ i) {\n\
    \        c0[i] = a0[i] * b0[i];\n        c1[i] = a1[i] * b1[i];\n        c2[i]\
    \ = a2[i] * b2[i];\n    }\n    NTT::trans(c0, true), NTT::trans(c1, true), NTT::trans(c2,\
    \ true);\n    static const long long mod0 = NTT::MOD0, mod01 = mod0 * NTT::MOD1;\n\
    \    static const __int128_t mod012 = (__int128_t)mod01 * NTT::MOD2;\n    std::vector<long\
    \ long> res(N + M - 1);\n    for (int i = 0; i < N + M - 1; ++ i) {\n        int\
    \ y0 = c0[i].value();\n        int y1 = (NTT::imod0 * (c1[i] - y0)).value();\n\
    \        int y2 = (NTT::imod01 * (c2[i] - y0) - NTT::imod1 * y1).value();\n  \
    \      __int128_t tmp = (__int128_t)mod01 * y2 + (__int128_t)mod0 * y1 + y0;\n\
    \        if(tmp < (mod012 >> 1)) res[i] = tmp;\n        else res[i] = tmp - mod012;\n\
    \    }\n    return res;\n}\n#line 4 \"test/yosupo-convolution-mod.test.cpp\"\n\
    \nusing mint = modint998244353;\n\nint main() {\n    long long n, m, x;\n    std::cin\
    \ >> n >> m;\n    std::vector<mint> a(n), b(m);\n    for(int i = 0; i < n; ++\
    \ i) {\n        std::cin >> x;\n        a[i] = mint(x);\n    }\n    for(int i\
    \ = 0; i < m; ++ i) {\n        std::cin >> x;\n        b[i] = mint(x);\n    }\n\
    \    auto c = convolution(a, b);\n    for(auto e : c) std::cout << e.value() <<\
    \ \" \";\n    std::cout << std::endl;\n\n    return 0;\n\n}\n\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"../cpp/number-theory.hpp\"\n\nusing mint = modint998244353;\n\nint main()\
    \ {\n    long long n, m, x;\n    std::cin >> n >> m;\n    std::vector<mint> a(n),\
    \ b(m);\n    for(int i = 0; i < n; ++ i) {\n        std::cin >> x;\n        a[i]\
    \ = mint(x);\n    }\n    for(int i = 0; i < m; ++ i) {\n        std::cin >> x;\n\
    \        b[i] = mint(x);\n    }\n    auto c = convolution(a, b);\n    for(auto\
    \ e : c) std::cout << e.value() << \" \";\n    std::cout << std::endl;\n\n   \
    \ return 0;\n\n}\n\n\n"
  dependsOn:
  - cpp/number-theory.hpp
  - cpp/modint.hpp
  isVerificationFile: true
  path: test/yosupo-convolution-mod.test.cpp
  requiredBy: []
  timestamp: '2023-08-29 23:08:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-convolution-mod.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-convolution-mod.test.cpp
- /verify/test/yosupo-convolution-mod.test.cpp.html
title: test/yosupo-convolution-mod.test.cpp
---
