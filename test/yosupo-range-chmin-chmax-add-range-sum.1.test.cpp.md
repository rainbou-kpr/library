---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/segtree-beats.hpp
    title: Segment Tree Beats
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
  bundledCode: "#line 1 \"test/yosupo-range-chmin-chmax-add-range-sum.1.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include <iostream>\n#include <ostream>\n\n#line 2 \"cpp/segtree-beats.hpp\"\
    \n\n/**\n * @file segtree-beats.hpp\n * @brief Segment Tree Beats\n */\n\n#include\
    \ <cassert>\n#include <functional>\n#include <limits>\n#line 12 \"cpp/segtree-beats.hpp\"\
    \n#include <tuple>\n#include <vector>\n\n/**\n * @brief Segment Tree Beats\u306E\
    CRTP\u57FA\u5E95\u30AF\u30E9\u30B9\n * \n * @tparam S \u5024\u30E2\u30CE\u30A4\
    \u30C9\u306E\u578B\n * @tparam F \u4F5C\u7528\u7D20\u30E2\u30CE\u30A4\u30C9\u306E\
    \u578B\n * @tparam ActualSegTree \u6D3E\u751F\u30AF\u30E9\u30B9\n */\ntemplate\
    \ <typename S, typename F, typename ActualSegTreeBeats>\nclass SegTreeBeatsBase\
    \ {\n    S op(const S& a, const S& b) const { return static_cast<const ActualSegTreeBeats&>(*this).op(a,\
    \ b); }\n    S e() const { return static_cast<const ActualSegTreeBeats&>(*this).e();\
    \ }\n    std::pair<bool, S> mapping(const F& f, const S& x, int l, int r) const\
    \ { return static_cast<const ActualSegTreeBeats&>(*this).mapping(f, x, l, r);\
    \ }\n    F composition(const F& f, const F& g) const { return static_cast<const\
    \ ActualSegTreeBeats&>(*this).composition(f, g); }\n    F id() const { return\
    \ static_cast<const ActualSegTreeBeats&>(*this).id(); }\n\n    int n, sz, height;\n\
    \    std::vector<S> data;\n    std::vector<int> fail;\n    std::vector<F> lazy;\n\
    \n    void update(int k) {\n        data[k] = op(data[2 * k], data[2 * k + 1]);\n\
    \        fail[k] = false;\n    }\n    void apply_node(int k, int h, const F& f)\
    \ {\n        int l = (k << h) & (sz - 1);\n        int r = l + (1 << h);\n   \
    \     std::tie(fail[k], data[k]) = mapping(f, data[k], l, r);\n        if(k <\
    \ sz) {\n            lazy[k] = composition(f, lazy[k]);\n            if(fail[k])\
    \ {\n                push(k, h);\n                update(k);\n            }\n\
    \        }\n    }\n    void push(int k, int h) {\n        apply_node(2 * k, h-1,\
    \ lazy[k]);\n        apply_node(2 * k + 1, h-1, lazy[k]);\n        lazy[k] = id();\n\
    \    }\n\n    class SegTreeBeatsReference {\n        SegTreeBeatsBase& segtree;\n\
    \        int k;\n    public:\n        SegTreeBeatsReference(SegTreeBeatsBase&\
    \ segtree, int k) : segtree(segtree), k(k) {}\n        SegTreeBeatsReference&\
    \ operator=(const S& x) {\n            segtree.set(k, x);\n            return\
    \ *this;\n        }\n        operator S() { return segtree.get(k); }\n    };\n\
    \nprotected:\n    void construct_data() {\n        sz = 1;\n        height = 0;\n\
    \        while (sz < n) {\n            sz <<= 1;\n            height++;\n    \
    \    }\n        data.assign(sz * 2, e());\n        fail.assign(sz * 2, false);\n\
    \        lazy.assign(sz * 2, id());\n    }\n    void initialize(const std::vector<S>&\
    \ v) {\n        for (int i = 0; i < n; i++) data[sz + i] = v[i];\n        for\
    \ (int i = sz - 1; i > 0; i--) update(i);\n    }\n\npublic:\n    // Warning: \u7D99\
    \u627F\u5148\u306E\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067construct_data()\u3092\
    \u5FC5\u305A\u547C\u3073\u51FA\u3059\uFF01\n    SegTreeBeatsBase(int n = 0) :\
    \ n(n) {}\n\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\
    \u306E\u5024\u3092\u8FD4\u3059\n     * \n     * @param k \u30A4\u30F3\u30C7\u30C3\
    \u30AF\u30B9\n     * @return S \u5024\n     */\n    S get(int k) {\n        k\
    \ += sz;\n        for(int h = height; h > 0; h--) {\n            push(k >> h,\
    \ h);\n        }\n        return data[k];\n    }\n    /**\n     * @brief \u6307\
    \u5B9A\u3055\u308C\u305F\u8981\u7D20\u3078\u306E\u53C2\u7167\u3092\u8FD4\u3059\
    \n     * \n     * @param k \n     * @return SegTreeReference \u8981\u7D20\u3078\
    \u306E\u53C2\u7167 \u4EE3\u5165\u3055\u308C\u308B\u3068set()\u304C\u547C\u3070\
    \u308C\u308B\n     */\n    SegTreeBeatsReference operator[] (int k) { return SegTreeBeatsReference(*this,\
    \ k); }\n\n    /**\n     * @brief \u5185\u5BB9\u3092\u51FA\u529B\u3059\u308B\n\
    \     * \n     * @tparam CharT \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\u30E0\u306E\
    \u6587\u5B57\u578B\n     * @tparam Traits \u51FA\u529B\u30B9\u30C8\u30EA\u30FC\
    \u30E0\u306E\u6587\u5B57\u578B\u7279\u6027\n     * @param os \u51FA\u529B\u30B9\
    \u30C8\u30EA\u30FC\u30E0\n     * @param rhs \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\
    \n     * @return std::basic_ostream<CharT, Traits>& \u51FA\u529B\u30B9\u30C8\u30EA\
    \u30FC\u30E0 \n     */\n    template <class CharT, class Traits>\n    friend std::basic_ostream<CharT,\
    \ Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, SegTreeBeatsBase&\
    \ rhs) {\n        for(int i = 0; i < rhs.n; i++) {\n            if(i != 0) os\
    \ << CharT(' ');\n            os << rhs[i];\n        }\n        return os;\n \
    \   }\n\n    /**\n     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\
    \u5024\u3092x\u306B\u66F4\u65B0\u3059\u308B\n     * \n     * @param k \u30A4\u30F3\
    \u30C7\u30C3\u30AF\u30B9\n     * @param x \u65B0\u3057\u3044\u5024\n     */\n\
    \    void set(int k, const S& x) {\n        k += sz;\n        for(int h = height;\
    \ h > 0; h--) {\n            push(k >> h, h);\n        }\n        data[k] = x;\n\
    \        while(k >>= 1) update(k);\n    }\n\n    /**\n     * @brief [l, r)\u306E\
    \u533A\u9593\u306E\u7DCF\u7A4D\u3092\u8FD4\u3059\n     * \n     * @param l \u534A\
    \u958B\u533A\u9593\u306E\u958B\u59CB\n     * @param r \u534A\u958B\u533A\u9593\
    \u306E\u7D42\u7AEF\n     * @return S \u7DCF\u7A4D\n     */\n    S prod(int l,\
    \ int r) {\n        l += sz; r += sz;\n        for(int h = height; h > 0; h--)\
    \ {\n            if(((l >> h) << h) != l) push(l >> h, h);\n            if(((r\
    \ >> h) << h) != r) push(r >> h, h);\n        }\n        S left_prod = e(), right_prod\
    \ = e();\n        while(l < r) {\n            if(l & 1) left_prod = op(left_prod,\
    \ data[l++]);\n            if(r & 1) right_prod = op(data[--r], right_prod);\n\
    \            l >>= 1; r >>= 1;\n        }\n        return op(left_prod, right_prod);\n\
    \    }\n    /**\n     * @brief \u3059\u3079\u3066\u306E\u8981\u7D20\u306E\u7DCF\
    \u7A4D\u3092\u8FD4\u3059\n     * \n     * @return S \u7DCF\u7A4D\n     */\n  \
    \  S all_prod() const { return data[1]; }\n    \n    /**\n     * @brief \u6307\
    \u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u306Bx\u3092\u4F5C\u7528\u3055\
    \u305B\u308B\n     * \n     * @param k \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n\
    \     * @param x \u4F5C\u7528\u7D20\n     */\n    void apply(int k, const F& f)\
    \ {\n        k += sz;\n        for(int h = height; h > 0; h--) {\n           \
    \ push(k >> h, h);\n        }\n        data[k] = mapping(f, data[k]);\n      \
    \  while(k >>= 1) update(k);\n    }\n    /**\n     * @brief [l, r)\u306E\u533A\
    \u9593\u306E\u5024\u306Bx\u3092\u4F5C\u7528\u3055\u305B\u308B\n     * \n     *\
    \ @param l \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n     * @param r \u534A\u958B\
    \u533A\u9593\u306E\u7D42\u7AEF\n     * @param f \u4F5C\u7528\u7D20\n     */\n\
    \    void apply(int l, int r, const F& f) {\n        if(l == r) return;\n    \
    \    l += sz; r += sz;\n        for(int h = height; h > 0; h--) {\n          \
    \  if(((l >> h) << h) != l) push(l >> h, h);\n            if(((r >> h) << h) !=\
    \ r) push(r >> h, h);\n        }\n        {\n            int l2 = l, r2 = r;\n\
    \            int h = 0;\n            while(l < r) {\n                if(l & 1)\
    \ apply_node(l++, h, f);\n                if(r & 1) apply_node(--r, h, f);\n \
    \               l >>= 1; r >>= 1;\n                h++;\n            }\n     \
    \       l = l2; r = r2;\n        }\n        for(int h = 1; h <= height; h++) {\n\
    \            if(((l >> h) << h) != l) update(l >> h);\n            if(((r >> h)\
    \ << h) != r) update((r - 1) >> h);\n        }\n    }\n\n    /**\n     * @brief\
    \ g(prod([l, r))) = true\u3068\u306A\u308B\u6700\u5927\u306Er\u3092\u8FD4\u3059\
    \n     * \n     * @tparam G\n     * @param l \u534A\u958B\u533A\u9593\u306E\u958B\
    \u59CB\n     * @param g \u5224\u5B9A\u95A2\u6570\n     * @return int \u6700\u5927\
    \u306Er\n     */\n    template <typename G>\n    int max_right(int l, G g) const\
    \ {\n        assert(g(e()));\n        if(l == n) return n;\n        l += sz;\n\
    \        for(int h = height; h > 0; h--) {\n            push(l >> h, h);\n   \
    \     }\n        S sum = e();\n        int h = 0;\n        while(g(op(sum, data[l])))\
    \ {\n            if(__builtin_clz(l) != __builtin_clz(l+1)) return n;\n      \
    \      sum = op(sum, data[l]);\n            l++;\n            while(l % 2 == 0)\
    \ {\n                l >>= 1;\n                h++;\n            }\n        }\n\
    \        while(l < sz) {\n            push(l, h);\n            if(!g(op(sum, data[l*2])))\
    \ {\n                l = l*2;\n            } else {\n                sum = op(sum,\
    \ data[l*2]);\n                l = l*2+1;\n            }\n            h--;\n \
    \       }\n        return l - sz;\n    }\n    /**\n     * @brief f(prod([l, r)))\
    \ = true\u3068\u306A\u308B\u6700\u5C0F\u306El\u3092\u8FD4\u3059\n     * \n   \
    \  * @tparam G\n     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n \
    \    * @param f \u5224\u5B9A\u95A2\u6570\n     * @return int \u6700\u5C0F\u306E\
    l\n     */\n    template <typename G>\n    int min_left(int r, G g) const {\n\
    \        assert(f(e()));\n        if (r == 0) return 0;\n        r += sz - 1;\n\
    \        for(int h = height; h > 0; h--) {\n            push(r >> h, h);\n   \
    \     }\n        int h = 0;\n        while(r % 2 == 1) {\n            r >>= 1;\n\
    \            h++;\n        }\n        S sum = e();\n        while(g(op(data[r],\
    \ sum))) {\n            if(__builtin_clz(r) != __builtin_clz(r-1)) return 0;\n\
    \            sum = op(data[r], sum);\n            r--;\n            while(r %\
    \ 2 == 0) {\n                r >>= 1;\n                h++;\n            }\n \
    \       }\n        while(r < sz) {\n            push(r, h);\n            if(!g(op(data[r*2+1],\
    \ sum))) {\n                r = r*2+1;\n            } else {\n               \
    \ sum = op(data[r*2+1], sum);\n                r = r*2;\n            }\n     \
    \       h--;\n        }\n        return r - sz + 1;\n    }\n};\n\n/**\n * @brief\
    \ \u30D5\u30A1\u30F3\u30AF\u30BF\u304C\u9759\u7684\u306A\u5834\u5408\u306ESegment\
    \ Tree Beats\u306E\u5B9F\u88C5\n * \n * @tparam S \u5024\u30E2\u30CE\u30A4\u30C9\
    \u306E\u578B\n * @tparam Op \u5024\u306E\u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\
    \n * @tparam E \u7A4D\u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\
    \u30AF\u30BF\n * @tparam F \u4F5C\u7528\u7D20\u30E2\u30CE\u30A4\u30C9\u306E\u578B\
    \n * @tparam Mapping \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\u308B\u30D5\u30A1\
    \u30F3\u30AF\u30BF \u5F15\u6570\u306F(\u4F5C\u7528\u7D20, \u5024)\u307E\u305F\u306F\
    (\u4F5C\u7528\u7D20, \u5024, \u30B5\u30A4\u30BA)(\u4F5C\u7528\u7D20, \u5024, \u5DE6\
    \u306E\u5B50, \u53F3\u306E\u5B50) \u623B\u308A\u5024\u306F(\u5931\u6557\u3057\u305F\
    \u304B(bool), \u5024)\u306Estd::pair\n * @tparam Composition \u4F5C\u7528\u7D20\
    \u306E\u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam ID \u4F5C\u7528\u7D20\
    \u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n */\n\
    template <typename S, typename Op, typename E, typename F, typename Mapping, typename\
    \ Composition, typename ID>\nclass StaticSegTreeBeats : public SegTreeBeatsBase<S,\
    \ F, StaticSegTreeBeats<S, Op, E, F, Mapping, Composition, ID>> {\n    using BaseType\
    \ = SegTreeBeatsBase<S, F, StaticSegTreeBeats<S, Op, E, F, Mapping, Composition,\
    \ ID>>;\n\n    inline static Op operator_object;\n    inline static E identity_object;\n\
    \    inline static Mapping mapping_object;\n    inline static Composition lazy_operator_object;\n\
    \    inline static ID lazy_identity_object;\npublic:\n    S op(const S& a, const\
    \ S& b) const { return operator_object(a, b); }\n    S e() const { return identity_object();\
    \ }\n    std::pair<bool, S> mapping(const F& f, const S& x, int l, int r) const\
    \ {\n        if constexpr(std::is_invocable_v<Mapping, F, S, int, int>) {\n  \
    \          return mapping_object(f, x, l, r);\n        } else if constexpr(std::is_invocable_v<Mapping,\
    \ F, S, int>) {\n            return mapping_object(f, x, r - l);\n        } else\
    \ {\n            return mapping_object(f, x);\n        }\n    }\n    F composition(const\
    \ F& f, const F& g) const {\n        return lazy_operator_object(f, g);\n    }\n\
    \    F id() const { return lazy_identity_object(); }\n\n    /**\n     * @brief\
    \ \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n \
    \    * \n    */\n    StaticSegTreeBeats() = default;\n    /**\n     * @brief \u30B3\
    \u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param n \u8981\u7D20\u6570\
    \n     */\n    explicit StaticSegTreeBeats(int n) : BaseType(n) {\n        this->construct_data();\n\
    \    }\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n  \
    \   * \n     * @param v \u521D\u671F\u306E\u8981\u7D20\n     */\n    explicit\
    \ StaticSegTreeBeats(const std::vector<S>& v) : StaticSegTreeBeats(v.size()) {\n\
    \        this->initialize(v);\n    }\n};\n\n/**\n * @brief \u30B3\u30F3\u30B9\u30C8\
    \u30E9\u30AF\u30BF\u3067\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\
    \u4E0E\u3048\u308B\u3053\u3068\u3067\u7A4D\u3092\u5B9A\u7FA9\u3059\u308BSegment\
    \ Tree Beats\u306E\u5B9F\u88C5\n * \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\u5F15\u6570\
    \u3092\u7701\u7565\u3059\u308B\u3053\u3068\u304C\u3067\u304D\u3001\u30E9\u30E0\
    \u30C0\u5F0F\u304C\u4F7F\u3048\u308B\n * \n * @tparam S \u30E2\u30CE\u30A4\u30C9\
    \u306E\u578B\n * @tparam Op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\
    \u30C8\u306E\u578B\n * @tparam F \u4F5C\u7528\u7D20\u30E2\u30CE\u30A4\u30C9\u306E\
    \u578B\n * @tparam Mapping \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\u308B\u95A2\
    \u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u306E\u578B\n * @tparam Composition\
    \ \u4F5C\u7528\u7D20\u306E\u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\
    \u30C8\u306E\u578B\n */\ntemplate <typename S, typename Op, typename F, typename\
    \ Mapping, typename Composition>\nclass SegTreeBeats : public SegTreeBeatsBase<S,\
    \ F, SegTreeBeats<S, Op, F, Mapping, Composition>> {\n    using BaseType = SegTreeBeatsBase<S,\
    \ F, SegTreeBeats<S, Op, F, Mapping, Composition>>;\n\n    Op operator_object;\n\
    \    S identity;\n    Mapping mapping_object;\n    Composition lazy_operator_object;\n\
    \    F lazy_identity;\n\npublic:\n    S op(const S& a, const S& b) const { return\
    \ operator_object(a, b); }\n    S e() const { return identity; }\n    std::pair<bool,\
    \ S> mapping(const F& f, const S& x, int l, int r) const {\n        if constexpr(std::is_invocable_v<Mapping,\
    \ F, S, int, int>) {\n            return mapping_object(f, x, l, r);\n       \
    \ } else if constexpr(std::is_invocable_v<Mapping, F, S, int>) {\n           \
    \ return mapping_object(f, x, r - l);\n        } else {\n            return mapping_object(f,\
    \ x);\n        }\n    }\n    F composition(const F& f, const F& g) const {\n \
    \       return lazy_operator_object(f, g);\n    }\n    F id() const { return lazy_identity;\
    \ }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n    */\n    SegTreeBeats() = default;\n    /**\n   \
    \  * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param\
    \ n \u8981\u7D20\u6570\n     * @param op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\n     * @param identity \u5358\u4F4D\u5143\n     * @param mapping\
    \ \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\u308B\u95A2\u6570\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\n     * @param composition \u4F5C\u7528\u7D20\u306E\u7A4D\u306E\
    \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param lazy_identity\
    \ \u4F5C\u7528\u7D20\u306E\u5358\u4F4D\u5143\n     */\n    explicit SegTreeBeats(int\
    \ n, Op op, const S& identity, Mapping mapping, Composition composition, const\
    \ F& lazy_identity)\n        : BaseType(n), operator_object(std::move(op)), identity(identity),\
    \ mapping_object(std::move(mapping)),\n        lazy_operator_object(std::move(composition)),\
    \ lazy_identity(lazy_identity) {\n        this->construct_data();\n    }\n   \
    \ /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n   \
    \  * @param v \u521D\u671F\u306E\u8981\u7D20\n     * @param op \u7A4D\u306E\u95A2\
    \u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param identity \u5358\u4F4D\
    \u5143\n     * @param mapping \u4F5C\u7528\u7D20\u3092\u9069\u7528\u3059\u308B\
    \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     * @param composition \u4F5C\
    \u7528\u7D20\u306E\u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\
    \n     * @param lazy_identity \u4F5C\u7528\u7D20\u306E\u5358\u4F4D\u5143\n   \
    \  */\n    explicit SegTreeBeats(const std::vector<S>& v, Op op, const S& identity,\
    \ Mapping mapping, Composition composition, const F& lazy_identity)\n        :\
    \ SegTreeBeats(v.size(), std::move(op), identity, std::move(mapping), std::move(composition),\
    \ lazy_identity) {\n        this->initialize(v);\n    }\n};\n#line 7 \"test/yosupo-range-chmin-chmax-add-range-sum.1.test.cpp\"\
    \n\nlong long inf = 2e18;\n\nint main(void) {\n    std::cin.tie(nullptr);\n  \
    \  std::ios_base::sync_with_stdio(false);\n    struct S {\n        // 1\u756A\u76EE\
    \u30011\u756A\u76EE\u306E\u8981\u7D20\u6570\u30012\u756A\u76EE\u3001\u5408\u8A08\
    \n        long long max1, max1_num, max2, min1, min1_num, min2, sum;\n       \
    \ S(long long x = 0) : max1(x), max1_num(1), max2(-inf), min1(x), min1_num(1),\
    \ min2(inf), sum(x) {}\n    };\n    struct Op {\n        S operator() (const S&\
    \ l, const S& r) {\n            S res;\n            res.max1 = std::max(l.max1,\
    \ r.max1);\n            if(l.max1 == r.max1) {\n                res.max1_num =\
    \ l.max1_num + r.max1_num;\n                res.max2 = std::max(l.max2, r.max2);\n\
    \            } else if(l.max1 > r.max1) {\n                res.max1_num = l.max1_num;\n\
    \                res.max2 = std::max(l.max2, r.max1);\n            } else {\n\
    \                res.max1_num = r.max1_num;\n                res.max2 = std::max(l.max1,\
    \ r.max2);\n            }\n            res.min1 = std::min(l.min1, r.min1);\n\
    \            if(l.min1 == r.min1) {\n                res.min1_num = l.min1_num\
    \ + r.min1_num;\n                res.min2 = std::min(l.min2, r.min2);\n      \
    \      } else if(l.min1 < r.min1) {\n                res.min1_num = l.min1_num;\n\
    \                res.min2 = std::min(l.min2, r.min1);\n            } else {\n\
    \                res.min1_num = r.min1_num;\n                res.min2 = std::min(l.min1,\
    \ r.min2);\n            }\n            res.sum = l.sum + r.sum;\n            return\
    \ res;\n        }\n    };\n    struct E {\n        S operator() () {\n       \
    \     S res;\n            res.max1 = -inf;\n            res.max1_num = 0;\n  \
    \          res.max2 = -inf;\n            res.min1 = inf;\n            res.min1_num\
    \ = 0;\n            res.min2 = inf;\n            res.sum = 0;\n            return\
    \ res;\n        }\n    };\n    struct F {\n        // clamp(x + add, lb, ub)\n\
    \        long long lb, ub, add;\n    };\n    struct Mapping {\n        std::pair<bool,\
    \ S> operator() (const F& f, const S& x, int sz) {\n            S res = x;\n \
    \           res.max1 += f.add;\n            res.max2 += f.add;\n            res.min1\
    \ += f.add;\n            res.min2 += f.add;\n            res.sum += f.add * sz;\n\
    \            if(res.max1 == res.min1) {\n                long long x = std::clamp(res.max1,\
    \ f.lb, f.ub);\n                res.max1 = x;\n                res.max2 = -inf;\n\
    \                res.min1 = x;\n                res.min2 = inf;\n            \
    \    res.sum = x * sz;\n                return {false, res};\n            }\n\
    \            if(res.max1 == res.min2) {\n                long long xr = std::clamp(res.max1,\
    \ f.lb, f.ub);\n                long long xl = std::clamp(res.min1, f.lb, f.ub);\n\
    \                if(xr == xl) {\n                    res.max1 = xr;\n        \
    \            res.max1_num = sz;\n                    res.max2 = -inf;\n      \
    \              res.min1 = xr;\n                    res.min1_num = sz;\n      \
    \              res.min2 = inf;\n                    res.sum = xr * sz;\n     \
    \               return {false, res};\n                }\n                res.max1\
    \ = xr;\n                res.max2 = xl;\n                res.min1 = xl;\n    \
    \            res.min2 = xr;\n                res.sum = xr * res.max1_num + xl\
    \ * res.min1_num;\n                return {false, res};\n            }\n     \
    \       if(f.ub <= res.max2) return {true, res};\n            if(f.lb >= res.min2)\
    \ return {true, res};\n            if(f.ub < res.max1) {\n                res.sum\
    \ -= (res.max1 - f.ub) * res.max1_num;\n                res.max1 = f.ub;\n   \
    \         }\n            if(f.lb > res.min1) {\n                res.sum += (f.lb\
    \ - res.min1) * res.min1_num;\n                res.min1 = f.lb;\n            }\n\
    \            return {false, res};\n        }\n    };\n    struct Composition {\n\
    \        F operator() (const F& f, const F& g) {\n            F res;\n       \
    \     res.lb = std::clamp(g.lb + f.add, f.lb, f.ub);\n            res.ub = std::clamp(g.ub\
    \ + f.add, f.lb, f.ub);\n            res.add = f.add + g.add;\n            return\
    \ res;\n        }\n    };\n    struct Id {\n        F operator() () {\n      \
    \      F res;\n            res.lb = -inf;\n            res.ub = inf;\n       \
    \     res.add = 0;\n            return res;\n        }\n    };\n    int n, q;\
    \ std::cin >> n >> q;\n    std::vector<S> v(n);\n    for(int i = 0; i < n; i++)\
    \ {\n        long long a; std::cin >> a;\n        v[i] = S(a);\n    }\n    StaticSegTreeBeats<S,\
    \ Op, E, F, Mapping, Composition, Id> seg(v);\n    while(q--) {\n        int op;\
    \ std::cin >> op;\n        if(op == 0) {\n            int l, r; long long b; std::cin\
    \ >> l >> r >> b;\n            seg.apply(l, r, F{-inf, b, 0});\n        } else\
    \ if(op == 1) {\n            int l, r; long long b; std::cin >> l >> r >> b;\n\
    \            seg.apply(l, r, F{b, inf, 0});\n        } else if(op == 2) {\n  \
    \          int l, r; long long b; std::cin >> l >> r >> b;\n            seg.apply(l,\
    \ r, F{-inf, inf, b});\n        } else {\n            int l, r; std::cin >> l\
    \ >> r;\n            std::cout << seg.prod(l, r).sum << std::endl;\n        }\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include <iostream>\n#include <ostream>\n\n#include \"../cpp/segtree-beats.hpp\"\
    \n\nlong long inf = 2e18;\n\nint main(void) {\n    std::cin.tie(nullptr);\n  \
    \  std::ios_base::sync_with_stdio(false);\n    struct S {\n        // 1\u756A\u76EE\
    \u30011\u756A\u76EE\u306E\u8981\u7D20\u6570\u30012\u756A\u76EE\u3001\u5408\u8A08\
    \n        long long max1, max1_num, max2, min1, min1_num, min2, sum;\n       \
    \ S(long long x = 0) : max1(x), max1_num(1), max2(-inf), min1(x), min1_num(1),\
    \ min2(inf), sum(x) {}\n    };\n    struct Op {\n        S operator() (const S&\
    \ l, const S& r) {\n            S res;\n            res.max1 = std::max(l.max1,\
    \ r.max1);\n            if(l.max1 == r.max1) {\n                res.max1_num =\
    \ l.max1_num + r.max1_num;\n                res.max2 = std::max(l.max2, r.max2);\n\
    \            } else if(l.max1 > r.max1) {\n                res.max1_num = l.max1_num;\n\
    \                res.max2 = std::max(l.max2, r.max1);\n            } else {\n\
    \                res.max1_num = r.max1_num;\n                res.max2 = std::max(l.max1,\
    \ r.max2);\n            }\n            res.min1 = std::min(l.min1, r.min1);\n\
    \            if(l.min1 == r.min1) {\n                res.min1_num = l.min1_num\
    \ + r.min1_num;\n                res.min2 = std::min(l.min2, r.min2);\n      \
    \      } else if(l.min1 < r.min1) {\n                res.min1_num = l.min1_num;\n\
    \                res.min2 = std::min(l.min2, r.min1);\n            } else {\n\
    \                res.min1_num = r.min1_num;\n                res.min2 = std::min(l.min1,\
    \ r.min2);\n            }\n            res.sum = l.sum + r.sum;\n            return\
    \ res;\n        }\n    };\n    struct E {\n        S operator() () {\n       \
    \     S res;\n            res.max1 = -inf;\n            res.max1_num = 0;\n  \
    \          res.max2 = -inf;\n            res.min1 = inf;\n            res.min1_num\
    \ = 0;\n            res.min2 = inf;\n            res.sum = 0;\n            return\
    \ res;\n        }\n    };\n    struct F {\n        // clamp(x + add, lb, ub)\n\
    \        long long lb, ub, add;\n    };\n    struct Mapping {\n        std::pair<bool,\
    \ S> operator() (const F& f, const S& x, int sz) {\n            S res = x;\n \
    \           res.max1 += f.add;\n            res.max2 += f.add;\n            res.min1\
    \ += f.add;\n            res.min2 += f.add;\n            res.sum += f.add * sz;\n\
    \            if(res.max1 == res.min1) {\n                long long x = std::clamp(res.max1,\
    \ f.lb, f.ub);\n                res.max1 = x;\n                res.max2 = -inf;\n\
    \                res.min1 = x;\n                res.min2 = inf;\n            \
    \    res.sum = x * sz;\n                return {false, res};\n            }\n\
    \            if(res.max1 == res.min2) {\n                long long xr = std::clamp(res.max1,\
    \ f.lb, f.ub);\n                long long xl = std::clamp(res.min1, f.lb, f.ub);\n\
    \                if(xr == xl) {\n                    res.max1 = xr;\n        \
    \            res.max1_num = sz;\n                    res.max2 = -inf;\n      \
    \              res.min1 = xr;\n                    res.min1_num = sz;\n      \
    \              res.min2 = inf;\n                    res.sum = xr * sz;\n     \
    \               return {false, res};\n                }\n                res.max1\
    \ = xr;\n                res.max2 = xl;\n                res.min1 = xl;\n    \
    \            res.min2 = xr;\n                res.sum = xr * res.max1_num + xl\
    \ * res.min1_num;\n                return {false, res};\n            }\n     \
    \       if(f.ub <= res.max2) return {true, res};\n            if(f.lb >= res.min2)\
    \ return {true, res};\n            if(f.ub < res.max1) {\n                res.sum\
    \ -= (res.max1 - f.ub) * res.max1_num;\n                res.max1 = f.ub;\n   \
    \         }\n            if(f.lb > res.min1) {\n                res.sum += (f.lb\
    \ - res.min1) * res.min1_num;\n                res.min1 = f.lb;\n            }\n\
    \            return {false, res};\n        }\n    };\n    struct Composition {\n\
    \        F operator() (const F& f, const F& g) {\n            F res;\n       \
    \     res.lb = std::clamp(g.lb + f.add, f.lb, f.ub);\n            res.ub = std::clamp(g.ub\
    \ + f.add, f.lb, f.ub);\n            res.add = f.add + g.add;\n            return\
    \ res;\n        }\n    };\n    struct Id {\n        F operator() () {\n      \
    \      F res;\n            res.lb = -inf;\n            res.ub = inf;\n       \
    \     res.add = 0;\n            return res;\n        }\n    };\n    int n, q;\
    \ std::cin >> n >> q;\n    std::vector<S> v(n);\n    for(int i = 0; i < n; i++)\
    \ {\n        long long a; std::cin >> a;\n        v[i] = S(a);\n    }\n    StaticSegTreeBeats<S,\
    \ Op, E, F, Mapping, Composition, Id> seg(v);\n    while(q--) {\n        int op;\
    \ std::cin >> op;\n        if(op == 0) {\n            int l, r; long long b; std::cin\
    \ >> l >> r >> b;\n            seg.apply(l, r, F{-inf, b, 0});\n        } else\
    \ if(op == 1) {\n            int l, r; long long b; std::cin >> l >> r >> b;\n\
    \            seg.apply(l, r, F{b, inf, 0});\n        } else if(op == 2) {\n  \
    \          int l, r; long long b; std::cin >> l >> r >> b;\n            seg.apply(l,\
    \ r, F{-inf, inf, b});\n        } else {\n            int l, r; std::cin >> l\
    \ >> r;\n            std::cout << seg.prod(l, r).sum << std::endl;\n        }\n\
    \    }\n}"
  dependsOn:
  - cpp/segtree-beats.hpp
  isVerificationFile: true
  path: test/yosupo-range-chmin-chmax-add-range-sum.1.test.cpp
  requiredBy: []
  timestamp: '2023-05-12 17:36:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-range-chmin-chmax-add-range-sum.1.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-range-chmin-chmax-add-range-sum.1.test.cpp
- /verify/test/yosupo-range-chmin-chmax-add-range-sum.1.test.cpp.html
title: test/yosupo-range-chmin-chmax-add-range-sum.1.test.cpp
---
