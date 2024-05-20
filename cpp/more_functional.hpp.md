---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: cpp/lazy-segtree.hpp
    title: "\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: cpp/merge-sort-tree.hpp
    title: "\u30DE\u30FC\u30B8\u30BD\u30FC\u30C8\u30C4\u30EA\u30FC"
  - icon: ':heavy_check_mark:'
    path: cpp/potentialized-unionfind.hpp
    title: "\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304DUnionFind"
  - icon: ':heavy_check_mark:'
    path: cpp/segtree-2d.hpp
    title: "2\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: cpp/segtree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-1-b.test.cpp
    title: test/aoj-dsl-1-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-a.test.cpp
    title: test/aoj-dsl-2-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-b.test.cpp
    title: test/aoj-dsl-2-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-f.test.cpp
    title: test/aoj-dsl-2-f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-g.test.cpp
    title: test/aoj-dsl-2-g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-h.test.cpp
    title: test/aoj-dsl-2-h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-i.test.cpp
    title: test/aoj-dsl-2-i.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-jag-summer-2971.test.cpp
    title: test/aoj-jag-summer-2971.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/atcoder-abc177-f.1.test.cpp
    title: test/atcoder-abc177-f.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/atcoder-abc177-f.2.test.cpp
    title: test/atcoder-abc177-f.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/atcoder-abc185-f.test.cpp
    title: test/atcoder-abc185-f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/atcoder-abc254-f.test.cpp
    title: test/atcoder-abc254-f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/atcoder-abc331-f.test.cpp
    title: test/atcoder-abc331-f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/atcoder-past202012-n.test.cpp
    title: test/atcoder-past202012-n.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-lca.2.test.cpp
    title: test/yosupo-lca.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-point-add-rectangle-sum.test.cpp
    title: test/yosupo-point-add-rectangle-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-point-set-range-composite.1.test.cpp
    title: test/yosupo-point-set-range-composite.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-point-set-range-composite.2.test.cpp
    title: test/yosupo-point-set-range-composite.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-point-set-range-composite.3.test.cpp
    title: test/yosupo-point-set-range-composite.3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-range-affine-range-sum.1.test.cpp
    title: test/yosupo-range-affine-range-sum.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-range-affine-range-sum.2.test.cpp
    title: test/yosupo-range-affine-range-sum.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-range-affine-range-sum.3.test.cpp
    title: test/yosupo-range-affine-range-sum.3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-rectangle-sum.test.cpp
    title: test/yosupo-rectangle-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder-2292.test.cpp
    title: test/yukicoder-2292.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\
      \u3059\u308B"
    links: []
  bundledCode: "#line 2 \"cpp/more_functional.hpp\"\n\n/**\n * @file more_functional.hpp\n\
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
    \ { return S(1) / a; }\n};\n}  // namespace more_functional\n"
  code: "#pragma once\n\n/**\n * @file more_functional.hpp\n * @brief \u95A2\u6570\
    \u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\u308B\n */\n\n#include\
    \ <limits>\n#include <numeric>\n#include <type_traits>\n\nnamespace more_functional\
    \ {\ntemplate <typename S>\nstruct Max {\n    const S operator()(const S& a, const\
    \ S& b) const { return std::max(a, b); }\n};\ntemplate <typename S>\nstruct Min\
    \ {\n    const S operator()(const S& a, const S& b) const { return std::min(a,\
    \ b); }\n};\ntemplate <typename S, std::enable_if_t<std::is_integral_v<S>>* =\
    \ nullptr>\nstruct Gcd {\n    constexpr S operator()(const S& a, const S& b) const\
    \ { return std::gcd(a, b); }\n};\ntemplate <typename S>\nstruct Zero {\n    S\
    \ operator()() const { return S(0); }\n};\ntemplate <typename S>\nstruct One {\n\
    \    S operator()() const { return S(1); }\n};\ntemplate <typename S>\nstruct\
    \ None {\n    S operator()() const { return S{}; }\n};\ntemplate <typename S,\
    \ std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\nstruct MaxLimit {\n    constexpr\
    \ S operator()() const { return std::numeric_limits<S>::max(); }\n};\ntemplate\
    \ <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\nstruct MinLimit\
    \ {\n    constexpr S operator()() const { return std::numeric_limits<S>::lowest();\
    \ }\n};\ntemplate <typename S>\nstruct Div {\n    S operator()(const S& a) const\
    \ { return S(1) / a; }\n};\n}  // namespace more_functional\n"
  dependsOn: []
  isVerificationFile: false
  path: cpp/more_functional.hpp
  requiredBy:
  - cpp/merge-sort-tree.hpp
  - cpp/segtree-2d.hpp
  - cpp/potentialized-unionfind.hpp
  - cpp/lazy-segtree.hpp
  - cpp/segtree.hpp
  timestamp: '2024-05-17 22:45:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-lca.2.test.cpp
  - test/atcoder-abc254-f.test.cpp
  - test/yosupo-range-affine-range-sum.1.test.cpp
  - test/yosupo-point-set-range-composite.2.test.cpp
  - test/atcoder-past202012-n.test.cpp
  - test/atcoder-abc331-f.test.cpp
  - test/yosupo-point-set-range-composite.1.test.cpp
  - test/aoj-dsl-2-g.test.cpp
  - test/yosupo-range-affine-range-sum.3.test.cpp
  - test/aoj-dsl-2-a.test.cpp
  - test/atcoder-abc177-f.2.test.cpp
  - test/aoj-dsl-1-b.test.cpp
  - test/aoj-dsl-2-b.test.cpp
  - test/yukicoder-2292.test.cpp
  - test/aoj-dsl-2-h.test.cpp
  - test/aoj-dsl-2-i.test.cpp
  - test/aoj-dsl-2-f.test.cpp
  - test/atcoder-abc185-f.test.cpp
  - test/yosupo-point-add-rectangle-sum.test.cpp
  - test/yosupo-rectangle-sum.test.cpp
  - test/atcoder-abc177-f.1.test.cpp
  - test/yosupo-point-set-range-composite.3.test.cpp
  - test/aoj-jag-summer-2971.test.cpp
  - test/yosupo-range-affine-range-sum.2.test.cpp
documentation_of: cpp/more_functional.hpp
layout: document
redirect_from:
- /library/cpp/more_functional.hpp
- /library/cpp/more_functional.hpp.html
title: "\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\u308B"
---
