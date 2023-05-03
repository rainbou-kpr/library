---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo-enumerate-quotients.test.cpp
    title: test/yosupo-enumerate-quotients.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: floor(sqrt(n))
    links: []
  bundledCode: "#line 2 \"cpp/sqrt.hpp\"\n\n/**\n * @brief floor(sqrt(n))\n * @param\
    \ n \u5E73\u65B9\u6839\u3092\u6C42\u3081\u305F\u3044\u6574\u6570 long long \u578B\
    \u3067 0 <= n < 2^63 \u3092\u6E80\u305F\u3059\n * @return long long\n */\nlong\
    \ long sqrtll(long long n) { \n    // 3037000500 = ceil(sqrt(2^63))\n    long\
    \ long le = 0, ri = 3037000500; \n    while(ri - le > 1) {\n        long long\
    \ mid = (le + ri) / 2;\n        if(mid * mid <= n) le = mid;\n        else ri\
    \ = mid;\n    }\n    return le;\n}\n"
  code: "#pragma once\n\n/**\n * @brief floor(sqrt(n))\n * @param n \u5E73\u65B9\u6839\
    \u3092\u6C42\u3081\u305F\u3044\u6574\u6570 long long \u578B\u3067 0 <= n < 2^63\
    \ \u3092\u6E80\u305F\u3059\n * @return long long\n */\nlong long sqrtll(long long\
    \ n) { \n    // 3037000500 = ceil(sqrt(2^63))\n    long long le = 0, ri = 3037000500;\
    \ \n    while(ri - le > 1) {\n        long long mid = (le + ri) / 2;\n       \
    \ if(mid * mid <= n) le = mid;\n        else ri = mid;\n    }\n    return le;\n\
    }"
  dependsOn: []
  isVerificationFile: false
  path: cpp/sqrt.hpp
  requiredBy: []
  timestamp: '2023-05-03 12:22:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-enumerate-quotients.test.cpp
documentation_of: cpp/sqrt.hpp
layout: document
redirect_from:
- /library/cpp/sqrt.hpp
- /library/cpp/sqrt.hpp.html
title: floor(sqrt(n))
---
