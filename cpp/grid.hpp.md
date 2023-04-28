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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"cpp/grid.hpp\"\n\n#include <vector>\n#include <algorithm>\n\
    \ntemplate<class T> std::vector<T> transpose(const std::vector<T> &v) {\n    int\
    \ n = v.size();\n    if(n == 0) return v;\n    int m = v[0].size();\n    std::vector<T>\
    \ ret(m);\n    for(int i = 0; i < m; i ++) {\n        ret[i].resize(n);\n    \
    \    for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];\n    }\n    return ret;\n\
    }\n\ntemplate<class T> std::vector<T> rev_lr(std::vector<T> v) {\n    int n =\
    \ v.size();\n    for(int i = 0; i < n; i ++) reverse(v[i].begin(), v[i].end());\n\
    \    return v;\n}\n\ntemplate<class T> std::vector<T> rev_ud(std::vector<T> v)\
    \ {\n    reverse(v.begin(), v.end());\n    return v;\n}\n\ntemplate<class T> std::vector<T>\
    \ rotate(const std::vector<T> &v, int k) {\n    k %= 4;\n    if(k == 0) return\
    \ v;\n    if(k < 0) k += 4;\n    if(k == 2) return rev_lr(rev_ud(v));\n    int\
    \ n = v.size(); if(n == 0) return v;\n    int m = v[0].size();\n    std::vector<T>\
    \ ret(m);\n    if(k == 1) {\n        for(int i = 0; i < m; i ++) {\n         \
    \   ret[i].resize(n);\n            for(int j = 0; j < n; j ++) ret[i][j] = v[n\
    \ - j - 1][i];\n        }\n    } else {\n        for(int i = 0; i < m; i ++) {\n\
    \            ret[i].resize(n);\n            for(int j = 0; j < n; j ++) ret[i][j]\
    \ = v[j][m - i - 1];\n        }\n    }\n    return ret;\n}\n"
  code: "#pragma once\n\n#include <vector>\n#include <algorithm>\n\ntemplate<class\
    \ T> std::vector<T> transpose(const std::vector<T> &v) {\n    int n = v.size();\n\
    \    if(n == 0) return v;\n    int m = v[0].size();\n    std::vector<T> ret(m);\n\
    \    for(int i = 0; i < m; i ++) {\n        ret[i].resize(n);\n        for(int\
    \ j = 0; j < n; j ++) ret[i][j] = v[j][i];\n    }\n    return ret;\n}\n\ntemplate<class\
    \ T> std::vector<T> rev_lr(std::vector<T> v) {\n    int n = v.size();\n    for(int\
    \ i = 0; i < n; i ++) reverse(v[i].begin(), v[i].end());\n    return v;\n}\n\n\
    template<class T> std::vector<T> rev_ud(std::vector<T> v) {\n    reverse(v.begin(),\
    \ v.end());\n    return v;\n}\n\ntemplate<class T> std::vector<T> rotate(const\
    \ std::vector<T> &v, int k) {\n    k %= 4;\n    if(k == 0) return v;\n    if(k\
    \ < 0) k += 4;\n    if(k == 2) return rev_lr(rev_ud(v));\n    int n = v.size();\
    \ if(n == 0) return v;\n    int m = v[0].size();\n    std::vector<T> ret(m);\n\
    \    if(k == 1) {\n        for(int i = 0; i < m; i ++) {\n            ret[i].resize(n);\n\
    \            for(int j = 0; j < n; j ++) ret[i][j] = v[n - j - 1][i];\n      \
    \  }\n    } else {\n        for(int i = 0; i < m; i ++) {\n            ret[i].resize(n);\n\
    \            for(int j = 0; j < n; j ++) ret[i][j] = v[j][m - i - 1];\n      \
    \  }\n    }\n    return ret;\n}"
  dependsOn: []
  isVerificationFile: false
  path: cpp/grid.hpp
  requiredBy: []
  timestamp: '2023-04-28 10:20:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder-rotate-enlarge_2.test.cpp
  - test/yukicoder-rotate-enlarge_1.test.cpp
documentation_of: cpp/grid.hpp
layout: document
redirect_from:
- /library/cpp/grid.hpp
- /library/cpp/grid.hpp.html
title: cpp/grid.hpp
---
