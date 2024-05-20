---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/more_functional.hpp
    title: "\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u5B9A\u7FA9\u3059\
      \u308B"
  - icon: ':heavy_check_mark:'
    path: cpp/segtree-2d.hpp
    title: "2\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"test/yosupo-point-add-rectangle-sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\n#line\
    \ 2 \"cpp/segtree-2d.hpp\"\n\n/**\n * @file segtree-2d.hpp\n * @brief 2\u6B21\u5143\
    \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n */\n\n#include <algorithm>\n#include <tuple>\n\
    #include <vector>\n#line 2 \"cpp/more_functional.hpp\"\n\n/**\n * @file more_functional.hpp\n\
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
    \ { return S(1) / a; }\n};\n}  // namespace more_functional\n#line 12 \"cpp/segtree-2d.hpp\"\
    \n\n/**\n * @brief 2\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u306ECRTP\u57FA\
    \u5E95\u30AF\u30E9\u30B9\n *\n * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\
    \n * @tparam ActualSegTree \u6D3E\u751F\u30AF\u30E9\u30B9\n */\ntemplate <typename\
    \ S, typename ActualSegTree>\nclass SegTree2DBase {\n    S op(S a, S b) const\
    \ { return static_cast<const ActualSegTree&>(*this).op(a, b); }\n    S e() const\
    \ { return static_cast<const ActualSegTree&>(*this).e(); }\n\n    int h, w, sz_x,\
    \ sz_y, height_x, height_y;\n    std::vector<std::vector<int>> y_indices;\n  \
    \  std::vector<std::vector<S>> data_compressed;\n\n    S get_y(int kx, int ky)\
    \ {\n        ky += sz_y;\n        auto it = std::lower_bound(y_indices[kx].begin(),\
    \ y_indices[kx].end(), ky);\n        if(it == y_indices[kx].end() || *it != ky)\
    \ return e();\n        return data_compressed[kx][it - y_indices[kx].begin()];\n\
    \    }\n\n    S updated_y(int kx, int ky, int child_y_idx, bool child_y_right,\
    \ const S& child_val) {\n        if(!child_y_right && child_y_idx+1 < (int)y_indices[kx].size()\
    \ && y_indices[kx][child_y_idx+1] == ky*2+1) {\n            return op(child_val,\
    \ data_compressed[kx][child_y_idx+1]);\n        }\n        if(child_y_right &&\
    \ child_y_idx-1 >= 0 && y_indices[kx][child_y_idx-1] == ky*2) {\n            return\
    \ op(data_compressed[kx][child_y_idx-1], child_val);\n        }\n        return\
    \ child_val;\n    }\n\n    void update_tree_y(int kx, int ky, const S& val) {\n\
    \        ky += sz_y;\n        int y_idx = std::lower_bound(y_indices[kx].begin(),\
    \ y_indices[kx].end(), ky) - y_indices[kx].begin();\n        S tmp_val = val;\n\
    \        data_compressed[kx][y_idx] = tmp_val;\n        for(int i = 1; i <= height_y;\
    \ i++) {\n            int child_y_idx = y_idx;\n            y_idx = std::lower_bound(y_indices[kx].begin(),\
    \ y_indices[kx].begin() + child_y_idx, ky >> i) - y_indices[kx].begin();\n   \
    \         tmp_val = data_compressed[kx][y_idx] = updated_y(kx, ky >> i, child_y_idx,\
    \ ky>>(i-1)&1, tmp_val);\n        }\n    }\n\n    S updated_x(int kx, int ky,\
    \ bool child_x_right, const S& child_val) {\n        if(!child_x_right) {\n  \
    \          return op(child_val, get_y(kx*2+1, ky));\n        } else {\n      \
    \      return op(get_y(kx*2, ky), child_val);\n        }\n    }\n\n    void update_tree_x(int\
    \ kx, int ky, const S& val) {\n        kx += sz_x;\n        S tmp_val = val;\n\
    \        update_tree_y(kx, ky, tmp_val);\n        for(int i = 1; i <= height_x;\
    \ i++) {\n            tmp_val = updated_x(kx >> i, ky, kx>>(i-1)&1, tmp_val);\n\
    \            update_tree_y(kx >> i, ky, tmp_val);\n        }\n    }\n\n    S prod_y(int\
    \ kx, int ly, int ry) {\n        S left_prod = e(), right_prod = e();\n      \
    \  ly += sz_y; ry += sz_y;\n        auto itr = y_indices[kx].end();\n        while(ly\
    \ < ry) {\n            if(ry & 1) {\n                --ry;\n                itr\
    \ = std::lower_bound(y_indices[kx].begin(), itr, ry);\n                right_prod\
    \ = op(data_compressed[kx][itr - y_indices[kx].begin()], right_prod);\n      \
    \      }\n            if(ly & 1) {\n                itr = std::lower_bound(y_indices[kx].begin(),\
    \ itr, ly);\n                left_prod = op(left_prod, data_compressed[kx][itr\
    \ - y_indices[kx].begin()]);\n                ++ly;\n            }\n         \
    \   ly >>= 1; ry >>= 1;\n        }\n        return op(left_prod, right_prod);\n\
    \    }\n\n    S prod_x(int lx, int rx, int ly, int ry) {\n        S left_prod\
    \ = e(), right_prod = e();\n        lx += sz_x; rx += sz_x;\n        while(lx\
    \ < rx) {\n            if(lx & 1) {\n                left_prod = op(left_prod,\
    \ prod_y(lx++, ly, ry));\n            }\n            if(rx & 1) {\n          \
    \      right_prod = op(prod_y(--rx, ly, ry), right_prod);\n            }\n   \
    \         lx >>= 1; rx >>= 1;\n        }\n        return op(left_prod, right_prod);\n\
    \    }\n\nprotected:\n    void construct_data(const std::vector<std::tuple<int,\
    \ int>>& set_query_indices, const std::vector<std::tuple<int, int, int, int>>&\
    \ prod_query_indices) {\n        sz_x = 1; height_x = 0;\n        while(sz_x <\
    \ h) { sz_x <<= 1; ++height_x; }\n        sz_y = 1; height_y = 0;\n        while(sz_y\
    \ < w) { sz_y <<= 1; ++height_y; }\n        data_compressed.resize(sz_x*2);\n\
    \        y_indices.resize(sz_x*2);\n\n        for(auto [x, y] : set_query_indices)\
    \ {\n            x += sz_x;\n            std::vector<int> x_indices_tmp;\n   \
    \         for(int i = 0; i <= height_x; ++i) {\n                x_indices_tmp.push_back(x);\n\
    \                x >>= 1;\n            }\n            y += sz_y;\n           \
    \ std::vector<int> y_indices_tmp;\n            for(int i = 0; i <= height_y; ++i)\
    \ {\n                y_indices_tmp.push_back(y);\n                y >>= 1;\n \
    \           }\n            for(int x : x_indices_tmp) {\n                for(int\
    \ y : y_indices_tmp) {\n                    y_indices[x].push_back(y);\n     \
    \           }\n            }\n        }\n        for(auto [lx, rx, ly, ry] : prod_query_indices)\
    \ {\n            std::vector<int> x_indices_tmp;\n            lx += sz_x; rx +=\
    \ sz_x;\n            while(lx < rx) {\n                if(lx & 1) x_indices_tmp.push_back(lx++);\n\
    \                if(rx & 1) x_indices_tmp.push_back(--rx);\n                lx\
    \ >>= 1; rx >>= 1;\n            }\n            ly += sz_y; ry += sz_y;\n     \
    \       std::vector<int> y_indices_tmp;\n            while(ly < ry) {\n      \
    \          if(ly & 1) y_indices_tmp.push_back(ly++);\n                if(ry &\
    \ 1) y_indices_tmp.push_back(--ry);\n                ly >>= 1; ry >>= 1;\n   \
    \         }\n            for(int x : x_indices_tmp) {\n                for(int\
    \ y : y_indices_tmp) {\n                    y_indices[x].push_back(y);\n     \
    \           }\n            }\n        }\n\n        for(int x = 1; x < sz_x*2;\
    \ x++) {\n            std::sort(y_indices[x].begin(), y_indices[x].end());\n \
    \           y_indices[x].erase(std::unique(y_indices[x].begin(), y_indices[x].end()),\
    \ y_indices[x].end());\n        }\n        for(int i = 1; i < sz_x*2; ++i) {\n\
    \            data_compressed[i].assign(y_indices[i].size(), e());\n        }\n\
    \    }\n\npublic:\n    // Warning: \u7D99\u627F\u5148\u306E\u30B3\u30F3\u30B9\u30C8\
    \u30E9\u30AF\u30BF\u3067construct_data()\u3092\u5FC5\u305A\u547C\u3073\u51FA\u3059\
    \uFF01\n    SegTree2DBase(int h = 0, int w = 0) : h(h), w(w) {}\n\n    /**\n \
    \    * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u3092\u8FD4\
    \u3059\n     * @param kx x\u5EA7\u6A19\n     * @param ky y\u5EA7\u6A19\n     *\
    \ @return \u8981\u7D20\u306E\u5024\n     */\n    S get(int kx, int ky) {\n   \
    \     kx += sz_x;\n        return get_y(kx, ky);\n    }\n\n    /**\n     * @brief\
    \ \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u3092x\u306B\u66F4\u65B0\
    \u3059\u308B\n     * @param kx x\u5EA7\u6A19\n     * @param ky y\u5EA7\u6A19\n\
    \     * @param x \u4EE3\u5165\u3059\u308B\u5024\n     */\n    void set(int kx,\
    \ int ky, const S& x) {\n        update_tree_x(kx, ky, x);\n    }\n\n    /**\n\
    \     * @brief \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u306Bx\u3092\
    \u4F5C\u7528\u3055\u305B\u308B\n     *\n     * @param kx x\u5EA7\u6A19\n     *\
    \ @param ky y\u5EA7\u6A19\n     * @param x \u4F5C\u7528\u7D20\n     */\n    void\
    \ apply(int kx, int ky, const S& x) {\n        set(kx, ky, op(get(kx, ky), x));\n\
    \    }\n\n    /**\n     * @brief [lx, rx)x[ly, ry)\u306E\u7BC4\u56F2\u306E\u8981\
    \u7D20\u306E\u7DCF\u7A4D\u3092\u8FD4\u3059\n     *\n     * @param lx x\u5EA7\u6A19\
    \u306E\u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n     * @param rx x\u5EA7\u6A19\
    \u306E\u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @param ly y\u5EA7\u6A19\
    \u306E\u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n     * @param ry y\u5EA7\u6A19\
    \u306E\u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     */\n    S prod(int lx,\
    \ int rx, int ly, int ry) {\n        return prod_x(lx, rx, ly, ry);\n    }\n};\n\
    \n/**\n * @brief \u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\u304C\u9759\u7684\u306A\
    \u5834\u5408\u306E2\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u306E\u5B9F\
    \u88C5\n *\n * @tparam S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\n * @tparam Op \u7A4D\
    \u306E\u30D5\u30A1\u30F3\u30AF\u30BF\n * @tparam E \u7A4D\u306E\u5358\u4F4D\u5143\
    \u3092\u8FD4\u3059\u30D5\u30A1\u30F3\u30AF\u30BF\n */\ntemplate <typename S, typename\
    \ Op, typename E>\nclass StaticSegTree2D : public SegTree2DBase<S, StaticSegTree2D<S,\
    \ Op, E>> {\n    using BaseType = SegTree2DBase<S, StaticSegTree2D<S, Op, E>>;\n\
    \n    inline static Op operator_object;\n    inline static E identity;\npublic:\n\
    \    S op(const S& a, const S& b) const { return operator_object(a, b); }\n  \
    \  S e() const { return identity(); }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\
    \u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     */\n    StaticSegTree2D()\
    \ = default;\n\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\
    \n     *\n     * @param h \u9AD8\u3055(x\u2208[0,h))\u3068\u306A\u308B\u5024\n\
    \     * @param w \u5E45(y\u2208[0,w))\u3068\u306A\u308B\u5024\n     * @param set_query_indices\
    \ \u8981\u7D20\u306E\u66F4\u65B0\u3067\u6307\u5B9A\u3059\u308Bx\u5EA7\u6A19\u3068\
    y\u5EA7\u6A19\u306E\u30DA\u30A2\u306E\u5217\n     * @param prod_query_indices\
    \ \u7DCF\u7A4D\u306E\u30AF\u30A8\u30EA\u3067\u6307\u5B9A\u3059\u308Bx\u5EA7\u6A19\
    \u3068y\u5EA7\u6A19\u306E\u30DA\u30A2\u306E\u5217\n     */\n    explicit StaticSegTree2D(int\
    \ h, int w, const std::vector<std::tuple<int, int>>& set_query_indices, const\
    \ std::vector<std::tuple<int, int, int, int>>& prod_query_indices) : BaseType(h,\
    \ w) {\n        this->construct_data(set_query_indices, prod_query_indices);\n\
    \    }\n};\n\n/**\n * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\u3067\u95A2\
    \u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\u3092\u4E0E\u3048\u308B\u3053\u3068\
    \u3067\u7A4D\u3092\u5B9A\u7FA9\u3059\u308B2\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728\u306E\u5B9F\u88C5\n * \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\u5F15\u6570\
    \u3092\u7701\u7565\u3059\u308B\u3053\u3068\u304C\u3067\u304D\u3001\u30E9\u30E0\
    \u30C0\u5F0F\u304C\u4F7F\u3048\u308B\n *\n * @tparam S \u30E2\u30CE\u30A4\u30C9\
    \u306E\u578B\n * @tparam Op \u7A4D\u306E\u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\
    \u30C8\u306E\u578B\n */\ntemplate <typename S, typename Op>\nclass SegTree2D :\
    \ public SegTree2DBase<S, SegTree2D<S, Op>> {\n    using BaseType = SegTree2DBase<S,\
    \ SegTree2D<S, Op>>;\n\n    Op operator_object;\n    S identity;\n\npublic:\n\
    \    S op(const S& a, const S& b) const { return operator_object(a, b); }\n  \
    \  S e() const { return identity; }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\
    \u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     */\n    SegTree2D()\
    \ = default;\n\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\
    \n     *\n     * @param h \u9AD8\u3055(x\u2208[0,h))\u3068\u306A\u308B\u5024\n\
    \     * @param w \u5E45(y\u2208[0,w))\u3068\u306A\u308B\u5024\n     * @param set_query_indices\
    \ \u8981\u7D20\u306E\u66F4\u65B0\u3067\u6307\u5B9A\u3059\u308Bx\u5EA7\u6A19\u3068\
    y\u5EA7\u6A19\u306E\u30DA\u30A2\u306E\u5217\n     * @param prod_query_indices\
    \ \u7DCF\u7A4D\u306E\u30AF\u30A8\u30EA\u3067\u6307\u5B9A\u3059\u308Bx\u5EA7\u6A19\
    \u3068y\u5EA7\u6A19\u306E\u30DA\u30A2\u306E\u5217\n     */\n    explicit SegTree2D(int\
    \ h, int w, const std::vector<std::tuple<int, int>>& set_query_indices, const\
    \ std::vector<std::tuple<int, int, int, int>>& prod_query_indices, Op op, const\
    \ S& identity) : BaseType(h, w), operator_object(std::move(op)), identity(identity)\
    \ {\n        this->construct_data(set_query_indices, prod_query_indices);\n  \
    \  }\n};\n\n/**\n * @brief RangeMaxQuery\n *\n * @tparam S \u578B\n */\ntemplate\
    \ <typename S>\nusing RMaxQ2D = StaticSegTree2D<S, more_functional::Max<S>, more_functional::MinLimit<S>>;\n\
    /**\n * @brief RangeMinQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RMinQ2D = StaticSegTree2D<S, more_functional::Min<S>, more_functional::MaxLimit<S>>;\n\
    /**\n * @brief RangeSumQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RSumQ2D = StaticSegTree2D<S, std::plus<S>, more_functional::None<S>>;\n\
    #line 4 \"test/yosupo-point-add-rectangle-sum.test.cpp\"\n\n#include <iostream>\n\
    \nint main(void) {\n    std::cin.tie(nullptr);\n    std::ios_base::sync_with_stdio(false);\n\
    \n    int n, q; std::cin >> n >> q;\n    std::vector<std::tuple<int, int>> set_queries;\n\
    \    std::vector<std::tuple<int, int, int, int>> prod_queries;\n    std::vector<std::tuple<int,\
    \ int, int, int, int>> queries;\n    std::vector<int> xs, ys;\n    for (int i\
    \ = 0; i < n; i++) {\n        int x, y, w; std::cin >> x >> y >> w;\n        set_queries.emplace_back(x,\
    \ y);\n        queries.emplace_back(0, x, y, w, 0);\n        xs.push_back(x);\n\
    \        ys.push_back(y);\n    }\n    for(int i = 0; i < q; i++) {\n        int\
    \ op; std::cin >> op;\n        if(op == 0) {\n            int x, y, w; std::cin\
    \ >> x >> y >> w;\n            set_queries.emplace_back(x, y);\n            queries.emplace_back(0,\
    \ x, y, w, 0);\n            xs.push_back(x);\n            ys.push_back(y);\n \
    \       } else {\n            int l, d, r, u; std::cin >> l >> d >> r >> u;\n\
    \            prod_queries.emplace_back(l, r, d, u);\n            queries.emplace_back(1,\
    \ l, d, r, u);\n            xs.push_back(l);\n            xs.push_back(r);\n \
    \           ys.push_back(d);\n            ys.push_back(u);\n        }\n    }\n\
    \    std::sort(xs.begin(), xs.end());\n    std::sort(ys.begin(), ys.end());\n\
    \    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n    ys.erase(std::unique(ys.begin(),\
    \ ys.end()), ys.end());\n    for(auto& [x, y] : set_queries) {\n        x = std::lower_bound(xs.begin(),\
    \ xs.end(), x) - xs.begin();\n        y = std::lower_bound(ys.begin(), ys.end(),\
    \ y) - ys.begin();\n    }\n    for(auto& [lx, rx, ly, ry] : prod_queries) {\n\
    \        lx = std::lower_bound(xs.begin(), xs.end(), lx) - xs.begin();\n     \
    \   rx = std::lower_bound(xs.begin(), xs.end(), rx) - xs.begin();\n        ly\
    \ = std::lower_bound(ys.begin(), ys.end(), ly) - ys.begin();\n        ry = std::lower_bound(ys.begin(),\
    \ ys.end(), ry) - ys.begin();\n    }\n    RSumQ2D<long long> seg(xs.size(), ys.size(),\
    \ set_queries, prod_queries);\n    for(auto& [op, a, b, c, d] : queries) {\n \
    \       if(op == 0) {\n            a = std::lower_bound(xs.begin(), xs.end(),\
    \ a) - xs.begin();\n            b = std::lower_bound(ys.begin(), ys.end(), b)\
    \ - ys.begin();\n            seg.apply(a, b, c);\n        } else {\n         \
    \   a = std::lower_bound(xs.begin(), xs.end(), a) - xs.begin();\n            b\
    \ = std::lower_bound(ys.begin(), ys.end(), b) - ys.begin();\n            c = std::lower_bound(xs.begin(),\
    \ xs.end(), c) - xs.begin();\n            d = std::lower_bound(ys.begin(), ys.end(),\
    \ d) - ys.begin();\n            std::cout << seg.prod(a, c, b, d) << '\\n';\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../cpp/segtree-2d.hpp\"\n\n#include <iostream>\n\nint main(void)\
    \ {\n    std::cin.tie(nullptr);\n    std::ios_base::sync_with_stdio(false);\n\n\
    \    int n, q; std::cin >> n >> q;\n    std::vector<std::tuple<int, int>> set_queries;\n\
    \    std::vector<std::tuple<int, int, int, int>> prod_queries;\n    std::vector<std::tuple<int,\
    \ int, int, int, int>> queries;\n    std::vector<int> xs, ys;\n    for (int i\
    \ = 0; i < n; i++) {\n        int x, y, w; std::cin >> x >> y >> w;\n        set_queries.emplace_back(x,\
    \ y);\n        queries.emplace_back(0, x, y, w, 0);\n        xs.push_back(x);\n\
    \        ys.push_back(y);\n    }\n    for(int i = 0; i < q; i++) {\n        int\
    \ op; std::cin >> op;\n        if(op == 0) {\n            int x, y, w; std::cin\
    \ >> x >> y >> w;\n            set_queries.emplace_back(x, y);\n            queries.emplace_back(0,\
    \ x, y, w, 0);\n            xs.push_back(x);\n            ys.push_back(y);\n \
    \       } else {\n            int l, d, r, u; std::cin >> l >> d >> r >> u;\n\
    \            prod_queries.emplace_back(l, r, d, u);\n            queries.emplace_back(1,\
    \ l, d, r, u);\n            xs.push_back(l);\n            xs.push_back(r);\n \
    \           ys.push_back(d);\n            ys.push_back(u);\n        }\n    }\n\
    \    std::sort(xs.begin(), xs.end());\n    std::sort(ys.begin(), ys.end());\n\
    \    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n    ys.erase(std::unique(ys.begin(),\
    \ ys.end()), ys.end());\n    for(auto& [x, y] : set_queries) {\n        x = std::lower_bound(xs.begin(),\
    \ xs.end(), x) - xs.begin();\n        y = std::lower_bound(ys.begin(), ys.end(),\
    \ y) - ys.begin();\n    }\n    for(auto& [lx, rx, ly, ry] : prod_queries) {\n\
    \        lx = std::lower_bound(xs.begin(), xs.end(), lx) - xs.begin();\n     \
    \   rx = std::lower_bound(xs.begin(), xs.end(), rx) - xs.begin();\n        ly\
    \ = std::lower_bound(ys.begin(), ys.end(), ly) - ys.begin();\n        ry = std::lower_bound(ys.begin(),\
    \ ys.end(), ry) - ys.begin();\n    }\n    RSumQ2D<long long> seg(xs.size(), ys.size(),\
    \ set_queries, prod_queries);\n    for(auto& [op, a, b, c, d] : queries) {\n \
    \       if(op == 0) {\n            a = std::lower_bound(xs.begin(), xs.end(),\
    \ a) - xs.begin();\n            b = std::lower_bound(ys.begin(), ys.end(), b)\
    \ - ys.begin();\n            seg.apply(a, b, c);\n        } else {\n         \
    \   a = std::lower_bound(xs.begin(), xs.end(), a) - xs.begin();\n            b\
    \ = std::lower_bound(ys.begin(), ys.end(), b) - ys.begin();\n            c = std::lower_bound(xs.begin(),\
    \ xs.end(), c) - xs.begin();\n            d = std::lower_bound(ys.begin(), ys.end(),\
    \ d) - ys.begin();\n            std::cout << seg.prod(a, c, b, d) << '\\n';\n\
    \        }\n    }\n}\n"
  dependsOn:
  - cpp/segtree-2d.hpp
  - cpp/more_functional.hpp
  isVerificationFile: true
  path: test/yosupo-point-add-rectangle-sum.test.cpp
  requiredBy: []
  timestamp: '2024-05-17 23:06:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-point-add-rectangle-sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-point-add-rectangle-sum.test.cpp
- /verify/test/yosupo-point-add-rectangle-sum.test.cpp.html
title: test/yosupo-point-add-rectangle-sum.test.cpp
---
