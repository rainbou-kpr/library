---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/more_functional.hpp
    title: "\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\
      \u308B"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-1-b.test.cpp
    title: test/aoj-dsl-1-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-jag-summer-2971.test.cpp
    title: test/aoj-jag-summer-2971.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304DUnionFind"
    links: []
  bundledCode: "#line 2 \"cpp/potentialized-unionfind.hpp\"\n\n/**\n * @file potentialized-unionfind.hpp\n\
    \ * @brief \u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304DUnionFind\n */\n#include\
    \ <cassert>\n#include <functional>\n#include <stack>\n#include <utility>\n#include\
    \ <vector>\n#line 2 \"cpp/more_functional.hpp\"\n\n/**\n * @file more_functional.hpp\n\
    \ * @brief \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\
    \u308B\n */\n\n#include <limits>\n#include <numeric>\n#include <type_traits>\n\
    \nnamespace more_functional {\ntemplate <typename S>\nstruct Max {\n    const\
    \ S operator()(const S& a, const S& b) const { return std::max(a, b); }\n};\n\
    template <typename S>\nstruct Min {\n    const S operator()(const S& a, const\
    \ S& b) const { return std::min(a, b); }\n};\ntemplate <typename S, std::enable_if_t<std::is_integral_v<S>>*\
    \ = nullptr>\nstruct Gcd {\n    constexpr S operator()(const S& a, const S& b)\
    \ const { return std::gcd(a, b); }\n};\ntemplate <typename S>\nstruct Zero {\n\
    \    S operator()() const { return S(0); }\n};\ntemplate <typename S>\nstruct\
    \ One {\n    S operator()() const { return S(1); }\n};\ntemplate <typename S>\n\
    struct None {\n    S operator()() const { return S{}; }\n};\ntemplate <typename\
    \ S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\nstruct MaxLimit {\n  \
    \  constexpr S operator()() const { return std::numeric_limits<S>::max(); }\n\
    };\ntemplate <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\n\
    struct MinLimit {\n    constexpr S operator()() const { return std::numeric_limits<S>::lowest();\
    \ }\n};\ntemplate <typename S>\nstruct Div {\n    S operator()(const S& a) const\
    \ { return S(1) / a; }\n};\n}  // namespace more_functional\n#line 13 \"cpp/potentialized-unionfind.hpp\"\
    \n\n/**\n * @brief \u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304DUnionFind\n\
    \ * @tparam S \u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u306E\u578B\n * @tparam Op\
    \ S\u306E\u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam E S\u306E\u5358\
    \u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam Inv S\u306E\
    \u9006\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n */\ntemplate <typename\
    \ S, class Op, class E, class Inv>\nclass PotentializedUnionFind {\n   private:\n\
    \    int _n;\n    // \u8CA0\u306A\u3089\u30B5\u30A4\u30BA\u3001\u975E\u8CA0\u306A\
    \u3089\u89AA\n    std::vector<int> parent_or_size;\n    // \u91CD\u307F\n    std::vector<S>\
    \ diff_weight;\n\n    inline constexpr static auto op = Op();\n    inline constexpr\
    \ static auto e = E();\n    inline constexpr static auto inv = Inv();\n\n   public:\n\
    \    PotentializedUnionFind() : _n{}, parent_or_size{}, diff_weight{} {}\n\n \
    \   /**\n     * @param n \u8981\u7D20\u6570\n     */\n    explicit PotentializedUnionFind(int\
    \ n) : _n(n), parent_or_size(n, -1), diff_weight(n, e()) {}\n\n    /**\n     *\
    \ @brief \u9802\u70B9a\u306E\u5C5E\u3059\u308B\u9023\u7D50\u6210\u5206\u306E\u4EE3\
    \u8868\u5143\n     */\n    int leader(int a) {\n        assert(0 <= a && a < _n);\n\
    \        if (parent_or_size[a] < 0) return a;\n        std::stack<int> stk;\n\
    \        stk.push(a);\n        while (parent_or_size[stk.top()] >= 0) {\n    \
    \        stk.push(parent_or_size[stk.top()]);\n        }\n        const int root\
    \ = stk.top();\n        stk.pop();\n        stk.pop();\n        while (!stk.empty())\
    \ {\n            diff_weight[stk.top()] = op(diff_weight[parent_or_size[stk.top()]],\
    \ diff_weight[stk.top()]);\n            parent_or_size[stk.top()] = root;\n  \
    \          stk.pop();\n        }\n        return root;\n    }\n\n    /**\n   \
    \  * @brief a \u306E\u30B0\u30EB\u30FC\u30D7\u3068 b \u306E\u30B0\u30EB\u30FC\u30D7\
    \u3092\u7D71\u5408\u3059\u308B\n     * @param w (b \u306E\u30DD\u30C6\u30F3\u30B7\
    \u30E3\u30EB) - (a \u306E\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB)\n     * @return\
    \ \u9023\u7D50\u3057\u305F\u3082\u306E\u306E\u4EE3\u8868\u5143\n     */\n    int\
    \ merge(int a, int b, S w) {\n        assert(0 <= a && a < _n);\n        assert(0\
    \ <= b && b < _n);\n        w = op(weight(a), w);\n        w = op(w, inv(weight(b)));\n\
    \        int x = leader(a), y = leader(b);\n        if (x == y) return x;\n  \
    \      if (-parent_or_size[x] < -parent_or_size[y]) {\n            std::swap(x,\
    \ y);\n            w = inv(w);\n        }\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        diff_weight[y] = w;\n        return x;\n\
    \    }\n\n    /**\n     * @brief \u9802\u70B9a,b\u304C\u9023\u7D50\u304B\u3069\
    \u3046\u304B\n     */\n    bool same(int a, int b) {\n        assert(0 <= a &&\
    \ a < _n);\n        assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n\
    \    }\n\n    /**\n     * @brief (b \u306E\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\
    ) - (a \u306E\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB)\n     * @remark \u30C7\u30D5\
    \u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067\u4F5C\u3089\
    \u308C\u308B S \u306B\u3064\u3044\u3066 Inv \u304C\u5B9A\u7FA9\u3055\u308C\u3066\
    \u3044\u308B\u306A\u3089\u3070\u3001a == b \u3092\u8A31\u5BB9\n     */\n    S\
    \ diff(int a, int b) {\n        assert(same(a, b));\n        return op(inv(weight(a)),\
    \ weight(b));\n    }\n\n    /**\n     * @brief \u9802\u70B9a\u306E\u5C5E\u3059\
    \u308B\u9023\u7D50\u6210\u5206\u306E\u30B5\u30A4\u30BA\n     */\n    int size(int\
    \ a) {\n        assert(0 <= a && a < _n);\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u9023\u7D50\u6210\u5206\
    \u306B\u5206\u3051\u3001\u305D\u306E\u60C5\u5831\u3092\u8FD4\u3059\n     * @return\
    \ \u300C\u4E00\u3064\u306E\u9023\u7D50\u6210\u5206\u306E\u9802\u70B9\u756A\u53F7\
    \u306E\u30EA\u30B9\u30C8\u300D\u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }), result.end());\n    \
    \    return result;\n    }\n\n   private:\n    S weight(int a) {\n        leader(a);\n\
    \        return diff_weight[a];\n    }\n};\n\n/**\n * @tparam S \u7FA4\u306E\u578B\
    \n */\ntemplate <typename S>\nusing UnionFindPlus = PotentializedUnionFind<S,\
    \ std::plus<S>, more_functional::None<S>, std::negate<S>>;\n/**\n * @tparam S\
    \ \u7FA4\u306E\u578B\n */\ntemplate <typename S>\nusing UnionFindMul = PotentializedUnionFind<S,\
    \ std::multiplies<S>, more_functional::One<S>, more_functional::Div<S>>;\n"
  code: "#pragma once\n\n/**\n * @file potentialized-unionfind.hpp\n * @brief \u30DD\
    \u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304DUnionFind\n */\n#include <cassert>\n\
    #include <functional>\n#include <stack>\n#include <utility>\n#include <vector>\n\
    #include \"more_functional.hpp\"\n\n/**\n * @brief \u30DD\u30C6\u30F3\u30B7\u30E3\
    \u30EB\u4ED8\u304DUnionFind\n * @tparam S \u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\
    \u306E\u578B\n * @tparam Op S\u306E\u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n\
    \ * @tparam E S\u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\
    \u30BF\n * @tparam Inv S\u306E\u9006\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\
    \u30AF\u30BF\n */\ntemplate <typename S, class Op, class E, class Inv>\nclass\
    \ PotentializedUnionFind {\n   private:\n    int _n;\n    // \u8CA0\u306A\u3089\
    \u30B5\u30A4\u30BA\u3001\u975E\u8CA0\u306A\u3089\u89AA\n    std::vector<int> parent_or_size;\n\
    \    // \u91CD\u307F\n    std::vector<S> diff_weight;\n\n    inline constexpr\
    \ static auto op = Op();\n    inline constexpr static auto e = E();\n    inline\
    \ constexpr static auto inv = Inv();\n\n   public:\n    PotentializedUnionFind()\
    \ : _n{}, parent_or_size{}, diff_weight{} {}\n\n    /**\n     * @param n \u8981\
    \u7D20\u6570\n     */\n    explicit PotentializedUnionFind(int n) : _n(n), parent_or_size(n,\
    \ -1), diff_weight(n, e()) {}\n\n    /**\n     * @brief \u9802\u70B9a\u306E\u5C5E\
    \u3059\u308B\u9023\u7D50\u6210\u5206\u306E\u4EE3\u8868\u5143\n     */\n    int\
    \ leader(int a) {\n        assert(0 <= a && a < _n);\n        if (parent_or_size[a]\
    \ < 0) return a;\n        std::stack<int> stk;\n        stk.push(a);\n       \
    \ while (parent_or_size[stk.top()] >= 0) {\n            stk.push(parent_or_size[stk.top()]);\n\
    \        }\n        const int root = stk.top();\n        stk.pop();\n        stk.pop();\n\
    \        while (!stk.empty()) {\n            diff_weight[stk.top()] = op(diff_weight[parent_or_size[stk.top()]],\
    \ diff_weight[stk.top()]);\n            parent_or_size[stk.top()] = root;\n  \
    \          stk.pop();\n        }\n        return root;\n    }\n\n    /**\n   \
    \  * @brief a \u306E\u30B0\u30EB\u30FC\u30D7\u3068 b \u306E\u30B0\u30EB\u30FC\u30D7\
    \u3092\u7D71\u5408\u3059\u308B\n     * @param w (b \u306E\u30DD\u30C6\u30F3\u30B7\
    \u30E3\u30EB) - (a \u306E\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB)\n     * @return\
    \ \u9023\u7D50\u3057\u305F\u3082\u306E\u306E\u4EE3\u8868\u5143\n     */\n    int\
    \ merge(int a, int b, S w) {\n        assert(0 <= a && a < _n);\n        assert(0\
    \ <= b && b < _n);\n        w = op(weight(a), w);\n        w = op(w, inv(weight(b)));\n\
    \        int x = leader(a), y = leader(b);\n        if (x == y) return x;\n  \
    \      if (-parent_or_size[x] < -parent_or_size[y]) {\n            std::swap(x,\
    \ y);\n            w = inv(w);\n        }\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        diff_weight[y] = w;\n        return x;\n\
    \    }\n\n    /**\n     * @brief \u9802\u70B9a,b\u304C\u9023\u7D50\u304B\u3069\
    \u3046\u304B\n     */\n    bool same(int a, int b) {\n        assert(0 <= a &&\
    \ a < _n);\n        assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n\
    \    }\n\n    /**\n     * @brief (b \u306E\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\
    ) - (a \u306E\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB)\n     * @remark \u30C7\u30D5\
    \u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067\u4F5C\u3089\
    \u308C\u308B S \u306B\u3064\u3044\u3066 Inv \u304C\u5B9A\u7FA9\u3055\u308C\u3066\
    \u3044\u308B\u306A\u3089\u3070\u3001a == b \u3092\u8A31\u5BB9\n     */\n    S\
    \ diff(int a, int b) {\n        assert(same(a, b));\n        return op(inv(weight(a)),\
    \ weight(b));\n    }\n\n    /**\n     * @brief \u9802\u70B9a\u306E\u5C5E\u3059\
    \u308B\u9023\u7D50\u6210\u5206\u306E\u30B5\u30A4\u30BA\n     */\n    int size(int\
    \ a) {\n        assert(0 <= a && a < _n);\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u9023\u7D50\u6210\u5206\
    \u306B\u5206\u3051\u3001\u305D\u306E\u60C5\u5831\u3092\u8FD4\u3059\n     * @return\
    \ \u300C\u4E00\u3064\u306E\u9023\u7D50\u6210\u5206\u306E\u9802\u70B9\u756A\u53F7\
    \u306E\u30EA\u30B9\u30C8\u300D\u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }), result.end());\n    \
    \    return result;\n    }\n\n   private:\n    S weight(int a) {\n        leader(a);\n\
    \        return diff_weight[a];\n    }\n};\n\n/**\n * @tparam S \u7FA4\u306E\u578B\
    \n */\ntemplate <typename S>\nusing UnionFindPlus = PotentializedUnionFind<S,\
    \ std::plus<S>, more_functional::None<S>, std::negate<S>>;\n/**\n * @tparam S\
    \ \u7FA4\u306E\u578B\n */\ntemplate <typename S>\nusing UnionFindMul = PotentializedUnionFind<S,\
    \ std::multiplies<S>, more_functional::One<S>, more_functional::Div<S>>;\n"
  dependsOn:
  - cpp/more_functional.hpp
  isVerificationFile: false
  path: cpp/potentialized-unionfind.hpp
  requiredBy: []
  timestamp: '2024-05-17 22:45:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj-dsl-1-b.test.cpp
  - test/aoj-jag-summer-2971.test.cpp
documentation_of: cpp/potentialized-unionfind.hpp
layout: document
redirect_from:
- /library/cpp/potentialized-unionfind.hpp
- /library/cpp/potentialized-unionfind.hpp.html
title: "\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304DUnionFind"
---
