---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/sqrt.hpp
    title: floor(sqrt(n))
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_quotients
    links:
    - https://judge.yosupo.jp/problem/enumerate_quotients
  bundledCode: "#line 1 \"test/yosupo-enumerate-quotients.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/enumerate_quotients\"\n\n#line 2 \"cpp/sqrt.hpp\"\
    \n\n/**\n * @brief floor(sqrt(n))\n * @param n \u5E73\u65B9\u6839\u3092\u6C42\u3081\
    \u305F\u3044\u6574\u6570 long long \u578B\u3067 0 <= n < 2^63 \u3092\u6E80\u305F\
    \u3059\n * @return long long\n */\nlong long sqrtll(long long n) { \n    // 3037000500\
    \ = ceil(sqrt(2^63))\n    long long le = 0, ri = 3037000500; \n    while(ri -\
    \ le > 1) {\n        long long mid = (le + ri) / 2;\n        if(mid * mid <= n)\
    \ le = mid;\n        else ri = mid;\n    }\n    return le;\n}\n#line 4 \"test/yosupo-enumerate-quotients.test.cpp\"\
    \n#include <vector>\n#include <algorithm>\n#include <iostream>\n\nint main() {\n\
    \    long long n;\n    std::cin >> n;\n    std::vector<long long> v1, v2;\n  \
    \  long long m = sqrtll(n);\n    for(long long i = 1; i <= m; i ++) {\n      \
    \  v1.push_back(n / i);\n        v2.push_back(i);\n    }\n    if(v1.back() ==\
    \ v2.back()) v1.pop_back();\n\n    std::cout << v1.size() + v2.size() << std::endl;\n\
    \    reverse(v1.begin(), v1.end());\n    for(long long e : v2) std::cout << e\
    \ << \" \";\n    for(long long e : v1) std::cout << e << \" \";\n    std::cout\
    \ << std::endl;\n\n    return 0;\n}\n\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_quotients\"\n\
    \n#include \"../cpp/sqrt.hpp\"\n#include <vector>\n#include <algorithm>\n#include\
    \ <iostream>\n\nint main() {\n    long long n;\n    std::cin >> n;\n    std::vector<long\
    \ long> v1, v2;\n    long long m = sqrtll(n);\n    for(long long i = 1; i <= m;\
    \ i ++) {\n        v1.push_back(n / i);\n        v2.push_back(i);\n    }\n   \
    \ if(v1.back() == v2.back()) v1.pop_back();\n\n    std::cout << v1.size() + v2.size()\
    \ << std::endl;\n    reverse(v1.begin(), v1.end());\n    for(long long e : v2)\
    \ std::cout << e << \" \";\n    for(long long e : v1) std::cout << e << \" \"\
    ;\n    std::cout << std::endl;\n\n    return 0;\n}\n\n\n"
  dependsOn:
  - cpp/sqrt.hpp
  isVerificationFile: true
  path: test/yosupo-enumerate-quotients.test.cpp
  requiredBy: []
  timestamp: '2023-05-03 12:22:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-enumerate-quotients.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-enumerate-quotients.test.cpp
- /verify/test/yosupo-enumerate-quotients.test.cpp.html
title: test/yosupo-enumerate-quotients.test.cpp
---
