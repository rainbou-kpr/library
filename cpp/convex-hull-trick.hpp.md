---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo-line-add-get-min.test.cpp
    title: test/yosupo-line-add-get-min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-segment-add-get-min.test.cpp
    title: test/yosupo-segment-add-get-min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Convex Hull Trick
    links: []
  bundledCode: "#line 2 \"cpp/convex-hull-trick.hpp\"\n\n/**\n * @file convex-hull-tric.hpp\n\
    \ * @brief Convex Hull Trick\n *\n * \u4E00\u6B21\u95A2\u6570\u3067\u8868\u3055\
    \u308C\u308B\u76F4\u7DDA\u307E\u305F\u306F\u7DDA\u5206\u306E\u96C6\u5408\u3092\
    \u7BA1\u7406\u3057\u3001\u3042\u308Bx\u306B\u5BFE\u3059\u308B\u6700\u5C0F\u5024\
    \u3092\u6C42\u3081\u308B\n */\n\n#include <limits>\n#include <type_traits>\n#include\
    \ <vector>\n\n/**\n * @brief \u8FFD\u52A0\u3055\u308C\u308B\u50BE\u304D\u304C\u5358\
    \u8ABF\u3068\u306F\u9650\u3089\u306A\u3044\u5834\u5408\u306EConvex Hull Trick\n\
    \ *\n * @tparam T \u5024\u306E\u578B\n */\ntemplate <typename T, std::enable_if_t<std::is_scalar_v<T>,\
    \ std::nullptr_t> = nullptr>\nclass LiChaoTree {\n    int n, sz, height;\n   \
    \ std::vector<T> xs, as, bs;\n\n    void update(T a, T b, int k, int h) {\n  \
    \      int l = (k << h) & (sz - 1);\n        int r = l + (1 << h);\n        \n\
    \        while(1) {\n            int m = (l + r) >> 1;\n            T xl = xs[l],\
    \ xm = xs[m];\n            bool l_update = a*xl + b < as[k]*xl + bs[k];\n    \
    \        bool m_update = a*xm + b < as[k]*xm + bs[k];\n\n            if(m_update)\
    \ {\n                std::swap(as[k], a);\n                std::swap(bs[k], b);\n\
    \            }\n            if(h == 0) break;\n            if(l_update != m_update)\
    \ {\n                k = k*2;\n                r = m;\n            } else {\n\
    \                k = k*2+1;\n                l = m;\n            }\n         \
    \   h--;\n        }\n    }\n\npublic:\n    /**\n     * @brief \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     *\n     * @param xs \u6700\u5C0F\u5024\u30AF\u30A8\
    \u30EA\u306Ex\u5EA7\u6A19\u3084\u7DDA\u5206\u8FFD\u52A0\u30AF\u30A8\u30EA\u306E\
    \u4E21\u7AEF\u306Ex\u5EA7\u6A19\u3092\u5148\u8AAD\u307F\u3057\u3066\u30BD\u30FC\
    \u30C8\u3057\u305F\u914D\u5217\n     */\n    LiChaoTree(const std::vector<T>&\
    \ xs) : n(xs.size()), xs(xs) {\n        sz = 1, height = 0;\n        while(sz\
    \ < (int)xs.size()) {\n            sz <<= 1;\n            height++;\n        }\n\
    \        this->xs.resize(sz, xs.back());\n        as.assign(sz*2, 0);\n      \
    \  bs.assign(sz*2, std::numeric_limits<T>::max());\n    }\n\n    /**\n     * @brief\
    \ \u76F4\u7DDAy=ax+b\u306E\u8FFD\u52A0\n     *\n     * @param a \u50BE\u304D\n\
    \     * @param b \u5207\u7247\n     */\n    void add_line(T a, T b) {\n      \
    \  update(a, b, 1, height);\n    }\n    /**\n     * @brief \u7DDA\u5206y=ax+b\
    \ , x\u2208[xs[l],xs[r])\u306E\u8FFD\u52A0\n     *\n     * @param a \u50BE\u304D\
    \n     * @param b \u5207\u7247\n     * @param l \u5DE6\u7AEF(xs\u306E\u30A4\u30F3\
    \u30C7\u30C3\u30AF\u30B9)\n     * @param r x\u306E\u4E0A\u9650(xs\u306E\u30A4\u30F3\
    \u30C7\u30C3\u30AF\u30B9)\n     */\n    void add_segment(T a, T b, int l, int\
    \ r) {\n        if(l == r) return;\n        l += sz, r += sz;\n        int h =\
    \ 0;\n        while(l < r) {\n            if(l & 1) update(a, b, l++, h);\n  \
    \          if(r & 1) update(a, b, --r, h);\n            l >>= 1, r >>= 1, h++;\n\
    \        }\n    }\n\n    /**\n     * @brief x=xs[i]\u306B\u304A\u3051\u308B\u6700\
    \u5C0F\u5024\u3092\u6C42\u3081\u308B\n     *\n     * @param x x\u5EA7\u6A19(xs\u306E\
    \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9)\n     * @return T \u6700\u5C0F\u5024\n \
    \    */\n    T get_min(int i) const {\n        T x = xs[i];\n        int k = i\
    \ + sz;\n        T res = as[k]*x + bs[k];\n        while(k > 1) {\n          \
    \  k >>= 1;\n            T tmp = as[k]*x + bs[k];\n            if(tmp < res) res\
    \ = tmp;\n        }\n        return res;\n    }\n};\n"
  code: "#pragma once\n\n/**\n * @file convex-hull-tric.hpp\n * @brief Convex Hull\
    \ Trick\n *\n * \u4E00\u6B21\u95A2\u6570\u3067\u8868\u3055\u308C\u308B\u76F4\u7DDA\
    \u307E\u305F\u306F\u7DDA\u5206\u306E\u96C6\u5408\u3092\u7BA1\u7406\u3057\u3001\
    \u3042\u308Bx\u306B\u5BFE\u3059\u308B\u6700\u5C0F\u5024\u3092\u6C42\u3081\u308B\
    \n */\n\n#include <limits>\n#include <type_traits>\n#include <vector>\n\n/**\n\
    \ * @brief \u8FFD\u52A0\u3055\u308C\u308B\u50BE\u304D\u304C\u5358\u8ABF\u3068\u306F\
    \u9650\u3089\u306A\u3044\u5834\u5408\u306EConvex Hull Trick\n *\n * @tparam T\
    \ \u5024\u306E\u578B\n */\ntemplate <typename T, std::enable_if_t<std::is_scalar_v<T>,\
    \ std::nullptr_t> = nullptr>\nclass LiChaoTree {\n    int n, sz, height;\n   \
    \ std::vector<T> xs, as, bs;\n\n    void update(T a, T b, int k, int h) {\n  \
    \      int l = (k << h) & (sz - 1);\n        int r = l + (1 << h);\n        \n\
    \        while(1) {\n            int m = (l + r) >> 1;\n            T xl = xs[l],\
    \ xm = xs[m];\n            bool l_update = a*xl + b < as[k]*xl + bs[k];\n    \
    \        bool m_update = a*xm + b < as[k]*xm + bs[k];\n\n            if(m_update)\
    \ {\n                std::swap(as[k], a);\n                std::swap(bs[k], b);\n\
    \            }\n            if(h == 0) break;\n            if(l_update != m_update)\
    \ {\n                k = k*2;\n                r = m;\n            } else {\n\
    \                k = k*2+1;\n                l = m;\n            }\n         \
    \   h--;\n        }\n    }\n\npublic:\n    /**\n     * @brief \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     *\n     * @param xs \u6700\u5C0F\u5024\u30AF\u30A8\
    \u30EA\u306Ex\u5EA7\u6A19\u3084\u7DDA\u5206\u8FFD\u52A0\u30AF\u30A8\u30EA\u306E\
    \u4E21\u7AEF\u306Ex\u5EA7\u6A19\u3092\u5148\u8AAD\u307F\u3057\u3066\u30BD\u30FC\
    \u30C8\u3057\u305F\u914D\u5217\n     */\n    LiChaoTree(const std::vector<T>&\
    \ xs) : n(xs.size()), xs(xs) {\n        sz = 1, height = 0;\n        while(sz\
    \ < (int)xs.size()) {\n            sz <<= 1;\n            height++;\n        }\n\
    \        this->xs.resize(sz, xs.back());\n        as.assign(sz*2, 0);\n      \
    \  bs.assign(sz*2, std::numeric_limits<T>::max());\n    }\n\n    /**\n     * @brief\
    \ \u76F4\u7DDAy=ax+b\u306E\u8FFD\u52A0\n     *\n     * @param a \u50BE\u304D\n\
    \     * @param b \u5207\u7247\n     */\n    void add_line(T a, T b) {\n      \
    \  update(a, b, 1, height);\n    }\n    /**\n     * @brief \u7DDA\u5206y=ax+b\
    \ , x\u2208[xs[l],xs[r])\u306E\u8FFD\u52A0\n     *\n     * @param a \u50BE\u304D\
    \n     * @param b \u5207\u7247\n     * @param l \u5DE6\u7AEF(xs\u306E\u30A4\u30F3\
    \u30C7\u30C3\u30AF\u30B9)\n     * @param r x\u306E\u4E0A\u9650(xs\u306E\u30A4\u30F3\
    \u30C7\u30C3\u30AF\u30B9)\n     */\n    void add_segment(T a, T b, int l, int\
    \ r) {\n        if(l == r) return;\n        l += sz, r += sz;\n        int h =\
    \ 0;\n        while(l < r) {\n            if(l & 1) update(a, b, l++, h);\n  \
    \          if(r & 1) update(a, b, --r, h);\n            l >>= 1, r >>= 1, h++;\n\
    \        }\n    }\n\n    /**\n     * @brief x=xs[i]\u306B\u304A\u3051\u308B\u6700\
    \u5C0F\u5024\u3092\u6C42\u3081\u308B\n     *\n     * @param x x\u5EA7\u6A19(xs\u306E\
    \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9)\n     * @return T \u6700\u5C0F\u5024\n \
    \    */\n    T get_min(int i) const {\n        T x = xs[i];\n        int k = i\
    \ + sz;\n        T res = as[k]*x + bs[k];\n        while(k > 1) {\n          \
    \  k >>= 1;\n            T tmp = as[k]*x + bs[k];\n            if(tmp < res) res\
    \ = tmp;\n        }\n        return res;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: cpp/convex-hull-trick.hpp
  requiredBy: []
  timestamp: '2023-06-19 07:11:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-line-add-get-min.test.cpp
  - test/yosupo-segment-add-get-min.test.cpp
documentation_of: cpp/convex-hull-trick.hpp
layout: document
redirect_from:
- /library/cpp/convex-hull-trick.hpp
- /library/cpp/convex-hull-trick.hpp.html
title: Convex Hull Trick
---
