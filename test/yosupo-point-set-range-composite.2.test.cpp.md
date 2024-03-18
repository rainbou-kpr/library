---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: cpp/modint.hpp
    title: "\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod\
      \ \u3092\u53D6\u308B\u30AF\u30E9\u30B9"
  - icon: ':heavy_check_mark:'
    path: cpp/segtree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/yosupo-point-set-range-composite.2.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\n\n#include\
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
    #line 2 \"cpp/segtree.hpp\"\n\n/**\n * @file segtree.hpp\n * @brief \u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728\n */\n\n#line 9 \"cpp/segtree.hpp\"\n#include <functional>\n\
    #line 11 \"cpp/segtree.hpp\"\n#include <numeric>\n#include <ostream>\n#include\
    \ <vector>\n\n/**\n * @brief \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u306ECRTP\u57FA\
    \u5E95\u30AF\u30E9\u30B9\n * \n * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\
    \n * @tparam ActualSegTree \u6D3E\u751F\u30AF\u30E9\u30B9\n */\ntemplate <typename\
    \ S, typename ActualSegTree>\nclass SegTreeBase {\n    S op(const S& a, const\
    \ S& b) const { return static_cast<const ActualSegTree&>(*this).op(a, b); }\n\
    \    S e() const { return static_cast<const ActualSegTree&>(*this).e(); }\n\n\
    \    int n, sz, height;\n    std::vector<S> data;\n    void update(int k) { data[k]\
    \ = op(data[2 * k], data[2 * k + 1]); }\n\n    class SegTreeReference {\n    \
    \    SegTreeBase& segtree;\n        int k;\n    public:\n        SegTreeReference(SegTreeBase&\
    \ segtree, int k) : segtree(segtree), k(k) {}\n        SegTreeReference& operator=(const\
    \ S& x) {\n            segtree.set(k, x);\n            return *this;\n       \
    \ }\n        operator S() const { return segtree.get(k); }\n    };\n\nprotected:\n\
    \    void construct_data() {\n        sz = 1;\n        height = 0;\n        while\
    \ (sz < n) {\n            sz <<= 1;\n            height++;\n        }\n      \
    \  data.assign(sz * 2, e());\n    }\n    void initialize(const std::vector<S>&\
    \ v) {\n        for (int i = 0; i < n; i++) data[sz + i] = v[i];\n        for\
    \ (int i = sz - 1; i > 0; i--) update(i);\n    }\n\npublic:\n    // Warning: \u7D99\
    \u627F\u5148\u306E\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067construct_data()\u3092\
    \u5FC5\u305A\u547C\u3073\u51FA\u3059\uFF01\n    SegTreeBase(int n = 0) : n(n)\
    \ {}\n\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\
    \u5024\u3092\u8FD4\u3059\n     * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\
    \u30B9\n     * @return S \u5024\n     */\n    S get(int k) const {\n        assert(0\
    \ <= k && k < n);\n        return data[sz + k];\n    }\n    /**\n     * @brief\
    \ \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u3092\u8FD4\u3059\n \
    \    * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @return\
    \ S \u5024\n     */\n    S operator[] (int k) const { return get(k); }\n    /**\n\
    \     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u3078\u306E\u53C2\u7167\
    \u3092\u8FD4\u3059\n     * \n     * @param k \n     * @return SegTreeReference\
    \ \u8981\u7D20\u3078\u306E\u53C2\u7167 \u4EE3\u5165\u3055\u308C\u308B\u3068set()\u304C\
    \u547C\u3070\u308C\u308B\n     */\n    SegTreeReference operator[] (int k) { return\
    \ SegTreeReference(*this, k); }\n\n    /**\n     * @brief \u5185\u5BB9\u3092\u51FA\
    \u529B\u3059\u308B\n     * \n     * @tparam CharT \u51FA\u529B\u30B9\u30C8\u30EA\
    \u30FC\u30E0\u306E\u6587\u5B57\u578B\n     * @tparam Traits \u51FA\u529B\u30B9\
    \u30C8\u30EA\u30FC\u30E0\u306E\u6587\u5B57\u578B\u7279\u6027\n     * @param os\
    \ \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\n     * @param rhs \u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\n     * @return std::basic_ostream<CharT, Traits>& \u51FA\u529B\
    \u30B9\u30C8\u30EA\u30FC\u30E0 \n     */\n    template <class CharT, class Traits>\n\
    \    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT,\
    \ Traits>& os, const SegTreeBase& rhs) {\n        for(int i = 0; i < rhs.n; i++)\
    \ {\n            if(i != 0) os << CharT(' ');\n            os << rhs[i];\n   \
    \     }\n        return os;\n    }\n\n    /**\n     * @brief \u6307\u5B9A\u3055\
    \u308C\u305F\u8981\u7D20\u306E\u5024\u3092x\u306B\u66F4\u65B0\u3059\u308B\n  \
    \   * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @param x\
    \ \u65B0\u3057\u3044\u5024\n     */\n    void set(int k, const S& x) {\n     \
    \   assert(0 <= k && k < n);\n        k += sz;\n        data[k] = x;\n       \
    \ for (int i = 1; i <= height; i++) update(k >> i);\n    }\n    /**\n     * @brief\
    \ \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u306Bx\u3092\u4F5C\u7528\
    \u3055\u305B\u308B\n     * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\
    \n     * @param x \u4F5C\u7528\u7D20\n     */\n    void apply(int k, const S&\
    \ x) { set(k, op(get(k), x)); }\n\n    /**\n     * @brief [l, r)\u306E\u533A\u9593\
    \u306E\u7DCF\u7A4D\u3092\u8FD4\u3059\n     * \n     * @param l \u534A\u958B\u533A\
    \u9593\u306E\u958B\u59CB\n     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\
    \u7AEF 0<=l<=r<=n\n     * @return S \u7DCF\u7A4D\n     */\n    S prod(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= n);\n        S left_prod\
    \ = e(), right_prod = e();\n        l += sz;\n        r += sz;\n        while\
    \ (l < r) {\n            if (l & 1) left_prod = op(left_prod, data[l++]);\n  \
    \          if (r & 1) right_prod = op(data[--r], right_prod);\n            l >>=\
    \ 1;\n            r >>= 1;\n        }\n        return op(left_prod, right_prod);\n\
    \    }\n    /**\n     * @brief \u3059\u3079\u3066\u306E\u8981\u7D20\u306E\u7DCF\
    \u7A4D\u3092\u8FD4\u3059\n     * \n     * @return S \u7DCF\u7A4D\n     */\n  \
    \  S all_prod() const { return data[1]; }\n\n    /**\n     * @brief (r = l or\
    \ f(prod([l, r))) = true) and (r = n or f(prod([l, r+1))) = false)\u3068\u306A\
    \u308Br\u3092\u8FD4\u3059\n     * f\u304C\u5358\u8ABF\u306A\u3089\u3001f(prod([l,\
    \ r))) = true\u3068\u306A\u308B\u6700\u5927\u306Er\n     * \n     * @tparam F\n\
    \     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB 0<=l<=n\n     * @param\
    \ f \u5224\u5B9A\u95A2\u6570 f(e) = true\n     * @return int\n     */\n    template\
    \ <typename F>\n    int max_right(int l, F f) const {\n        assert(f(e()));\n\
    \        assert(0 <= l && l <= n);\n        if (l == n) return n;\n        l +=\
    \ sz;\n        while (l % 2 == 0) l >>= 1;\n        S sum = e();\n        while(f(op(sum,\
    \ data[l]))) {\n            sum = op(sum, data[l]);\n            l++;\n      \
    \      while (l % 2 == 0) l >>= 1;\n            if (l == 1) return n;\n      \
    \  }\n        while (l < sz) {\n            if (!f(op(sum, data[l * 2]))) l *=\
    \ 2;\n            else {\n                sum = op(sum, data[l * 2]);\n      \
    \          l = l * 2 + 1;\n            }\n        }\n        return l - sz;\n\
    \    }\n    /**\n     * @brief (l = 0 or f(prod([l, r))) = true) and (l = r or\
    \ f(prod([l-1, r))) = false)\u3068\u306A\u308Bl\u3092\u8FD4\u3059\n     * f\u304C\
    \u5358\u8ABF\u306A\u3089\u3001f(prod([l, r))) = true\u3068\u306A\u308B\u6700\u5C0F\
    \u306El\n     * \n     * @tparam F\n     * @param r \u534A\u958B\u533A\u9593\u306E\
    \u7D42\u7AEF 0<=r<=n\n     * @param f \u5224\u5B9A\u95A2\u6570 f(e) = true\n \
    \    * @return int\n     */\n    template <typename F>\n    int min_left(int r,\
    \ F f) const {\n        assert(f(e()));\n        assert(0 <= r && r <= n);\n \
    \       if (r == 0) return 0;\n        r += sz;\n        while (r % 2 == 0) r\
    \ >>= 1;\n        S sum = e();\n        while(f(op(data[r-1], sum))) {\n     \
    \       sum = op(data[r-1], sum);\n            r--;\n            while (r % 2\
    \ == 0) r >>= 1;\n            if (r == 1) return 0;\n        }\n        while\
    \ (r < sz) {\n            if (!f(op(data[r * 2 - 1], sum))) r *= 2;\n        \
    \    else {\n                sum = op(data[r * 2 - 1], sum);\n               \
    \ r = r * 2 - 1;\n            }\n        }\n        return r - sz;\n    }\n};\n\
    \n/**\n * @brief \u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\u304C\u9759\u7684\u306A\
    \u5834\u5408\u306E\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u306E\u5B9F\u88C5\n * \n\
    \ * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\n * @tparam Op \u7A4D\u306E\
    \u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam E \u7A4D\u306E\u5358\u4F4D\u5143\u3092\
    \u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n */\ntemplate <typename S, typename\
    \ Op, typename E>\nclass StaticSegTree : public SegTreeBase<S, StaticSegTree<S,\
    \ Op, E>> {\n    using BaseType = SegTreeBase<S, StaticSegTree<S, Op, E>>;\n\n\
    \    inline static Op operator_object;\n    inline static E identity_object;\n\
    public:\n    S op(const S& a, const S& b) const { return operator_object(a, b);\
    \ }\n    S e() const { return identity_object(); }\n\n    /**\n     * @brief \u30C7\
    \u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n\
    \    */\n    StaticSegTree() = default;\n    /**\n     * @brief \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * \n     * @param n \u8981\u7D20\u6570\n     */\n\
    \    explicit StaticSegTree(int n) : BaseType(n) {\n        this->construct_data();\n\
    \    }\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n  \
    \   * \n     * @param v \u521D\u671F\u306E\u8981\u7D20\n     */\n    explicit\
    \ StaticSegTree(const std::vector<S>& v) : StaticSegTree(v.size()) {\n       \
    \ this->initialize(v);\n    }\n};\n\n/**\n * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\
    \u30AF\u30BF\u3067\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u4E0E\
    \u3048\u308B\u3053\u3068\u3067\u7A4D\u3092\u5B9A\u7FA9\u3059\u308B\u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728\u306E\u5B9F\u88C5\n * \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\
    \u5F15\u6570\u3092\u7701\u7565\u3059\u308B\u3053\u3068\u304C\u3067\u304D\u3001\
    \u30E9\u30E0\u30C0\u5F0F\u304C\u4F7F\u3048\u308B\n * \n * @tparam S \u30E2\u30CE\
    \u30A4\u30C9\u306E\u578B\n * @tparam Op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\u306E\u578B\n */\ntemplate <typename S, typename Op>\nclass\
    \ SegTree : public SegTreeBase<S, SegTree<S, Op>> {\n    using BaseType = SegTreeBase<S,\
    \ SegTree<S, Op>>;\n\n    Op operator_object;\n    S identity;\n\npublic:\n  \
    \  S op(const S& a, const S& b) const { return operator_object(a, b); }\n    S\
    \ e() const { return identity; }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\
    \u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n    */\n    SegTree() = default;\n\
    \    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n\
    \     * @param n \u8981\u7D20\u6570\n     * @param op \u7A4D\u306E\u95A2\u6570\
    \u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param identity \u5358\u4F4D\u5143\
    \n     */\n    explicit SegTree(int n, Op op, const S& identity) : BaseType(n),\
    \ operator_object(std::move(op)), identity(identity) {\n        this->construct_data();\n\
    \    }\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n  \
    \   * \n     * @param v \u521D\u671F\u306E\u8981\u7D20\n     * @param op \u7A4D\
    \u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param identity\
    \ \u5358\u4F4D\u5143\n     */\n    explicit SegTree(const std::vector<S>& v, Op\
    \ op, const S& identity) : SegTree(v.size(), std::move(op), identity) {\n    \
    \    this->initialize(v);\n    }\n};\n\nnamespace segtree {\n    template <typename\
    \ S>\n    struct Max {\n        const S operator() (const S& a, const S& b) const\
    \ { return std::max(a, b); }\n    };\n    template <typename S>\n    struct Min\
    \ {\n        const S operator() (const S& a, const S& b) const { return std::min(a,\
    \ b); }\n    };\n    template <typename S, std::enable_if_t<std::is_integral_v<S>>*\
    \ = nullptr>\n    struct Gcd {\n        constexpr S operator()(const S& a, const\
    \ S& b) const { return std::gcd(a, b); }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MaxLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::max(); }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MinLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::lowest(); }\n    };\n    template <typename S>\n\
    \    struct Zero {\n        S operator() () const { return S(0); }\n    };\n \
    \   template <typename S>\n    struct One {\n        S operator()() const { return\
    \ S(1); }\n    };\n    template <typename S>\n    struct None {\n        S operator()()\
    \ const { return S{}; }\n    };\n}\n/**\n * @brief RangeMaxQuery\n * \n * @tparam\
    \ S \u578B\n */\ntemplate <typename S>\nusing RMaxQ = StaticSegTree<S, segtree::Max<S>,\
    \ segtree::MinLimit<S>>;\n/**\n * @brief RangeMinQuery\n * \n * @tparam S \u578B\
    \n */\ntemplate <typename S>\nusing RMinQ = StaticSegTree<S, segtree::Min<S>,\
    \ segtree::MaxLimit<S>>;\n/**\n * @brief RangeSumQuery\n * \n * @tparam S \u578B\
    \n */\ntemplate <typename S>\nusing RSumQ = StaticSegTree<S, std::plus<S>, segtree::None<S>>;\n\
    /**\n * @brief RangeProdQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RProdQ = StaticSegTree<S, std::multiplies<S>, segtree::One<S>>;\n\
    /**\n * @brief RangeXorQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RXorQ = StaticSegTree<S, std::bit_xor<S>, segtree::Zero<S>>;\n/**\n\
    \ * @brief RangeGcdQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename S>\n\
    using RGcdQ = StaticSegTree<S, segtree::Gcd<S>, segtree::Zero<S>>;\n#line 7 \"\
    test/yosupo-point-set-range-composite.2.test.cpp\"\n\nint main(void) {\n    int\
    \ n, q; std::cin >> n >> q;\n    using S = std::pair<modint998244353, modint998244353>;\n\
    \    std::vector<S> v(n);\n    for(int i = 0; i < n; i++) std::cin >> v[i].first\
    \ >> v[i].second;\n    SegTree seg(v, [](const S& l, const S& r) {\n         \
    \   return std::make_pair(r.first * l.first, r.first * l.second + r.second);\n\
    \        },\n        std::make_pair(modint998244353(1), modint998244353(0))\n\
    \    );\n    while(q--) {\n        int op; std::cin >> op;\n        if(op == 0)\
    \ {\n            int p; modint998244353 c, d; std::cin >> p >> c >> d;\n     \
    \       seg.set(p, std::make_pair(c, d));\n        } else {\n            int l,\
    \ r; modint998244353 x; std::cin >> l >> r >> x;\n            S f = seg.prod(l,\
    \ r);\n            std::cout << f.first * x + f.second << '\\n';\n        }\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include <iostream>\n\n#include \"../cpp/modint.hpp\"\n#include \"../cpp/segtree.hpp\"\
    \n\nint main(void) {\n    int n, q; std::cin >> n >> q;\n    using S = std::pair<modint998244353,\
    \ modint998244353>;\n    std::vector<S> v(n);\n    for(int i = 0; i < n; i++)\
    \ std::cin >> v[i].first >> v[i].second;\n    SegTree seg(v, [](const S& l, const\
    \ S& r) {\n            return std::make_pair(r.first * l.first, r.first * l.second\
    \ + r.second);\n        },\n        std::make_pair(modint998244353(1), modint998244353(0))\n\
    \    );\n    while(q--) {\n        int op; std::cin >> op;\n        if(op == 0)\
    \ {\n            int p; modint998244353 c, d; std::cin >> p >> c >> d;\n     \
    \       seg.set(p, std::make_pair(c, d));\n        } else {\n            int l,\
    \ r; modint998244353 x; std::cin >> l >> r >> x;\n            S f = seg.prod(l,\
    \ r);\n            std::cout << f.first * x + f.second << '\\n';\n        }\n\
    \    }\n}"
  dependsOn:
  - cpp/modint.hpp
  - cpp/segtree.hpp
  isVerificationFile: true
  path: test/yosupo-point-set-range-composite.2.test.cpp
  requiredBy: []
  timestamp: '2024-03-11 22:28:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-point-set-range-composite.2.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-point-set-range-composite.2.test.cpp
- /verify/test/yosupo-point-set-range-composite.2.test.cpp.html
title: test/yosupo-point-set-range-composite.2.test.cpp
---
