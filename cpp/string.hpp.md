---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo-zalgorithm.test.cpp
    title: test/yosupo-zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Z-algorithm
    links: []
  bundledCode: "#line 2 \"cpp/string.hpp\"\n\n#include <vector>\n\n/**\n * @brief\
    \ Z-algorithm\n * s[0:]\u3068s[i:]\u306ELCP\u306E\u9577\u3055\u3092\u5404i\u306B\
    \u3064\u3044\u3066\u6C42\u3081\u308B \u5168\u4F53\u3067O(N)\n *\n * @tparam It\
    \ \u914D\u5217\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\n * @param begin \u914D\u5217\
    \u306E\u958B\u59CB\u30A4\u30C6\u30EC\u30FC\u30BF\n * @param end \u914D\u5217\u306E\
    \u7D42\u4E86\u30A4\u30C6\u30EC\u30FC\u30BF\n * @return std::vector<typename std::iterator_traits<It>::value_type>\
    \ z\n */\ntemplate <typename It>\nstd::vector<int> z_algorithm(It begin, It end)\
    \ {\n    int n = end - begin;\n    std::vector<int> z(n);\n    z[0] = n;\n   \
    \ for(int i = 1, j = 0; i < n;) {\n        // [0, j)\u3068[i, i + j)\u304C\u4E00\
    \u81F4\u3057\u3066\u3044\u308B\n        while(i + j < n && begin[j] == begin[i\
    \ + j]) j++;\n        z[i] = j;\n        int k = 1; // [k,)\u3068[i+k,)\u306F\
    LCP\u304C\u7B49\u3057\u3044\u3068\u78BA\u5B9A\u3057\u3066\u3044\u308B\n      \
    \  for(; k < j && k + z[k] < j; k++) {\n            z[i + k] = z[k];\n       \
    \ }\n        i += k;\n        if(j) j -= k;\n    }\n    return z;\n}\n\n/**\n\
    \ * @brief Z-algorithm\n * s[0:]\u3068s[i:]\u306ELCP\u306E\u9577\u3055\u3092\u5404\
    i\u306B\u3064\u3044\u3066\u6C42\u3081\u308B \u5168\u4F53\u3067O(N)\n *\n * @tparam\
    \ R \u914D\u5217\u306E\u578B\n * @param s \u914D\u5217\n * @return std::vector<typename\
    \ R::value_type> z\n */\ntemplate <typename R>\nstd::vector<int> z_algorithm(const\
    \ R& s) {\n    return z_algorithm(std::begin(s), std::end(s));\n}\n"
  code: "#pragma once\n\n#include <vector>\n\n/**\n * @brief Z-algorithm\n * s[0:]\u3068\
    s[i:]\u306ELCP\u306E\u9577\u3055\u3092\u5404i\u306B\u3064\u3044\u3066\u6C42\u3081\
    \u308B \u5168\u4F53\u3067O(N)\n *\n * @tparam It \u914D\u5217\u306E\u30A4\u30C6\
    \u30EC\u30FC\u30BF\n * @param begin \u914D\u5217\u306E\u958B\u59CB\u30A4\u30C6\
    \u30EC\u30FC\u30BF\n * @param end \u914D\u5217\u306E\u7D42\u4E86\u30A4\u30C6\u30EC\
    \u30FC\u30BF\n * @return std::vector<typename std::iterator_traits<It>::value_type>\
    \ z\n */\ntemplate <typename It>\nstd::vector<int> z_algorithm(It begin, It end)\
    \ {\n    int n = end - begin;\n    std::vector<int> z(n);\n    z[0] = n;\n   \
    \ for(int i = 1, j = 0; i < n;) {\n        // [0, j)\u3068[i, i + j)\u304C\u4E00\
    \u81F4\u3057\u3066\u3044\u308B\n        while(i + j < n && begin[j] == begin[i\
    \ + j]) j++;\n        z[i] = j;\n        int k = 1; // [k,)\u3068[i+k,)\u306F\
    LCP\u304C\u7B49\u3057\u3044\u3068\u78BA\u5B9A\u3057\u3066\u3044\u308B\n      \
    \  for(; k < j && k + z[k] < j; k++) {\n            z[i + k] = z[k];\n       \
    \ }\n        i += k;\n        if(j) j -= k;\n    }\n    return z;\n}\n\n/**\n\
    \ * @brief Z-algorithm\n * s[0:]\u3068s[i:]\u306ELCP\u306E\u9577\u3055\u3092\u5404\
    i\u306B\u3064\u3044\u3066\u6C42\u3081\u308B \u5168\u4F53\u3067O(N)\n *\n * @tparam\
    \ R \u914D\u5217\u306E\u578B\n * @param s \u914D\u5217\n * @return std::vector<typename\
    \ R::value_type> z\n */\ntemplate <typename R>\nstd::vector<int> z_algorithm(const\
    \ R& s) {\n    return z_algorithm(std::begin(s), std::end(s));\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: cpp/string.hpp
  requiredBy: []
  timestamp: '2023-06-15 15:22:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-zalgorithm.test.cpp
documentation_of: cpp/string.hpp
layout: document
redirect_from:
- /library/cpp/string.hpp
- /library/cpp/string.hpp.html
title: Z-algorithm
---
