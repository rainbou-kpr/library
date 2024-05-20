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
    path: test/yosupo-rectangle-sum.test.cpp
    title: test/yosupo-rectangle-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30DE\u30FC\u30B8\u30BD\u30FC\u30C8\u30C4\u30EA\u30FC"
    links: []
  bundledCode: "#line 2 \"cpp/merge-sort-tree.hpp\"\n\n/**\n * @file merge-sort-tree.hpp\n\
    \ * @brief \u30DE\u30FC\u30B8\u30BD\u30FC\u30C8\u30C4\u30EA\u30FC\n */\n#include\
    \ <algorithm>\n#include <cassert>\n#include <functional>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n#line 2 \"cpp/more_functional.hpp\"\n\n\
    /**\n * @file more_functional.hpp\n * @brief \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\
    \u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\u308B\n */\n\n#include <limits>\n#include\
    \ <numeric>\n#include <type_traits>\n\nnamespace more_functional {\ntemplate <typename\
    \ S>\nstruct Max {\n    const S operator()(const S& a, const S& b) const { return\
    \ std::max(a, b); }\n};\ntemplate <typename S>\nstruct Min {\n    const S operator()(const\
    \ S& a, const S& b) const { return std::min(a, b); }\n};\ntemplate <typename S,\
    \ std::enable_if_t<std::is_integral_v<S>>* = nullptr>\nstruct Gcd {\n    constexpr\
    \ S operator()(const S& a, const S& b) const { return std::gcd(a, b); }\n};\n\
    template <typename S>\nstruct Zero {\n    S operator()() const { return S(0);\
    \ }\n};\ntemplate <typename S>\nstruct One {\n    S operator()() const { return\
    \ S(1); }\n};\ntemplate <typename S>\nstruct None {\n    S operator()() const\
    \ { return S{}; }\n};\ntemplate <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\nstruct MaxLimit {\n    constexpr S operator()() const { return std::numeric_limits<S>::max();\
    \ }\n};\ntemplate <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\n\
    struct MinLimit {\n    constexpr S operator()() const { return std::numeric_limits<S>::lowest();\
    \ }\n};\ntemplate <typename S>\nstruct Div {\n    S operator()(const S& a) const\
    \ { return S(1) / a; }\n};\n}  // namespace more_functional\n#line 14 \"cpp/merge-sort-tree.hpp\"\
    \n\n/**\n * @brief \u533A\u9593\u306E\u95BE\u5024\u4EE5\u5185\u306E\u5024\u306E\
    \u7A4D\n *\n * @tparam S value_type \u53EF\u63DB\u7FA4\u306E\u578B\n * @tparam\
    \ K key_type \u30BD\u30FC\u30C8\u306B\u4F7F\u3046\u578B\n * @tparam Op S\u306E\
    \u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam E S\u306E\u5358\u4F4D\u5143\
    \u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam Inv S\u306E\u9006\
    \u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam Comp K\u3092\
    \u6BD4\u8F03\u3059\u308B\u30D5\u30A1\u30F3\u30AF\u30BF\n */\ntemplate <typename\
    \ S, typename K, class Op, class E, class Inv, class Comp = std::less<K>>\nclass\
    \ MergeSortTree {\n   public:\n    using value_type = S;\n    using key_type =\
    \ K;\n\n    inline constexpr static auto op = Op();\n    inline constexpr static\
    \ auto inv = Inv();\n    inline constexpr static auto e = E();\n    inline constexpr\
    \ static auto comp = Comp();\n\n   private:\n    int n, sz, height;\n    std::vector<key_type>\
    \ key_data;\n    std::vector<value_type> cumulative_value;\n\n    void initialize(const\
    \ std::vector<value_type>& value, const std::vector<key_type>& key) {\n      \
    \  n = key.size();\n        sz = 1;\n        height = 1;\n        while (sz <\
    \ n) {\n            sz <<= 1;\n            height++;\n        }\n        key_data.assign(sz\
    \ * height, {});\n        std::vector<value_type> value_data(sz * height, e());\n\
    \        cumulative_value.assign(sz * height, {});\n        for (int i = 0; i\
    \ < n; i++) {\n            key_data[(height - 1) * sz + i] = key[i];\n       \
    \     value_data[(height - 1) * sz + i] = value[i];\n            cumulative_value[(height\
    \ - 1) * sz + i] = value[i];\n        }\n        int t = 1;\n        for (int\
    \ h = height - 1; h > 0; h--) {\n            for (int i = 0; i < n; i += t * 2)\
    \ {\n                int j1 = h * sz + i;\n                int j2 = h * sz + std::min(n,\
    \ i + t);\n                int j0 = (h - 1) * sz + i;\n                int last1\
    \ = j2;\n                int last2 = h * sz + std::min(n, i + t * 2);\n      \
    \          while (j1 != last1 || j2 != last2) {\n                    if (j1 ==\
    \ last1 || (j2 < last2 && comp(key_data[j2], key_data[j1]))) {\n             \
    \           key_data[j0] = key_data[j2];\n                        value_data[j0]\
    \ = value_data[j2];\n                        j0++;\n                        j2++;\n\
    \                    } else {\n                        key_data[j0] = key_data[j1];\n\
    \                        value_data[j0] = value_data[j1];\n                  \
    \      j0++;\n                        j1++;\n                    }\n         \
    \       }\n                cumulative_value[(h - 1) * sz + i] = value_data[(h\
    \ - 1) * sz + i];\n                for (int j = i + 1; j < std::min(n, i + t *\
    \ 2); j++) {\n                    cumulative_value[(h - 1) * sz + j] = op(cumulative_value[(h\
    \ - 1) * sz + j - 1], value_data[(h - 1) * sz + j]);\n                }\n    \
    \        }\n            t <<= 1;\n        }\n    }\n\n    value_type prod_section(int\
    \ l, int r, std::optional<key_type> a, std::optional<key_type> b) const {\n  \
    \      value_type ret = cumulative_value[r - 1];\n        if (b.has_value()) {\n\
    \            int i = std::lower_bound(key_data.begin() + l, key_data.begin() +\
    \ r, b.value(), comp) - key_data.begin();\n            if (i != l) {\n       \
    \         ret = cumulative_value[i - 1];\n            } else {\n             \
    \   ret = e();\n            }\n        }\n        if (a.has_value()) {\n     \
    \       int i = std::lower_bound(key_data.begin() + l, key_data.begin() + r, a.value(),\
    \ comp) - key_data.begin();\n            if (i != l) {\n                ret =\
    \ op(ret, inv(cumulative_value[i - 1]));\n            }\n        }\n        return\
    \ ret;\n    }\n\n   public:\n    MergeSortTree() = default;\n    /**\n     * @param\
    \ value_key value\u3068key\u306Epair\u306Evector\n     */\n    explicit MergeSortTree(const\
    \ std::vector<std::pair<value_type, key_type>>& value_key) {\n        std::vector<key_type>\
    \ key;\n        std::vector<value_type> value;\n        key.reserve(value_key.size());\n\
    \        value.reserve(value_key.size());\n        for (size_t i = 0; i < value_key.size();\
    \ i++) {\n            value.push_back(value_key[i].first);\n            key.push_back(value_key[i].second);\n\
    \        }\n        this->initialize(value, key);\n    }\n    /**\n     * @param\
    \ value prod\u3067\u8A08\u7B97\u3059\u308B\u5BFE\u8C61\n     * @param key \u30BD\
    \u30FC\u30C8\u3059\u308B\u57FA\u6E96\n     */\n    MergeSortTree(const std::vector<value_type>&\
    \ value, const std::vector<key_type>& key) {\n        assert(key.size() == value.size());\n\
    \        this->initialize(value, key);\n    }\n\n    /**\n     * @brief product\
    \ value[i] s.t. a <= key[i] < b , i in [l, r)\n     *\n     * @param l \u534A\u958B\
    \u533A\u9593\u306E\u958B\u59CB\n     * @param r \u534A\u958B\u533A\u9593\u306E\
    \u7D42\u7AEF 0<=l<=r<=n\n     * @param a nullopt\u306E\u5834\u5408\u306F\u8CA0\
    \u306E\u7121\u9650\u5927\n     * @param b nullopt\u306E\u5834\u5408\u306F\u6B63\
    \u306E\u7121\u9650\u5927\n     */\n    value_type prod(int l, int r, std::optional<key_type>\
    \ a = std::nullopt, std::optional<key_type> b = std::nullopt) const {\n      \
    \  assert(0 <= l && l <= r && r <= n);\n        if (a.has_value() && b.has_value()\
    \ && !comp(a.value(), b.value())) return e();\n        value_type ret = e();\n\
    \        int h = height - 1;\n        int t = 1;\n        while (l < r) {\n  \
    \          if (l & t) {\n                ret = op(ret, prod_section(h * sz + l,\
    \ h * sz + l + t, a, b));\n                l += t;\n            }\n          \
    \  if (r & t) {\n                r -= t;\n                ret = op(ret, prod_section(h\
    \ * sz + r, h * sz + r + t, a, b));\n            }\n            h--;\n       \
    \     t <<= 1;\n        }\n        return ret;\n    }\n};\n\n/**\n * @tparam S\
    \ \u53EF\u63DB\u7FA4\u306E\u578B\n * @tparam K \u30BD\u30FC\u30C8\u306B\u4F7F\u3046\
    \u578B\n */\ntemplate <typename S, typename K>\nusing MSTreeSum = MergeSortTree<S,\
    \ K, std::plus<S>, more_functional::None<S>, std::negate<S>, std::less<K>>;\n\
    /**\n * @tparam S \u53EF\u63DB\u7FA4\u306E\u578B\n * @tparam K \u30BD\u30FC\u30C8\
    \u306B\u4F7F\u3046\u578B\n */\ntemplate <typename S, typename K>\nusing MSTreeProd\
    \ = MergeSortTree<S, K, std::multiplies<S>, more_functional::One<S>, more_functional::Div<S>,\
    \ std::less<K>>;\n"
  code: "#pragma once\n\n/**\n * @file merge-sort-tree.hpp\n * @brief \u30DE\u30FC\
    \u30B8\u30BD\u30FC\u30C8\u30C4\u30EA\u30FC\n */\n#include <algorithm>\n#include\
    \ <cassert>\n#include <functional>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n#include \"more_functional.hpp\"\n\n/**\n * @brief \u533A\u9593\
    \u306E\u95BE\u5024\u4EE5\u5185\u306E\u5024\u306E\u7A4D\n *\n * @tparam S value_type\
    \ \u53EF\u63DB\u7FA4\u306E\u578B\n * @tparam K key_type \u30BD\u30FC\u30C8\u306B\
    \u4F7F\u3046\u578B\n * @tparam Op S\u306E\u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\
    \n * @tparam E S\u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\
    \u30BF\n * @tparam Inv S\u306E\u9006\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\
    \u30AF\u30BF\n * @tparam Comp K\u3092\u6BD4\u8F03\u3059\u308B\u30D5\u30A1\u30F3\
    \u30AF\u30BF\n */\ntemplate <typename S, typename K, class Op, class E, class\
    \ Inv, class Comp = std::less<K>>\nclass MergeSortTree {\n   public:\n    using\
    \ value_type = S;\n    using key_type = K;\n\n    inline constexpr static auto\
    \ op = Op();\n    inline constexpr static auto inv = Inv();\n    inline constexpr\
    \ static auto e = E();\n    inline constexpr static auto comp = Comp();\n\n  \
    \ private:\n    int n, sz, height;\n    std::vector<key_type> key_data;\n    std::vector<value_type>\
    \ cumulative_value;\n\n    void initialize(const std::vector<value_type>& value,\
    \ const std::vector<key_type>& key) {\n        n = key.size();\n        sz = 1;\n\
    \        height = 1;\n        while (sz < n) {\n            sz <<= 1;\n      \
    \      height++;\n        }\n        key_data.assign(sz * height, {});\n     \
    \   std::vector<value_type> value_data(sz * height, e());\n        cumulative_value.assign(sz\
    \ * height, {});\n        for (int i = 0; i < n; i++) {\n            key_data[(height\
    \ - 1) * sz + i] = key[i];\n            value_data[(height - 1) * sz + i] = value[i];\n\
    \            cumulative_value[(height - 1) * sz + i] = value[i];\n        }\n\
    \        int t = 1;\n        for (int h = height - 1; h > 0; h--) {\n        \
    \    for (int i = 0; i < n; i += t * 2) {\n                int j1 = h * sz + i;\n\
    \                int j2 = h * sz + std::min(n, i + t);\n                int j0\
    \ = (h - 1) * sz + i;\n                int last1 = j2;\n                int last2\
    \ = h * sz + std::min(n, i + t * 2);\n                while (j1 != last1 || j2\
    \ != last2) {\n                    if (j1 == last1 || (j2 < last2 && comp(key_data[j2],\
    \ key_data[j1]))) {\n                        key_data[j0] = key_data[j2];\n  \
    \                      value_data[j0] = value_data[j2];\n                    \
    \    j0++;\n                        j2++;\n                    } else {\n    \
    \                    key_data[j0] = key_data[j1];\n                        value_data[j0]\
    \ = value_data[j1];\n                        j0++;\n                        j1++;\n\
    \                    }\n                }\n                cumulative_value[(h\
    \ - 1) * sz + i] = value_data[(h - 1) * sz + i];\n                for (int j =\
    \ i + 1; j < std::min(n, i + t * 2); j++) {\n                    cumulative_value[(h\
    \ - 1) * sz + j] = op(cumulative_value[(h - 1) * sz + j - 1], value_data[(h -\
    \ 1) * sz + j]);\n                }\n            }\n            t <<= 1;\n   \
    \     }\n    }\n\n    value_type prod_section(int l, int r, std::optional<key_type>\
    \ a, std::optional<key_type> b) const {\n        value_type ret = cumulative_value[r\
    \ - 1];\n        if (b.has_value()) {\n            int i = std::lower_bound(key_data.begin()\
    \ + l, key_data.begin() + r, b.value(), comp) - key_data.begin();\n          \
    \  if (i != l) {\n                ret = cumulative_value[i - 1];\n           \
    \ } else {\n                ret = e();\n            }\n        }\n        if (a.has_value())\
    \ {\n            int i = std::lower_bound(key_data.begin() + l, key_data.begin()\
    \ + r, a.value(), comp) - key_data.begin();\n            if (i != l) {\n     \
    \           ret = op(ret, inv(cumulative_value[i - 1]));\n            }\n    \
    \    }\n        return ret;\n    }\n\n   public:\n    MergeSortTree() = default;\n\
    \    /**\n     * @param value_key value\u3068key\u306Epair\u306Evector\n     */\n\
    \    explicit MergeSortTree(const std::vector<std::pair<value_type, key_type>>&\
    \ value_key) {\n        std::vector<key_type> key;\n        std::vector<value_type>\
    \ value;\n        key.reserve(value_key.size());\n        value.reserve(value_key.size());\n\
    \        for (size_t i = 0; i < value_key.size(); i++) {\n            value.push_back(value_key[i].first);\n\
    \            key.push_back(value_key[i].second);\n        }\n        this->initialize(value,\
    \ key);\n    }\n    /**\n     * @param value prod\u3067\u8A08\u7B97\u3059\u308B\
    \u5BFE\u8C61\n     * @param key \u30BD\u30FC\u30C8\u3059\u308B\u57FA\u6E96\n \
    \    */\n    MergeSortTree(const std::vector<value_type>& value, const std::vector<key_type>&\
    \ key) {\n        assert(key.size() == value.size());\n        this->initialize(value,\
    \ key);\n    }\n\n    /**\n     * @brief product value[i] s.t. a <= key[i] < b\
    \ , i in [l, r)\n     *\n     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\
    \n     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF 0<=l<=r<=n\n    \
    \ * @param a nullopt\u306E\u5834\u5408\u306F\u8CA0\u306E\u7121\u9650\u5927\n \
    \    * @param b nullopt\u306E\u5834\u5408\u306F\u6B63\u306E\u7121\u9650\u5927\n\
    \     */\n    value_type prod(int l, int r, std::optional<key_type> a = std::nullopt,\
    \ std::optional<key_type> b = std::nullopt) const {\n        assert(0 <= l &&\
    \ l <= r && r <= n);\n        if (a.has_value() && b.has_value() && !comp(a.value(),\
    \ b.value())) return e();\n        value_type ret = e();\n        int h = height\
    \ - 1;\n        int t = 1;\n        while (l < r) {\n            if (l & t) {\n\
    \                ret = op(ret, prod_section(h * sz + l, h * sz + l + t, a, b));\n\
    \                l += t;\n            }\n            if (r & t) {\n          \
    \      r -= t;\n                ret = op(ret, prod_section(h * sz + r, h * sz\
    \ + r + t, a, b));\n            }\n            h--;\n            t <<= 1;\n  \
    \      }\n        return ret;\n    }\n};\n\n/**\n * @tparam S \u53EF\u63DB\u7FA4\
    \u306E\u578B\n * @tparam K \u30BD\u30FC\u30C8\u306B\u4F7F\u3046\u578B\n */\ntemplate\
    \ <typename S, typename K>\nusing MSTreeSum = MergeSortTree<S, K, std::plus<S>,\
    \ more_functional::None<S>, std::negate<S>, std::less<K>>;\n/**\n * @tparam S\
    \ \u53EF\u63DB\u7FA4\u306E\u578B\n * @tparam K \u30BD\u30FC\u30C8\u306B\u4F7F\u3046\
    \u578B\n */\ntemplate <typename S, typename K>\nusing MSTreeProd = MergeSortTree<S,\
    \ K, std::multiplies<S>, more_functional::One<S>, more_functional::Div<S>, std::less<K>>;\n"
  dependsOn:
  - cpp/more_functional.hpp
  isVerificationFile: false
  path: cpp/merge-sort-tree.hpp
  requiredBy: []
  timestamp: '2024-05-17 22:45:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-rectangle-sum.test.cpp
documentation_of: cpp/merge-sort-tree.hpp
layout: document
redirect_from:
- /library/cpp/merge-sort-tree.hpp
- /library/cpp/merge-sort-tree.hpp.html
title: "\u30DE\u30FC\u30B8\u30BD\u30FC\u30C8\u30C4\u30EA\u30FC"
---
