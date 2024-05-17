---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: cpp/potentialized-unionfind.hpp
    title: "\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304DUnionFind"
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
    document_title: "\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\
      \u3059\u308B"
    links: []
  bundledCode: "#line 2 \"cpp/more_functional.hpp\"\n\n/**\n * @file more_functional.hpp\n\
    \ * @brief \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\
    \u308B\n */\n\nnamespace more_functional {\ntemplate <typename S>\nstruct Zero\
    \ {\n    S operator()() const { return S(0); }\n};\ntemplate <typename S>\nstruct\
    \ One {\n    S operator()() const { return S(1); }\n};\ntemplate <typename S>\n\
    struct None {\n    S operator()() const { return S{}; }\n};\ntemplate <typename\
    \ S>\nstruct Div {\n    S operator()(const S& a) const { return S(1) / a; }\n\
    };\n}  // namespace more_functional\n"
  code: "#pragma once\n\n/**\n * @file more_functional.hpp\n * @brief \u95A2\u6570\
    \u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\u308B\n */\n\nnamespace\
    \ more_functional {\ntemplate <typename S>\nstruct Zero {\n    S operator()()\
    \ const { return S(0); }\n};\ntemplate <typename S>\nstruct One {\n    S operator()()\
    \ const { return S(1); }\n};\ntemplate <typename S>\nstruct None {\n    S operator()()\
    \ const { return S{}; }\n};\ntemplate <typename S>\nstruct Div {\n    S operator()(const\
    \ S& a) const { return S(1) / a; }\n};\n}  // namespace more_functional\n"
  dependsOn: []
  isVerificationFile: false
  path: cpp/more_functional.hpp
  requiredBy:
  - cpp/potentialized-unionfind.hpp
  timestamp: '2024-05-07 01:35:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj-dsl-1-b.test.cpp
  - test/aoj-jag-summer-2971.test.cpp
documentation_of: cpp/more_functional.hpp
layout: document
redirect_from:
- /library/cpp/more_functional.hpp
- /library/cpp/more_functional.hpp.html
title: "\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\u308B"
---
