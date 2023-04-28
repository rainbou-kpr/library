---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/grid.hpp
    title: cpp/grid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/565
    links:
    - https://yukicoder.me/problems/no/565
  bundledCode: "#line 1 \"test/yukicoder-rotate-enlarge_2.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/565\"\n\n#line 2 \"cpp/grid.hpp\"\n\n#include\
    \ <vector>\n#include <algorithm>\n\ntemplate<class T> std::vector<T> transpose(const\
    \ std::vector<T> &v) {\n    int n = v.size();\n    if(n == 0) return v;\n    int\
    \ m = v[0].size();\n    std::vector<T> ret(m);\n    for(int i = 0; i < m; i ++)\
    \ {\n        ret[i].resize(n);\n        for(int j = 0; j < n; j ++) ret[i][j]\
    \ = v[j][i];\n    }\n    return ret;\n}\n\ntemplate<class T> std::vector<T> rev_lr(std::vector<T>\
    \ v) {\n    int n = v.size();\n    for(int i = 0; i < n; i ++) reverse(v[i].begin(),\
    \ v[i].end());\n    return v;\n}\n\ntemplate<class T> std::vector<T> rev_ud(std::vector<T>\
    \ v) {\n    reverse(v.begin(), v.end());\n    return v;\n}\n\ntemplate<class T>\
    \ std::vector<T> rotate(const std::vector<T> &v, int k) {\n    k %= 4;\n    if(k\
    \ == 0) return v;\n    if(k < 0) k += 4;\n    if(k == 2) return rev_lr(rev_ud(v));\n\
    \    int n = v.size(); if(n == 0) return v;\n    int m = v[0].size();\n    std::vector<T>\
    \ ret(m);\n    if(k == 1) {\n        for(int i = 0; i < m; i ++) {\n         \
    \   ret[i].resize(n);\n            for(int j = 0; j < n; j ++) ret[i][j] = v[n\
    \ - j - 1][i];\n        }\n    } else {\n        for(int i = 0; i < m; i ++) {\n\
    \            ret[i].resize(n);\n            for(int j = 0; j < n; j ++) ret[i][j]\
    \ = v[j][m - i - 1];\n        }\n    }\n    return ret;\n}\n#line 4 \"test/yukicoder-rotate-enlarge_2.test.cpp\"\
    \n#include <iostream>\n#include <string>\n\nstd::string extend(std::string s,\
    \ int k) {\n    std::string ret = \"\";\n    for(char c : s) ret += std::string(k,\
    \ c);\n    return ret;\n}\n\nint main() {\n    int r, k, h, w;\n    std::cin >>\
    \ r >> k >> h >> w;\n    std::vector<std::string> c(h);\n    for(int i = 0; i\
    \ < h; i ++) std::cin >> c[i];\n\n    for(auto s : rotate(c, r / 90)) {\n    \
    \    std::string t = extend(s, k);\n        for(int i = 0; i < k; i ++) std::cout\
    \ << t << std::endl;\n    }\n    return 0;\n}\n\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/565\"\n\n#include \"../cpp/grid.hpp\"\
    \n#include <iostream>\n#include <string>\n\nstd::string extend(std::string s,\
    \ int k) {\n    std::string ret = \"\";\n    for(char c : s) ret += std::string(k,\
    \ c);\n    return ret;\n}\n\nint main() {\n    int r, k, h, w;\n    std::cin >>\
    \ r >> k >> h >> w;\n    std::vector<std::string> c(h);\n    for(int i = 0; i\
    \ < h; i ++) std::cin >> c[i];\n\n    for(auto s : rotate(c, r / 90)) {\n    \
    \    std::string t = extend(s, k);\n        for(int i = 0; i < k; i ++) std::cout\
    \ << t << std::endl;\n    }\n    return 0;\n}\n\n"
  dependsOn:
  - cpp/grid.hpp
  isVerificationFile: true
  path: test/yukicoder-rotate-enlarge_2.test.cpp
  requiredBy: []
  timestamp: '2023-04-28 10:20:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yukicoder-rotate-enlarge_2.test.cpp
layout: document
redirect_from:
- /verify/test/yukicoder-rotate-enlarge_2.test.cpp
- /verify/test/yukicoder-rotate-enlarge_2.test.cpp.html
title: test/yukicoder-rotate-enlarge_2.test.cpp
---
