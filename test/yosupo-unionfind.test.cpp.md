---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/unionfind.hpp
    title: UnionFind
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/yosupo-unionfind.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#include <iostream>\n\n#line 2 \"cpp/unionfind.hpp\"\n\n/**\n * @file unionfind.hpp\n\
    \ * @brief UnionFind\n */\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <vector>\n\n/**\n * @brief \u7121\u5411\u30B0\u30E9\u30D5\u306B\u5BFE\u3057\u3066\
    \u300C\u8FBA\u306E\u8FFD\u52A0\u300D\u3001\u300C2\u9802\u70B9\u304C\u9023\u7D50\
    \u304B\u306E\u5224\u5B9A\u300D\u3092\u3059\u308B\n */\nstruct UnionFind {\n  \
    \ private:\n    int _n;\n    // \u8CA0\u306A\u3089\u30B5\u30A4\u30BA\u3001\u975E\
    \u8CA0\u306A\u3089\u89AA\n    std::vector<int> parent_or_size;\n\n   public:\n\
    \    UnionFind() : _n(0) {}\n    explicit UnionFind(int n) : _n(n), parent_or_size(n,\
    \ -1) {}\n\n    /**\n     * @brief \u8FBA(a,b)\u3092\u8DB3\u3059\n     * @return\
    \ \u9023\u7D50\u3057\u305F\u3082\u306E\u306E\u4EE3\u8868\u5143\n     */\n    int\
    \ merge(int a, int b) {\n        assert(0 <= a && a < _n);\n        assert(0 <=\
    \ b && b < _n);\n        int x = leader(a), y = leader(b);\n        if (x == y)\
    \ return x;\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n    /**\n     * @brief \u9802\u70B9a,b\u304C\
    \u9023\u7D50\u304B\u3069\u3046\u304B\n     */\n    bool same(int a, int b) {\n\
    \        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n      \
    \  return leader(a) == leader(b);\n    }\n    /**\n     * @brief \u9802\u70B9\
    a\u306E\u5C5E\u3059\u308B\u9023\u7D50\u6210\u5206\u306E\u4EE3\u8868\u5143\n  \
    \   */\n    int leader(int a) {\n        assert(0 <= a && a < _n);\n        if\
    \ (parent_or_size[a] < 0) return a;\n        int x = a;\n        while (parent_or_size[x]\
    \ >= 0) {\n            x = parent_or_size[x];\n        }\n        while (parent_or_size[a]\
    \ >= 0) {\n            int t = parent_or_size[a];\n            parent_or_size[a]\
    \ = x;\n            a = t;\n        }\n        return x;\n    }\n    /**\n   \
    \  * @brief \u9802\u70B9a\u306E\u5C5E\u3059\u308B\u9023\u7D50\u6210\u5206\u306E\
    \u30B5\u30A4\u30BA\n     */\n    int size(int a) {\n        assert(0 <= a && a\
    \ < _n);\n        return -parent_or_size[leader(a)];\n    }\n    /**\n     * @brief\
    \ \u30B0\u30E9\u30D5\u3092\u9023\u7D50\u6210\u5206\u306B\u5206\u3051\u3001\u305D\
    \u306E\u60C5\u5831\u3092\u8FD4\u3059\n     * @return \u300C\u4E00\u3064\u306E\u9023\
    \u7D50\u6210\u5206\u306E\u9802\u70B9\u756A\u53F7\u306E\u30EA\u30B9\u30C8\u300D\
    \u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>> groups()\
    \ {\n        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(\n            std::remove_if(result.begin(),\
    \ result.end(),\n                           [&](const std::vector<int>& v) { return\
    \ v.empty(); }),\n            result.end());\n        return result;\n    }\n\
    };\n#line 6 \"test/yosupo-unionfind.test.cpp\"\n\nint main() {\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n    UnionFind g(N);\n    int t, u, v;\n    for (int\
    \ i = 0; i < Q; i++) {\n        std::cin >> t >> u >> v;\n        if (t == 0)\
    \ {\n            g.merge(u, v);\n        } else {\n            std::cout << g.same(u,\
    \ v) << '\\n';\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <iostream>\n\n#include \"../cpp/unionfind.hpp\"\n\nint main() {\n    int N,\
    \ Q;\n    std::cin >> N >> Q;\n    UnionFind g(N);\n    int t, u, v;\n    for\
    \ (int i = 0; i < Q; i++) {\n        std::cin >> t >> u >> v;\n        if (t ==\
    \ 0) {\n            g.merge(u, v);\n        } else {\n            std::cout <<\
    \ g.same(u, v) << '\\n';\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - cpp/unionfind.hpp
  isVerificationFile: true
  path: test/yosupo-unionfind.test.cpp
  requiredBy: []
  timestamp: '2023-04-28 12:54:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-unionfind.test.cpp
- /verify/test/yosupo-unionfind.test.cpp.html
title: test/yosupo-unionfind.test.cpp
---
