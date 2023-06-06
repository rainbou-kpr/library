---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-a.test.cpp
    title: test/aoj-dsl-2-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-b.test.cpp
    title: test/aoj-dsl-2-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-lca.2.test.cpp
    title: test/yosupo-lca.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-point-set-range-composite.1.test.cpp
    title: test/yosupo-point-set-range-composite.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-point-set-range-composite.2.test.cpp
    title: test/yosupo-point-set-range-composite.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "#line 2 \"cpp/segtree.hpp\"\n\n/**\n * @file segtree.hpp\n * @brief\
    \ \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n */\n\n#include <cassert>\n#include <functional>\n\
    #include <limits>\n#include <ostream>\n#include <vector>\n\n/**\n * @brief \u30BB\
    \u30B0\u30E1\u30F3\u30C8\u6728\u306ECRTP\u57FA\u5E95\u30AF\u30E9\u30B9\n * \n\
    \ * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\n * @tparam ActualSegTree \u6D3E\
    \u751F\u30AF\u30E9\u30B9\n */\ntemplate <typename S, typename ActualSegTree>\n\
    class SegTreeBase {\n    S op(const S& a, const S& b) const { return static_cast<const\
    \ ActualSegTree&>(*this).op(a, b); }\n    S e() const { return static_cast<const\
    \ ActualSegTree&>(*this).e(); }\n\n    int n, sz, height;\n    std::vector<S>\
    \ data;\n    void update(int k) { data[k] = op(data[2 * k], data[2 * k + 1]);\
    \ }\n\n    class SegTreeReference {\n        SegTreeBase& segtree;\n        int\
    \ k;\n    public:\n        SegTreeReference(SegTreeBase& segtree, int k) : segtree(segtree),\
    \ k(k) {}\n        SegTreeReference& operator=(const S& x) {\n            segtree.set(k,\
    \ x);\n            return *this;\n        }\n        operator S() const { return\
    \ segtree.get(k); }\n    };\n\nprotected:\n    void construct_data() {\n     \
    \   sz = 1;\n        height = 0;\n        while (sz < n) {\n            sz <<=\
    \ 1;\n            height++;\n        }\n        data.assign(sz * 2, e());\n  \
    \  }\n    void initialize(const std::vector<S>& v) {\n        for (int i = 0;\
    \ i < n; i++) data[sz + i] = v[i];\n        for (int i = sz - 1; i > 0; i--) update(i);\n\
    \    }\n\npublic:\n    // Warning: \u7D99\u627F\u5148\u306E\u30B3\u30F3\u30B9\u30C8\
    \u30E9\u30AF\u30BF\u3067construct_data()\u3092\u5FC5\u305A\u547C\u3073\u51FA\u3059\
    \uFF01\n    SegTreeBase(int n = 0) : n(n) {}\n\n    /**\n     * @brief \u6307\u5B9A\
    \u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u3092\u8FD4\u3059\n     * \n     *\
    \ @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @return S \u5024\n   \
    \  */\n    S get(int k) const { return data[sz + k]; }\n    /**\n     * @brief\
    \ \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u3092\u8FD4\u3059\n \
    \    * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @return\
    \ S \u5024\n     */\n    S operator[] (int k) const { return get(k); }\n    /**\n\
    \     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u3078\u306E\u53C2\u7167\
    \u3092\u8FD4\u3059\n     * \n     * @param k \n     * @return SegTreeReference\
    \ \u8981\u7D20\u3078\u306E\u53C2\u7167 \u4EE3\u5165\u3055\u308C\u308B\u3068set()\u304C\
    \u547C\u3070\u308C\u308B\n     */\n    SegTreeReference operator[] (int k) { return\
    \ SegTreeReference(*this, k); }\n\n    /**\n     * @brief \u5185\u5BB9\u3092\u51FA\
    \u529B\u3059\u308B\n     * \n     * @tparam CharT \u51FA\u529B\u30B9\u30C8\u30EA\
    \u30FC\u30E0\u306E\u6587\u5B57\u578B\n     * @tparam Traits \u51FA\u529B\u30B9\
    \u30C8\u30EA\u30FC\u30E0\u306E\u6587\u5B57\u578B\u7279\u6027\n     * @param os\
    \ \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\n     * @param rhs \u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\n     * @return std::basic_ostream<CharT, Traits>& \u51FA\u529B\
    \u30B9\u30C8\u30EA\u30FC\u30E0 \n     */\n    template <class CharT, class Traits>\n\
    \    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT,\
    \ Traits>& os, const SegTreeBase& rhs) {\n        for(int i = 0; i < rhs.n; i++)\
    \ {\n            if(i != 0) os << CharT(' ');\n            os << rhs[i];\n   \
    \     }\n        return os;\n    }\n\n    /**\n     * @brief \u6307\u5B9A\u3055\
    \u308C\u305F\u8981\u7D20\u306E\u5024\u3092x\u306B\u66F4\u65B0\u3059\u308B\n  \
    \   * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @param x\
    \ \u65B0\u3057\u3044\u5024\n     */\n    void set(int k, const S& x) {\n     \
    \   k += sz;\n        data[k] = x;\n        for (int i = 1; i <= height; i++)\
    \ update(k >> i);\n    }\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\
    \u8981\u7D20\u306E\u5024\u306Bx\u3092\u4F5C\u7528\u3055\u305B\u308B\n     * \n\
    \     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @param x \u4F5C\u7528\
    \u7D20\n     */\n    void apply(int k, const S& x) { set(k, op(get(k), x)); }\n\
    \n    /**\n     * @brief [l, r)\u306E\u533A\u9593\u306E\u7DCF\u7A4D\u3092\u8FD4\
    \u3059\n     * \n     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n\
    \     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @return S\
    \ \u7DCF\u7A4D\n     */\n    S prod(int l, int r) const {\n        S left_prod\
    \ = e(), right_prod = e();\n        l += sz;\n        r += sz;\n        while\
    \ (l < r) {\n            if (l & 1) left_prod = op(left_prod, data[l++]);\n  \
    \          if (r & 1) right_prod = op(data[--r], right_prod);\n            l >>=\
    \ 1;\n            r >>= 1;\n        }\n        return op(left_prod, right_prod);\n\
    \    }\n    /**\n     * @brief \u3059\u3079\u3066\u306E\u8981\u7D20\u306E\u7DCF\
    \u7A4D\u3092\u8FD4\u3059\n     * \n     * @return S \u7DCF\u7A4D\n     */\n  \
    \  S all_prod() const { return data[1]; }\n\n    /**\n     * @brief (r = l or\
    \ f(prod([l, r))) = true) and (r = n or f(prod([l, r+1))) = false)\u3068\u306A\
    \u308Br\u3092\u8FD4\u3059\n     * f\u304C\u5358\u8ABF\u306A\u3089\u3001f(prod([l,\
    \ r))) = true\u3068\u306A\u308B\u6700\u5927\u306Er\n     * \n     * @tparam F\n\
    \     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n     * @param f \u5224\
    \u5B9A\u95A2\u6570 f(e) = true\n     * @return int\n     */\n    template <typename\
    \ F>\n    int max_right(int l, F f) const {\n        assert(f(e()));\n       \
    \ if (l == n) return n;\n        l += sz;\n        while (l % 2 == 0) l >>= 1;\n\
    \        S sum = e();\n        while(f(op(sum, data[l]))) {\n            if (__builtin_clz(l)\
    \ != __builtin_clz(l+1)) return n;\n            sum = op(sum, data[l]);\n    \
    \        l++;\n            while (l % 2 == 0) l >>= 1;\n        }\n        while\
    \ (l < sz) {\n            if (!f(op(sum, data[l * 2]))) l *= 2;\n            else\
    \ {\n                sum = op(sum, data[l * 2]);\n                l = l * 2 +\
    \ 1;\n            }\n        }\n        return l - sz;\n    }\n    /**\n     *\
    \ @brief (l = 0 or f(prod([l, r))) = true) and (l = r or f(prod([l-1, r))) = false)\u3068\
    \u306A\u308Bl\u3092\u8FD4\u3059\n     * f\u304C\u5358\u8ABF\u306A\u3089\u3001\
    f(prod([l, r))) = true\u3068\u306A\u308B\u6700\u5C0F\u306El\n     * \n     * @tparam\
    \ F\n     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @param\
    \ f \u5224\u5B9A\u95A2\u6570 f(e) = true\n     * @return int\n     */\n    template\
    \ <typename F>\n    int min_left(int r, F f) const {\n        assert(f(e()));\n\
    \        if (r == 0) return 0;\n        r += sz - 1;\n        while (r % 2 ==\
    \ 1) r >>= 1;\n        S sum = e();\n        while(f(op(sum, data[r]))) {\n  \
    \          if (__builtin_clz(r) != __builtin_clz(r-1)) return 0;\n           \
    \ sum = op(sum, data[r]);\n            r--;\n            while (r % 2 == 1) r\
    \ >>= 1;\n        }\n        while (r < sz) {\n            if (!f(op(data[r *\
    \ 2 + 1], sum))) r = r * 2 + 1;\n            else {\n                sum = op(data[r\
    \ * 2 + 1], sum);\n                r *= 2;\n            }\n        }\n       \
    \ return r + 1 - sz;\n    }\n};\n\n/**\n * @brief \u7A4D\u306E\u30D5\u30A1\u30F3\
    \u30AF\u30BF\u304C\u9759\u7684\u306A\u5834\u5408\u306E\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728\u306E\u5B9F\u88C5\n * \n * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\
    \u578B\n * @tparam Op \u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam E\
    \ \u7A4D\u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\
    \n */\ntemplate <typename S, typename Op, typename E>\nclass StaticSegTree : public\
    \ SegTreeBase<S, StaticSegTree<S, Op, E>> {\n    using BaseType = SegTreeBase<S,\
    \ StaticSegTree<S, Op, E>>;\n\n    inline static Op operator_object;\n    inline\
    \ static E identity_object;\npublic:\n    S op(const S& a, const S& b) const {\
    \ return operator_object(a, b); }\n    S e() const { return identity_object();\
    \ }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * \n    */\n    StaticSegTree() = default;\n  \
    \  /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n  \
    \   * @param n \u8981\u7D20\u6570\n     */\n    explicit StaticSegTree(int n)\
    \ : BaseType(n) {\n        this->construct_data();\n    }\n    /**\n     * @brief\
    \ \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param v \u521D\u671F\
    \u306E\u8981\u7D20\n     */\n    explicit StaticSegTree(const std::vector<S>&\
    \ v) : StaticSegTree(v.size()) {\n        this->initialize(v);\n    }\n};\n\n\
    /**\n * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067\u95A2\u6570\u30AA\
    \u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u4E0E\u3048\u308B\u3053\u3068\u3067\u7A4D\
    \u3092\u5B9A\u7FA9\u3059\u308B\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u306E\u5B9F\
    \u88C5\n * \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\u5F15\u6570\u3092\u7701\u7565\u3059\
    \u308B\u3053\u3068\u304C\u3067\u304D\u3001\u30E9\u30E0\u30C0\u5F0F\u304C\u4F7F\
    \u3048\u308B\n * \n * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\n * @tparam\
    \ Op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u306E\u578B\n\
    \ */\ntemplate <typename S, typename Op>\nclass SegTree : public SegTreeBase<S,\
    \ SegTree<S, Op>> {\n    using BaseType = SegTreeBase<S, SegTree<S, Op>>;\n\n\
    \    Op operator_object;\n    S identity;\n\npublic:\n    S op(const S& a, const\
    \ S& b) const { return operator_object(a, b); }\n    S e() const { return identity;\
    \ }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n    */\n    SegTree() = default;\n    /**\n     * @brief\
    \ \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param n \u8981\u7D20\
    \u6570\n     * @param op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\
    \u30C8\n     * @param identity \u5358\u4F4D\u5143\n     */\n    explicit SegTree(int\
    \ n, Op op, const S& identity) : BaseType(n), operator_object(std::move(op)),\
    \ identity(identity) {\n        this->construct_data();\n    }\n    /**\n    \
    \ * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param\
    \ v \u521D\u671F\u306E\u8981\u7D20\n     * @param op \u7A4D\u306E\u95A2\u6570\u30AA\
    \u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param identity \u5358\u4F4D\u5143\n  \
    \   */\n    explicit SegTree(const std::vector<S>& v, Op op, const S& identity)\
    \ : SegTree(v.size(), std::move(op), identity) {\n        this->initialize(v);\n\
    \    }\n};\n\nnamespace segtree {\n    template <typename S>\n    struct Max {\n\
    \        const S operator() (const S& a, const S& b) const { return std::max(a,\
    \ b); }\n    };\n    template <typename S>\n    struct Min {\n        const S\
    \ operator() (const S& a, const S& b) const { return std::min(a, b); }\n    };\n\
    \    template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\n\
    \    struct MaxLimit {\n        constexpr S operator() () const { return std::numeric_limits<S>::max();\
    \ }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MinLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::lowest(); }\n    };\n    template <typename S>\n\
    \    struct Zero {\n        S operator() () const { return S(0); }\n    };\n}\n\
    /**\n * @brief RangeMaxQuery\n * \n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RMaxQ = StaticSegTree<S, segtree::Max<S>, segtree::MinLimit<S>>;\n\
    /**\n * @brief RangeMinQuery\n * \n * @tparam S \u578B\n */\ntemplate <typename\
    \ S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\nusing RMinQ = StaticSegTree<S,\
    \ segtree::Min<S>, segtree::MaxLimit<S>>;\n/**\n * @brief RangeSumQuery\n * \n\
    \ * @tparam S \u578B\n */\ntemplate <typename S>\nusing RSumQ = StaticSegTree<S,\
    \ std::plus<S>, segtree::Zero<S>>;\n"
  code: "#pragma once\n\n/**\n * @file segtree.hpp\n * @brief \u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728\n */\n\n#include <cassert>\n#include <functional>\n#include <limits>\n\
    #include <ostream>\n#include <vector>\n\n/**\n * @brief \u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728\u306ECRTP\u57FA\u5E95\u30AF\u30E9\u30B9\n * \n * @tparam S \u30E2\
    \u30CE\u30A4\u30C9\u306E\u578B\n * @tparam ActualSegTree \u6D3E\u751F\u30AF\u30E9\
    \u30B9\n */\ntemplate <typename S, typename ActualSegTree>\nclass SegTreeBase\
    \ {\n    S op(const S& a, const S& b) const { return static_cast<const ActualSegTree&>(*this).op(a,\
    \ b); }\n    S e() const { return static_cast<const ActualSegTree&>(*this).e();\
    \ }\n\n    int n, sz, height;\n    std::vector<S> data;\n    void update(int k)\
    \ { data[k] = op(data[2 * k], data[2 * k + 1]); }\n\n    class SegTreeReference\
    \ {\n        SegTreeBase& segtree;\n        int k;\n    public:\n        SegTreeReference(SegTreeBase&\
    \ segtree, int k) : segtree(segtree), k(k) {}\n        SegTreeReference& operator=(const\
    \ S& x) {\n            segtree.set(k, x);\n            return *this;\n       \
    \ }\n        operator S() const { return segtree.get(k); }\n    };\n\nprotected:\n\
    \    void construct_data() {\n        sz = 1;\n        height = 0;\n        while\
    \ (sz < n) {\n            sz <<= 1;\n            height++;\n        }\n      \
    \  data.assign(sz * 2, e());\n    }\n    void initialize(const std::vector<S>&\
    \ v) {\n        for (int i = 0; i < n; i++) data[sz + i] = v[i];\n        for\
    \ (int i = sz - 1; i > 0; i--) update(i);\n    }\n\npublic:\n    // Warning: \u7D99\
    \u627F\u5148\u306E\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067construct_data()\u3092\
    \u5FC5\u305A\u547C\u3073\u51FA\u3059\uFF01\n    SegTreeBase(int n = 0) : n(n)\
    \ {}\n\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\
    \u5024\u3092\u8FD4\u3059\n     * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\
    \u30B9\n     * @return S \u5024\n     */\n    S get(int k) const { return data[sz\
    \ + k]; }\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\
    \u5024\u3092\u8FD4\u3059\n     * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\
    \u30B9\n     * @return S \u5024\n     */\n    S operator[] (int k) const { return\
    \ get(k); }\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\
    \u3078\u306E\u53C2\u7167\u3092\u8FD4\u3059\n     * \n     * @param k \n     *\
    \ @return SegTreeReference \u8981\u7D20\u3078\u306E\u53C2\u7167 \u4EE3\u5165\u3055\
    \u308C\u308B\u3068set()\u304C\u547C\u3070\u308C\u308B\n     */\n    SegTreeReference\
    \ operator[] (int k) { return SegTreeReference(*this, k); }\n\n    /**\n     *\
    \ @brief \u5185\u5BB9\u3092\u51FA\u529B\u3059\u308B\n     * \n     * @tparam CharT\
    \ \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u306E\u6587\u5B57\u578B\n     * @tparam\
    \ Traits \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u306E\u6587\u5B57\u578B\u7279\
    \u6027\n     * @param os \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\n     * @param\
    \ rhs \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n     * @return std::basic_ostream<CharT,\
    \ Traits>& \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0 \n     */\n    template\
    \ <class CharT, class Traits>\n    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT,\
    \ Traits>& os, const SegTreeBase& rhs) {\n        for(int i = 0; i < rhs.n; i++)\
    \ {\n            if(i != 0) os << CharT(' ');\n            os << rhs[i];\n   \
    \     }\n        return os;\n    }\n\n    /**\n     * @brief \u6307\u5B9A\u3055\
    \u308C\u305F\u8981\u7D20\u306E\u5024\u3092x\u306B\u66F4\u65B0\u3059\u308B\n  \
    \   * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @param x\
    \ \u65B0\u3057\u3044\u5024\n     */\n    void set(int k, const S& x) {\n     \
    \   k += sz;\n        data[k] = x;\n        for (int i = 1; i <= height; i++)\
    \ update(k >> i);\n    }\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\
    \u8981\u7D20\u306E\u5024\u306Bx\u3092\u4F5C\u7528\u3055\u305B\u308B\n     * \n\
    \     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n     * @param x \u4F5C\u7528\
    \u7D20\n     */\n    void apply(int k, const S& x) { set(k, op(get(k), x)); }\n\
    \n    /**\n     * @brief [l, r)\u306E\u533A\u9593\u306E\u7DCF\u7A4D\u3092\u8FD4\
    \u3059\n     * \n     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n\
    \     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @return S\
    \ \u7DCF\u7A4D\n     */\n    S prod(int l, int r) const {\n        S left_prod\
    \ = e(), right_prod = e();\n        l += sz;\n        r += sz;\n        while\
    \ (l < r) {\n            if (l & 1) left_prod = op(left_prod, data[l++]);\n  \
    \          if (r & 1) right_prod = op(data[--r], right_prod);\n            l >>=\
    \ 1;\n            r >>= 1;\n        }\n        return op(left_prod, right_prod);\n\
    \    }\n    /**\n     * @brief \u3059\u3079\u3066\u306E\u8981\u7D20\u306E\u7DCF\
    \u7A4D\u3092\u8FD4\u3059\n     * \n     * @return S \u7DCF\u7A4D\n     */\n  \
    \  S all_prod() const { return data[1]; }\n\n    /**\n     * @brief (r = l or\
    \ f(prod([l, r))) = true) and (r = n or f(prod([l, r+1))) = false)\u3068\u306A\
    \u308Br\u3092\u8FD4\u3059\n     * f\u304C\u5358\u8ABF\u306A\u3089\u3001f(prod([l,\
    \ r))) = true\u3068\u306A\u308B\u6700\u5927\u306Er\n     * \n     * @tparam F\n\
    \     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n     * @param f \u5224\
    \u5B9A\u95A2\u6570 f(e) = true\n     * @return int\n     */\n    template <typename\
    \ F>\n    int max_right(int l, F f) const {\n        assert(f(e()));\n       \
    \ if (l == n) return n;\n        l += sz;\n        while (l % 2 == 0) l >>= 1;\n\
    \        S sum = e();\n        while(f(op(sum, data[l]))) {\n            if (__builtin_clz(l)\
    \ != __builtin_clz(l+1)) return n;\n            sum = op(sum, data[l]);\n    \
    \        l++;\n            while (l % 2 == 0) l >>= 1;\n        }\n        while\
    \ (l < sz) {\n            if (!f(op(sum, data[l * 2]))) l *= 2;\n            else\
    \ {\n                sum = op(sum, data[l * 2]);\n                l = l * 2 +\
    \ 1;\n            }\n        }\n        return l - sz;\n    }\n    /**\n     *\
    \ @brief (l = 0 or f(prod([l, r))) = true) and (l = r or f(prod([l-1, r))) = false)\u3068\
    \u306A\u308Bl\u3092\u8FD4\u3059\n     * f\u304C\u5358\u8ABF\u306A\u3089\u3001\
    f(prod([l, r))) = true\u3068\u306A\u308B\u6700\u5C0F\u306El\n     * \n     * @tparam\
    \ F\n     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @param\
    \ f \u5224\u5B9A\u95A2\u6570 f(e) = true\n     * @return int\n     */\n    template\
    \ <typename F>\n    int min_left(int r, F f) const {\n        assert(f(e()));\n\
    \        if (r == 0) return 0;\n        r += sz - 1;\n        while (r % 2 ==\
    \ 1) r >>= 1;\n        S sum = e();\n        while(f(op(sum, data[r]))) {\n  \
    \          if (__builtin_clz(r) != __builtin_clz(r-1)) return 0;\n           \
    \ sum = op(sum, data[r]);\n            r--;\n            while (r % 2 == 1) r\
    \ >>= 1;\n        }\n        while (r < sz) {\n            if (!f(op(data[r *\
    \ 2 + 1], sum))) r = r * 2 + 1;\n            else {\n                sum = op(data[r\
    \ * 2 + 1], sum);\n                r *= 2;\n            }\n        }\n       \
    \ return r + 1 - sz;\n    }\n};\n\n/**\n * @brief \u7A4D\u306E\u30D5\u30A1\u30F3\
    \u30AF\u30BF\u304C\u9759\u7684\u306A\u5834\u5408\u306E\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728\u306E\u5B9F\u88C5\n * \n * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\
    \u578B\n * @tparam Op \u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam E\
    \ \u7A4D\u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\
    \n */\ntemplate <typename S, typename Op, typename E>\nclass StaticSegTree : public\
    \ SegTreeBase<S, StaticSegTree<S, Op, E>> {\n    using BaseType = SegTreeBase<S,\
    \ StaticSegTree<S, Op, E>>;\n\n    inline static Op operator_object;\n    inline\
    \ static E identity_object;\npublic:\n    S op(const S& a, const S& b) const {\
    \ return operator_object(a, b); }\n    S e() const { return identity_object();\
    \ }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n     * \n    */\n    StaticSegTree() = default;\n  \
    \  /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n  \
    \   * @param n \u8981\u7D20\u6570\n     */\n    explicit StaticSegTree(int n)\
    \ : BaseType(n) {\n        this->construct_data();\n    }\n    /**\n     * @brief\
    \ \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param v \u521D\u671F\
    \u306E\u8981\u7D20\n     */\n    explicit StaticSegTree(const std::vector<S>&\
    \ v) : StaticSegTree(v.size()) {\n        this->initialize(v);\n    }\n};\n\n\
    /**\n * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067\u95A2\u6570\u30AA\
    \u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u4E0E\u3048\u308B\u3053\u3068\u3067\u7A4D\
    \u3092\u5B9A\u7FA9\u3059\u308B\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u306E\u5B9F\
    \u88C5\n * \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\u5F15\u6570\u3092\u7701\u7565\u3059\
    \u308B\u3053\u3068\u304C\u3067\u304D\u3001\u30E9\u30E0\u30C0\u5F0F\u304C\u4F7F\
    \u3048\u308B\n * \n * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\n * @tparam\
    \ Op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u306E\u578B\n\
    \ */\ntemplate <typename S, typename Op>\nclass SegTree : public SegTreeBase<S,\
    \ SegTree<S, Op>> {\n    using BaseType = SegTreeBase<S, SegTree<S, Op>>;\n\n\
    \    Op operator_object;\n    S identity;\n\npublic:\n    S op(const S& a, const\
    \ S& b) const { return operator_object(a, b); }\n    S e() const { return identity;\
    \ }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n    */\n    SegTree() = default;\n    /**\n     * @brief\
    \ \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param n \u8981\u7D20\
    \u6570\n     * @param op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\
    \u30C8\n     * @param identity \u5358\u4F4D\u5143\n     */\n    explicit SegTree(int\
    \ n, Op op, const S& identity) : BaseType(n), operator_object(std::move(op)),\
    \ identity(identity) {\n        this->construct_data();\n    }\n    /**\n    \
    \ * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param\
    \ v \u521D\u671F\u306E\u8981\u7D20\n     * @param op \u7A4D\u306E\u95A2\u6570\u30AA\
    \u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param identity \u5358\u4F4D\u5143\n  \
    \   */\n    explicit SegTree(const std::vector<S>& v, Op op, const S& identity)\
    \ : SegTree(v.size(), std::move(op), identity) {\n        this->initialize(v);\n\
    \    }\n};\n\nnamespace segtree {\n    template <typename S>\n    struct Max {\n\
    \        const S operator() (const S& a, const S& b) const { return std::max(a,\
    \ b); }\n    };\n    template <typename S>\n    struct Min {\n        const S\
    \ operator() (const S& a, const S& b) const { return std::min(a, b); }\n    };\n\
    \    template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\n\
    \    struct MaxLimit {\n        constexpr S operator() () const { return std::numeric_limits<S>::max();\
    \ }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MinLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::lowest(); }\n    };\n    template <typename S>\n\
    \    struct Zero {\n        S operator() () const { return S(0); }\n    };\n}\n\
    /**\n * @brief RangeMaxQuery\n * \n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RMaxQ = StaticSegTree<S, segtree::Max<S>, segtree::MinLimit<S>>;\n\
    /**\n * @brief RangeMinQuery\n * \n * @tparam S \u578B\n */\ntemplate <typename\
    \ S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>\nusing RMinQ = StaticSegTree<S,\
    \ segtree::Min<S>, segtree::MaxLimit<S>>;\n/**\n * @brief RangeSumQuery\n * \n\
    \ * @tparam S \u578B\n */\ntemplate <typename S>\nusing RSumQ = StaticSegTree<S,\
    \ std::plus<S>, segtree::Zero<S>>;\n"
  dependsOn: []
  isVerificationFile: false
  path: cpp/segtree.hpp
  requiredBy: []
  timestamp: '2023-05-24 09:10:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj-dsl-2-b.test.cpp
  - test/yosupo-lca.2.test.cpp
  - test/aoj-dsl-2-a.test.cpp
  - test/yosupo-point-set-range-composite.2.test.cpp
  - test/yosupo-point-set-range-composite.1.test.cpp
documentation_of: cpp/segtree.hpp
layout: document
redirect_from:
- /library/cpp/segtree.hpp
- /library/cpp/segtree.hpp.html
title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---