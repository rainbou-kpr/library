---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/rolling-hash.hpp
    title: "\u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_palindromes
    links:
    - https://judge.yosupo.jp/problem/enumerate_palindromes
  bundledCode: "#line 1 \"test/yosupo-enumerate-palindromes.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\n\n#line 2 \"cpp/rolling-hash.hpp\"\
    \n\n#include <string>\n#include <vector>\n#include <random>\n\n/**\n * @brief\
    \ \u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\n *\n * \u30D3\u30C3\u30C8\
    \u6F14\u7B97\u306B\u5BC4\u308B\u9AD8\u901F\u5316\u306E\u305F\u3081\u30CF\u30C3\
    \u30B7\u30E5\u306FMOD = 2^61-1\u3067\u8A08\u7B97\u3055\u308C\u308B\n *\n * 10^8\u500B\
    \u304F\u3089\u3044\u306A\u308999%\u306E\u78BA\u7387\u3067\u885D\u7A81\u3059\u308B\
    \u7D44\u304C\u5B58\u5728\u3057\u306A\u3044\n */\nclass RollingHash {\n    constexpr\
    \ static unsigned long long MASK30 = (1ULL << 30) - 1;\n    constexpr static unsigned\
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
    \ MOD - mul(hash[l], power[r-l]));\n    }\n};\n#line 4 \"test/yosupo-enumerate-palindromes.test.cpp\"\
    \n\n#include <iostream>\n\nint main(void) {\n    std::string s; std::cin >> s;\n\
    \    int n = s.length();\n    RollingHash rh;\n    auto hash1 = rh.build(s);\n\
    \    auto hash2 = rh.build(s.rbegin(), s.rend());\n    std::vector<int> ans(n*2-1);\n\
    \    for(int i = 0; i < n; i++) {\n        int ok = 0, ng = std::min(i+1, n-i);\n\
    \        while(ng - ok > 1) {\n            int mid = (ok + ng) / 2;\n        \
    \    if(rh.query(hash1, i-mid, i+mid+1) == rh.query(hash2, s.length()-i-mid-1,\
    \ s.length()-i+mid)) ok = mid;\n            else ng = mid;\n        }\n      \
    \  ans[i*2] = ok*2+1;\n    }\n    for(int i = 0; i < n-1; i++) {\n        int\
    \ ok = 0, ng = std::min(i+2, n-i);\n        while(ng - ok > 1) {\n           \
    \ int mid = (ok + ng) / 2;\n            if(rh.query(hash1, i-mid+1, i+mid+1) ==\
    \ rh.query(hash2, s.length()-i-mid-1, s.length()-i+mid-1)) ok = mid;\n       \
    \     else ng = mid;\n        }\n        ans[i*2+1] = ok*2;\n    }\n    for(int\
    \ i = 0; i < n*2-1; i++) std::cout << ans[i] << \" \\n\"[i+1==n*2-1];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n\n#include \"../cpp/rolling-hash.hpp\"\n\n#include <iostream>\n\nint main(void)\
    \ {\n    std::string s; std::cin >> s;\n    int n = s.length();\n    RollingHash\
    \ rh;\n    auto hash1 = rh.build(s);\n    auto hash2 = rh.build(s.rbegin(), s.rend());\n\
    \    std::vector<int> ans(n*2-1);\n    for(int i = 0; i < n; i++) {\n        int\
    \ ok = 0, ng = std::min(i+1, n-i);\n        while(ng - ok > 1) {\n           \
    \ int mid = (ok + ng) / 2;\n            if(rh.query(hash1, i-mid, i+mid+1) ==\
    \ rh.query(hash2, s.length()-i-mid-1, s.length()-i+mid)) ok = mid;\n         \
    \   else ng = mid;\n        }\n        ans[i*2] = ok*2+1;\n    }\n    for(int\
    \ i = 0; i < n-1; i++) {\n        int ok = 0, ng = std::min(i+2, n-i);\n     \
    \   while(ng - ok > 1) {\n            int mid = (ok + ng) / 2;\n            if(rh.query(hash1,\
    \ i-mid+1, i+mid+1) == rh.query(hash2, s.length()-i-mid-1, s.length()-i+mid-1))\
    \ ok = mid;\n            else ng = mid;\n        }\n        ans[i*2+1] = ok*2;\n\
    \    }\n    for(int i = 0; i < n*2-1; i++) std::cout << ans[i] << \" \\n\"[i+1==n*2-1];\n\
    }\n"
  dependsOn:
  - cpp/rolling-hash.hpp
  isVerificationFile: true
  path: test/yosupo-enumerate-palindromes.test.cpp
  requiredBy: []
  timestamp: '2023-05-31 16:27:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-enumerate-palindromes.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-enumerate-palindromes.test.cpp
- /verify/test/yosupo-enumerate-palindromes.test.cpp.html
title: test/yosupo-enumerate-palindromes.test.cpp
---
