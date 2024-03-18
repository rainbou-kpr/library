---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/rolling-hash.hpp
    title: "\u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5"
  - icon: ':heavy_check_mark:'
    path: cpp/segtree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: cpp/traits.hpp
    title: cpp/traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc331/tasks/abc331_f
    links:
    - https://atcoder.jp/contests/abc331/tasks/abc331_f
  bundledCode: "#line 1 \"test/atcoder-abc331-f.test.cpp\"\n#define PROBLEM \"https://atcoder.jp/contests/abc331/tasks/abc331_f\"\
    \n\n#include <iostream>\n\n#line 2 \"cpp/rolling-hash.hpp\"\n\n#include <string>\n\
    #include <vector>\n#include <random>\n#include <cassert>\n#include <string_view>\n\
    #include <type_traits>\n\n#line 2 \"cpp/traits.hpp\"\n\n#include <iterator>\n\
    #line 5 \"cpp/traits.hpp\"\n#include <utility>\n\nnamespace detail {\nusing std::begin,\
    \ std::end;\n\ntemplate <class T, class = void>\nstruct is_range_impl : std::false_type\
    \ {};\ntemplate <class T>\nstruct is_range_impl<T, std::void_t<decltype(begin(std::declval<T&>()),\
    \ end(std::declval<T&>()))>> : std::true_type {};\n}  // namespace detail\n\n\
    template <class T>\nstruct is_range : detail::is_range_impl<T>::type {};\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n#line 11\
    \ \"cpp/rolling-hash.hpp\"\n\nstruct RHString;\n\n/**\n * @brief \u30ED\u30FC\u30EA\
    \u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\n *\n * \u30D3\u30C3\u30C8\u6F14\u7B97\u306B\
    \u5BC4\u308B\u9AD8\u901F\u5316\u306E\u305F\u3081\u30CF\u30C3\u30B7\u30E5\u306F\
    MOD = 2^61-1\u3067\u8A08\u7B97\u3055\u308C\u308B\n *\n * 10^8\u500B\u304F\u3089\
    \u3044\u306A\u308999%\u306E\u78BA\u7387\u3067\u885D\u7A81\u3059\u308B\u7D44\u304C\
    \u5B58\u5728\u3057\u306A\u3044\n */\nclass RollingHash {\n    constexpr static\
    \ unsigned long long MASK30 = (1ULL << 30) - 1;\n    constexpr static unsigned\
    \ long long MASK31 = (1ULL << 31) - 1;\n    constexpr static unsigned long long\
    \ MOD = (1ULL << 61) - 1;\n\n    // a < MOD, b < MOD\u5FC5\u9808\n    constexpr\
    \ static unsigned long long add(unsigned long long a, unsigned long long b) {\n\
    \        if((a += b) >= MOD) a -= MOD;\n        return a;\n    }\n\n    // a <\
    \ MOD, b < MOD\u5FC5\u9808\n    constexpr static unsigned long long mul(unsigned\
    \ long long a, unsigned long long b) {\n        __uint128_t c = static_cast<__uint128_t>(a)\
    \ * b;\n        return add(static_cast<unsigned long long>(c >> 61), static_cast<unsigned\
    \ long long>(c & MOD));\n    }\n\n    void expand(int n) {\n        while(static_cast<int>(power.size())\
    \ <= n) power.push_back(mul(power.back(), base));\n    }\n\npublic:\n    unsigned\
    \ int base; //!< \u30CF\u30C3\u30B7\u30E5\u306E\u57FA\u6570\n    std::vector<unsigned\
    \ long long> power; //!< base\u306E\u7D2F\u4E57\n\n    /**\n     * @brief \u30B3\
    \u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     *\n     * @param base \u30CF\u30C3\u30B7\
    \u30E5\u306E\u57FA\u6570 \u7701\u7565\u3059\u308B\u3068\u30E9\u30F3\u30C0\u30E0\
    \n     */\n    RollingHash(unsigned int base = 0) : base(base) {\n        if(base\
    \ == 0) {\n            std::mt19937 mt(std::random_device{}());\n            this->base\
    \ = std::uniform_int_distribution<unsigned int>(129, ~0U)(mt);\n        }\n  \
    \      power = {1};\n    }\n\n    /**\n     * @brief \u914D\u5217/\u6587\u5B57\
    \u5217\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\u9593\u306E\u30CF\u30C3\u30B7\u30E5\
    \u306E\u8A08\u7B97(O(N))\n     *\n     * @tparam It \u30A4\u30C6\u30EC\u30FC\u30BF\
    \n     * @param first \u914D\u5217\u306E\u958B\u59CB\u30A4\u30C6\u30EC\u30FC\u30BF\
    \n     * @param last \u914D\u5217\u306E\u7D42\u4E86\u30A4\u30C6\u30EC\u30FC\u30BF\
    \n     * @return std::vector<unsigned long long> \u5148\u982D\u304B\u3089\u5404\
    \u8981\u7D20\u6570\u5206\u306E\u30CF\u30C3\u30B7\u30E5\n     */\n    template\
    \ <typename It>\n    std::vector<unsigned long long> build(It first, It last)\
    \ {\n        std::vector<unsigned long long> res;\n        if constexpr (std::is_convertible_v<typename\
    \ std::iterator_traits<It>::iterator_category, std::random_access_iterator_tag>)\
    \ {\n            res.reserve(last - first + 1);\n        }\n        res.push_back(0);\n\
    \        for(; first != last; ++first) {\n            res.push_back(add(mul(res.back(),\
    \ base), *first));\n        }\n        return res;\n    }\n\n    /**\n     * @brief\
    \ \u914D\u5217/\u6587\u5B57\u5217\u5168\u4F53\u306E\u30CF\u30C3\u30B7\u30E5\u306E\
    \u8A08\u7B97(O(N))\n     *\n     * @param s \u914D\u5217/\u6587\u5B57\u5217\n\
    \     * @return std::vector<unsigned long long> \u5148\u982D\u304B\u3089\u5404\
    \u6587\u5B57\u6570\u5206\u306E\u30CF\u30C3\u30B7\u30E5\n     */\n    template\
    \ <typename R>\n    std::vector<unsigned long long> build(R&& s) {\n        using\
    \ std::begin, std::end;\n        return build(begin(s), end(s));\n    }\n\n  \
    \  /**\n     * @brief [l,r)\u306E\u30CF\u30C3\u30B7\u30E5\u306E\u8A08\u7B97(O(1))\n\
    \     *\n     * @param hash \u5148\u982D\u304B\u3089\u306E\u30CF\u30C3\u30B7\u30E5\
    \n     * @param l \u533A\u9593\u306E\u5DE6\u7AEF\n     * @param r \u533A\u9593\
    \u306E\u53F3\u7AEF\n     * @return unsigned long long [l,r)\u306E\u30CF\u30C3\u30B7\
    \u30E5\n     */\n    unsigned long long query(const std::vector<unsigned long\
    \ long>& hash, int l, int r) {\n        expand(r - l);\n        return add(hash[r],\
    \ MOD - mul(hash[l], power[r-l]));\n    }\n\n    friend RHString;\n};\n\n/**\n\
    \ * @brief \u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\u306B\u3088\u3063\
    \u3066\u7BA1\u7406\u3055\u308C\u308B\u6587\u5B57\u5217\u578B\n */\nstruct RHString\
    \ {\n    RollingHash& rh;\n    size_t sz;\n    unsigned long long hash1;  //!<\
    \ \u6B63\u9806\n    unsigned long long hash2;  //!< \u9006\u9806\n    /**\n  \
    \   * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \u4E88\u3081RollingHash\u3092\
    \u30A4\u30F3\u30B9\u30BF\u30F3\u30B9\u5316\u3057\u3066\u304A\u304F\u5FC5\u8981\
    \u304C\u3042\u308B\n     */\n    RHString(RollingHash& rh) : rh(rh), sz(0), hash1(0),\
    \ hash2(0) {}\n    RHString(RollingHash& rh, size_t sz, unsigned long long hash1,\
    \ unsigned long long hash2) : rh(rh), sz(sz), hash1(hash1), hash2(hash2) {}\n\
    \    RHString(const RHString& o) : rh(o.rh), sz(o.sz), hash1(o.hash1), hash2(o.hash2)\
    \ {}\n    /**\n     * @brief vector\u306A\u3069\u3067\u521D\u671F\u5316\u3059\u308B\
    \n     */\n    template <class R, std::enable_if_t<is_range_v<R> && !std::is_convertible_v<R,\
    \ std::string_view>, std::nullptr_t> = nullptr>\n    RHString(RollingHash& rh,\
    \ R&& v) : rh(rh) {\n        using std::begin, std::end, std::rbegin, std::rend;\n\
    \        sz = std::distance(begin(v), end(v));\n        hash1 = rh.build(begin(v),\
    \ end(v)).back();\n        hash2 = rh.build(rbegin(v), rend(v)).back();\n    }\n\
    \    /**\n     * @brief char\u3084unsigned long long\u306A\u3069\u3067\u521D\u671F\
    \u5316\u3059\u308B\n     */\n    template <class T, std::enable_if_t<std::is_convertible_v<T,\
    \ unsigned long long> && !std::is_convertible_v<T, std::string_view>, std::nullptr_t>\
    \ = nullptr>\n    RHString(RollingHash& rh, T&& x) : rh(rh) {\n        sz = 1;\n\
    \        hash1 = x;\n        hash2 = x;\n    }\n    /**\n     * @brief \u6587\u5B57\
    \u5217(string, const char*, string_view)\u3067\u521D\u671F\u5316\u3059\u308B\n\
    \     */\n    RHString(RollingHash& rh, std::string_view s) : rh(rh) {\n     \
    \   sz = std::distance(s.begin(), s.end());\n        hash1 = rh.build(s.begin(),\
    \ s.end()).back();\n        hash2 = rh.build(s.rbegin(), s.rend()).back();\n \
    \   }\n\n    /**\n     * @brief \u56DE\u6587\u304B\u5426\u304B\n     */\n    bool\
    \ is_palindrome() const {\n        return hash1 == hash2;\n    }\n    size_t size()\
    \ const {\n        return sz;\n    }\n    void clear() {\n        sz = 0;\n  \
    \      hash1 = 0;\n        hash2 = 0;\n    }\n    bool empty() const {\n     \
    \   return sz == 0;\n    }\n    RHString& operator+=(const RHString& o) {\n  \
    \      assert(&rh == &o.rh);\n        rh.expand(sz);\n        rh.expand(o.sz);\n\
    \        hash1 = rh.add(rh.mul(hash1, rh.power[o.sz]), o.hash1);\n        hash2\
    \ = rh.add(hash2, rh.mul(o.hash2, rh.power[sz]));\n        sz += o.sz;\n     \
    \   return *this;\n    }\n    /**\n     * @brief \u518D\u4EE3\u5165\u3059\u308B\
    \n     * RollingHash\u306F\u540C\u3058\u3082\u306E\u3067\u3042\u308B\u5FC5\u8981\
    \u304C\u3042\u308B\n     */\n    void assign(const RHString& o) {\n        assert(&rh\
    \ == &o.rh);\n        sz = o.sz;\n        hash1 = o.hash1;\n        hash2 = o.hash2;\n\
    \    }\n    /**\n     * @brief vector\u306A\u3069\u3092\u518D\u4EE3\u5165\u3059\
    \u308B\n     */\n    template <class R, std::enable_if_t<is_range_v<R> && !std::is_convertible_v<R,\
    \ std::string_view>, std::nullptr_t> = nullptr>\n    void assign(R&& v) {\n  \
    \      using std::begin, std::end, std::rbegin, std::rend;\n        sz = std::distance(begin(v),\
    \ end(v));\n        hash1 = rh.build(begin(v), end(v)).back();\n        hash2\
    \ = rh.build(rbegin(v), rend(v)).back();\n    }\n    /**\n     * @brief char\u3084\
    unsigned long long\u306A\u3069\u3092\u518D\u4EE3\u5165\u3059\u308B\n     */\n\
    \    template <class T, std::enable_if_t<std::is_convertible_v<T, unsigned long\
    \ long> && !std::is_convertible_v<T, std::string_view>, std::nullptr_t> = nullptr>\n\
    \    void assign(T&& x) {\n        sz = 1;\n        hash1 = x;\n        hash2\
    \ = x;\n    }\n    /**\n     * @brief \u6587\u5B57\u5217(string, const char*,\
    \ string_view)\u3092\u518D\u4EE3\u5165\u3059\u308B\n     */\n    void assign(std::string_view\
    \ s) {\n        sz = std::distance(s.begin(), s.end());\n        hash1 = rh.build(s.begin(),\
    \ s.end()).back();\n        hash2 = rh.build(s.rbegin(), s.rend()).back();\n \
    \   }\n    /**\n     * @brief \u518D\u4EE3\u5165\u3059\u308B\n     * RollingHash\u306F\
    \u540C\u3058\u3082\u306E\u3067\u3042\u308B\u5FC5\u8981\u304C\u3042\u308B\n   \
    \  */\n    RHString& operator=(const RHString& o) {\n        assign(o);\n    \
    \    return *this;\n    }\n    /**\n     * @brief vector\u306A\u3069\u3092\u518D\
    \u4EE3\u5165\u3059\u308B\n     */\n    template <class R, std::enable_if_t<is_range_v<R>\
    \ && !std::is_convertible_v<R, std::string_view>, std::nullptr_t> = nullptr>\n\
    \    RHString& operator=(R&& v) {\n        assign(v);\n        return *this;\n\
    \    }\n    /**\n     * @brief char\u3084unsigned long long\u306A\u3069\u3092\u518D\
    \u4EE3\u5165\u3059\u308B\n     */\n    template <class T, std::enable_if_t<std::is_convertible_v<T,\
    \ unsigned long long> && !std::is_convertible_v<T, std::string_view>, std::nullptr_t>\
    \ = nullptr>\n    RHString& operator=(T&& x) {\n        assign(x);\n        return\
    \ *this;\n    }\n    /**\n     * @brief \u6587\u5B57\u5217(string, const char*,\
    \ string_view)\u3092\u518D\u4EE3\u5165\u3059\u308B\n     */\n    RHString& operator=(std::string_view\
    \ s) {\n        assign(s);\n        return *this;\n    }\n    friend RHString\
    \ operator+(const RHString& t1, const RHString& t2) {\n        RHString ret =\
    \ t1;\n        ret += t2;\n        return ret;\n    }\n    friend bool operator==(const\
    \ RHString& t1, const RHString& t2) {\n        assert(&t1.rh == &t2.rh);\n   \
    \     return t1.sz == t2.sz && t1.hash1 == t2.hash1 && t1.hash2 == t2.hash2;\n\
    \    }\n    friend bool operator!=(const RHString& t1, const RHString& t2) { return\
    \ !(t1 == t2); }\n};\n#line 2 \"cpp/segtree.hpp\"\n\n/**\n * @file segtree.hpp\n\
    \ * @brief \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n */\n\n#line 9 \"cpp/segtree.hpp\"\
    \n#include <functional>\n#include <limits>\n#include <numeric>\n#include <ostream>\n\
    #line 14 \"cpp/segtree.hpp\"\n\n/**\n * @brief \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\
    \u306ECRTP\u57FA\u5E95\u30AF\u30E9\u30B9\n * \n * @tparam S \u30E2\u30CE\u30A4\
    \u30C9\u306E\u578B\n * @tparam ActualSegTree \u6D3E\u751F\u30AF\u30E9\u30B9\n\
    \ */\ntemplate <typename S, typename ActualSegTree>\nclass SegTreeBase {\n   \
    \ S op(const S& a, const S& b) const { return static_cast<const ActualSegTree&>(*this).op(a,\
    \ b); }\n    S e() const { return static_cast<const ActualSegTree&>(*this).e();\
    \ }\n\n    int n, sz, height;\n    std::vector<S> data;\n    void update(int k)\
    \ { data[k] = op(data[2 * k], data[2 * k + 1]); }\n\n    class SegTreeReference\
    \ {\n        SegTreeBase& segtree;\n        int k;\n    public:\n        SegTreeReference(SegTreeBase&\
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
    test/atcoder-abc331-f.test.cpp\"\n\nRollingHash rh;\nstruct E {\n    RHString\
    \ operator()() const { return RHString(rh); }\n};\n\nint main() {\n    int N,\
    \ Q;\n    std::string S;\n    std::cin >> N >> Q >> S;\n    std::vector<RHString>\
    \ init;\n    init.reserve(N);\n    for (char c : S) {\n        init.emplace_back(rh,\
    \ c);\n    }\n    StaticSegTree<RHString, std::plus<RHString>, E> seg(init);\n\
    \    while (Q--) {\n        int q;\n        std::cin >> q;\n        if (q == 1)\
    \ {\n            int x;\n            char c;\n            std::cin >> x >> c;\n\
    \            seg.set(x - 1, RHString(rh, c));\n        } else {\n            int\
    \ L, R;\n            std::cin >> L >> R;\n            std::cout << (seg.prod(L\
    \ - 1, R).is_palindrome() ? \"Yes\" : \"No\") << std::endl;\n        }\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc331/tasks/abc331_f\"\n\n\
    #include <iostream>\n\n#include \"../cpp/rolling-hash.hpp\"\n#include \"../cpp/segtree.hpp\"\
    \n\nRollingHash rh;\nstruct E {\n    RHString operator()() const { return RHString(rh);\
    \ }\n};\n\nint main() {\n    int N, Q;\n    std::string S;\n    std::cin >> N\
    \ >> Q >> S;\n    std::vector<RHString> init;\n    init.reserve(N);\n    for (char\
    \ c : S) {\n        init.emplace_back(rh, c);\n    }\n    StaticSegTree<RHString,\
    \ std::plus<RHString>, E> seg(init);\n    while (Q--) {\n        int q;\n    \
    \    std::cin >> q;\n        if (q == 1) {\n            int x;\n            char\
    \ c;\n            std::cin >> x >> c;\n            seg.set(x - 1, RHString(rh,\
    \ c));\n        } else {\n            int L, R;\n            std::cin >> L >>\
    \ R;\n            std::cout << (seg.prod(L - 1, R).is_palindrome() ? \"Yes\" :\
    \ \"No\") << std::endl;\n        }\n    }\n}"
  dependsOn:
  - cpp/rolling-hash.hpp
  - cpp/traits.hpp
  - cpp/segtree.hpp
  isVerificationFile: true
  path: test/atcoder-abc331-f.test.cpp
  requiredBy: []
  timestamp: '2024-03-11 22:28:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/atcoder-abc331-f.test.cpp
layout: document
redirect_from:
- /verify/test/atcoder-abc331-f.test.cpp
- /verify/test/atcoder-abc331-f.test.cpp.html
title: test/atcoder-abc331-f.test.cpp
---
