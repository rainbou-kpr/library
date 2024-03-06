---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/graph.hpp
    title: "\u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9"
  - icon: ':heavy_check_mark:'
    path: cpp/segtree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: cpp/tree.hpp
    title: "\u6728\u306E\u6C4E\u7528\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/yosupo-lca.2.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
    \n\n#include <iostream>\n\n#line 2 \"cpp/tree.hpp\"\n\n/**\n * @file tree.hpp\n\
    \ * @brief \u6728\u306E\u6C4E\u7528\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\n*/\n\n\
    #include <algorithm>\n#include <stack>\n#include <tuple>\n\n#line 2 \"cpp/graph.hpp\"\
    \n\n#line 4 \"cpp/graph.hpp\"\n#include <limits>\n#include <queue>\n#include <vector>\n\
    \n/**\n * @brief \u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9\n *\n\
    \ * @tparam Cost \u8FBA\u306E\u30B3\u30B9\u30C8\u306E\u578B\n */\ntemplate <typename\
    \ Cost=int>\nstruct Graph {\n    /**\n     * @brief \u6709\u5411\u8FBA\u306E\u69CB\
    \u9020\u4F53\n     *\n     * operator int()\u3092\u5B9A\u7FA9\u3057\u3066\u3044\
    \u308B\u306E\u3067\u3001int\u578B\u306B\u30AD\u30E3\u30B9\u30C8\u3059\u308B\u3068\
    \u52DD\u624B\u306Bdst\u306B\u306A\u308B\n     * \u4F8B\u3048\u3070\u3001\n   \
    \  * for (auto& e : g[v]) \u3092\u3059\u308B\u3068\u3001v\u304B\u3089\u51FA\u308B\
    \u8FBA\u304C\u5217\u6319\u3055\u308C\u308B\u304C\u3001\n     * for (int dst :\
    \ g[v]) \u3068\u3059\u308B\u3068\u3001v\u304B\u3089\u51FA\u308B\u8FBA\u306E\u884C\
    \u304D\u5148\u304C\u5217\u6319\u3055\u308C\u308B\n     */\n    struct Edge {\n\
    \        int src; //!< \u59CB\u70B9\n        int dst; //!< \u7D42\u70B9\n    \
    \    Cost cost; //!< \u30B3\u30B9\u30C8\n        int id; //!< \u8FBA\u306E\u756A\
    \u53F7(\u8FFD\u52A0\u3055\u308C\u305F\u9806\u3001\u7121\u5411\u8FBA\u306E\u5834\
    \u5408\u306Fid\u304C\u540C\u3058\u3067\u65B9\u5411\u304C\u9006\u306E\u3082\u306E\
    \u304C2\u3064\u5B58\u5728\u3059\u308B)\n        Edge() = default;\n        Edge(int\
    \ src, int dst, Cost cost=1, int id=-1) : src(src), dst(dst), cost(cost), id(id)\
    \ {}\n        operator int() const { return dst; }\n    };\n\n    int n; //!<\
    \ \u9802\u70B9\u6570\n    int m; //!< \u8FBA\u6570\n    std::vector<std::vector<Edge>>\
    \ g; //!< \u30B0\u30E9\u30D5\u306E\u96A3\u63A5\u30EA\u30B9\u30C8\u8868\u73FE\n\
    \n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\
    \u30E9\u30AF\u30BF\n     */\n    Graph() : n(0), m(0), g(0) {}\n    /**\n    \
    \ * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * @param n \u9802\u70B9\
    \u6570\n     */\n    explicit Graph(int n) : n(n), m(0), g(n) {}\n    /**\n  \
    \   * @brief \u7121\u5411\u8FBA\u3092\u8FFD\u52A0\u3059\u308B\n     * @param u\
    \ \u59CB\u70B9\n     * @param v \u7D42\u70B9\n     * @param w \u30B3\u30B9\u30C8\
    \ \u7701\u7565\u3057\u305F\u30891\n     */\n    void add_edge(int u, int v, Cost\
    \ w=1) {\n        g[u].push_back({u, v, w, m});\n        g[v].push_back({v, u,\
    \ w, m++});\n    }\n    /**\n     * @brief \u6709\u5411\u8FBA\u3092\u8FFD\u52A0\
    \u3059\u308B\n     * @param u \u59CB\u70B9\n     * @param v \u7D42\u70B9\n   \
    \  * @param w \u30B3\u30B9\u30C8 \u7701\u7565\u3057\u305F\u30891\n     */\n  \
    \  void add_directed_edge(int u, int v, Cost w=1) {\n        g[u].push_back({u,\
    \ v, w, m++});\n    }\n    /**\n     * @brief \u8FBA\u306E\u60C5\u5831\u3092\u6A19\
    \u6E96\u5165\u529B\u304B\u3089\u53D7\u3051\u53D6\u3063\u3066\u8FFD\u52A0\u3059\
    \u308B\n     * @param m \u8FBA\u306E\u6570\n     * @param padding \u9802\u70B9\
    \u756A\u53F7\u3092\u5165\u529B\u304B\u3089\u3044\u304F\u3064\u305A\u3089\u3059\
    \u304B \u7701\u7565\u3057\u305F\u3089-1\n     * @param weighted \u8FBA\u306E\u91CD\
    \u307F\u304C\u5165\u529B\u3055\u308C\u308B\u304B \u7701\u7565\u3057\u305F\u3089\
    false\u3068\u306A\u308A\u3001\u91CD\u307F1\u3067\u8FBA\u304C\u8FFD\u52A0\u3055\
    \u308C\u308B\n     * @param directed \u6709\u5411\u30B0\u30E9\u30D5\u304B\u3069\
    \u3046\u304B \u7701\u7565\u3057\u305F\u3089false\n     */\n    void read(int m,\
    \ int padding=-1, bool weighted=false, bool directed=false) {\n        for(int\
    \ i = 0; i < m; i++) {\n            int u, v; std::cin >> u >> v; u += padding,\
    \ v += padding;\n            Cost c(1);\n            if(weighted) std::cin >>\
    \ c;\n            if(directed) add_directed_edge(u, v, c);\n            else add_edge(u,\
    \ v, c);\n        }\n    }\n    /**\n     * @brief \u3042\u308B\u9802\u70B9\u304B\
    \u3089\u51FA\u308B\u8FBA\u3092\u5217\u6319\u3059\u308B\n     * @param v \u9802\
    \u70B9\u756A\u53F7\n     * @return std::vector<Edge>& v\u304B\u3089\u51FA\u308B\
    \u8FBA\u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<Edge>& operator[](int\
    \ v) {\n        return g[v];\n    }\n    /**\n     * @brief \u3042\u308B\u9802\
    \u70B9\u304B\u3089\u51FA\u308B\u8FBA\u3092\u5217\u6319\u3059\u308B\n     * @param\
    \ v \u9802\u70B9\u756A\u53F7\n     * @return const std::vector<Edge>& v\u304B\u3089\
    \u51FA\u308B\u8FBA\u306E\u30EA\u30B9\u30C8\n     */\n    const std::vector<Edge>&\
    \ operator[](int v) const {\n        return g[v];\n    }\n    /**\n     * @brief\
    \ \u8FBA\u306E\u30EA\u30B9\u30C8\n     * @return std::vector<Edge> \u8FBA\u306E\
    \u30EA\u30B9\u30C8(id\u306E\u6607\u9806)\n     *\n     * \u7121\u5411\u8FBA\u306F\
    \u4EE3\u8868\u3057\u30661\u3064\u3060\u3051\u683C\u7D0D\u3055\u308C\u308B\n  \
    \   */\n    std::vector<Edge> edges() const {\n        std::vector<Edge> res(m);\n\
    \        for(int i = 0; i < n; i++) {\n            for(auto& e : g[i]) {\n   \
    \             res[e.id] = e;\n            }\n        }\n        return res;\n\
    \    }\n    /**\n     * @brief \u3042\u308B\u9802\u70B9\u304B\u3089\u5404\u9802\
    \u70B9\u3078\u306E\u6700\u77ED\u8DEF\n     *\n     * @param s \u59CB\u70B9\n \
    \    * @param weighted 1\u4EE5\u5916\u306E\u30B3\u30B9\u30C8\u306E\u8FBA\u304C\
    \u5B58\u5728\u3059\u308B\u304B \u7701\u7565\u3059\u308B\u3068true\n     * @param\
    \ inf \u30B3\u30B9\u30C8\u306Emin\u306E\u5358\u4F4D\u5143 \u672A\u5230\u9054\u306E\
    \u9802\u70B9\u3078\u306E\u8DDD\u96E2\u306Finf\u306B\u306A\u308B \u7701\u7565\u3059\
    \u308B\u3068-1\n     * @return std::pair<std::vector<Cost>, std::vector<Edge>>\
    \ first:\u5404\u9802\u70B9\u3078\u306E\u6700\u77ED\u8DEF\u9577 second:\u5404\u9802\
    \u70B9\u3078\u306E\u6700\u77ED\u8DEF\u4E0A\u306E\u76F4\u524D\u306E\u8FBA\n   \
    \  */\n    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path(int s,\
    \ bool weignted = true, Cost inf = -1) const {\n        if(weignted) return shortest_path_dijkstra(s,\
    \ inf);\n        return shortest_path_bfs(s, inf);\n    }\n    \n    std::vector<int>\
    \ topological_sort() {\n        std::vector<int> indeg(n), sorted;\n        std::queue<int>\
    \ q;\n        for (int i = 0; i < n; i++) {\n            for (int dst : g[i])\
    \ indeg[dst]++;\n        }\n        for (int i = 0; i < n; i++) {\n          \
    \  if (!indeg[i]) q.push(i);\n        }\n        while (!q.empty()) {\n      \
    \      int cur = q.front(); q.pop();\n            for (int dst : g[cur]) {\n \
    \               if (!--indeg[dst]) q.push(dst);\n            }\n            sorted.push_back(cur);\n\
    \        }\n        return sorted;\n    }\n\nprivate:\n    std::pair<std::vector<Cost>,\
    \ std::vector<Edge>> shortest_path_bfs(int s, Cost inf) const {\n        std::vector<Cost>\
    \ dist(n, inf);\n        std::vector<Edge> prev(n);\n        std::queue<int> que;\n\
    \        dist[s] = 0;\n        que.push(s);\n        while(!que.empty()) {\n \
    \           int u = que.front(); que.pop();\n            for(auto& e : g[u]) {\n\
    \                if(dist[e.dst] == inf) {\n                    dist[e.dst] = dist[e.src]\
    \ + 1;\n                    prev[e.dst] = e;\n                    que.push(e.dst);\n\
    \                }\n            }\n        }\n        return {dist, prev};\n \
    \   }\n    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path_dijkstra(int\
    \ s, Cost inf) const {\n        std::vector<Cost> dist(n, inf);\n        std::vector<Edge>\
    \ prev(n);\n        using Node = std::pair<Cost, int>;\n        std::priority_queue<Node,\
    \ std::vector<Node>, std::greater<Node>> que;\n        dist[s] = 0;\n        que.push({0,\
    \ s});\n        while(!que.empty()) {\n            auto [d, u] = que.top(); que.pop();\n\
    \            if(d > dist[u]) continue;\n            for(auto& e : g[u]) {\n  \
    \              if(dist[e.dst] == inf || dist[e.dst] > dist[e.src] + e.cost) {\n\
    \                    dist[e.dst] = dist[e.src] + e.cost;\n                   \
    \ prev[e.dst] = e;\n                    que.push({dist[e.dst], e.dst});\n    \
    \            }\n            }\n        }\n        return {dist, prev};\n    }\n\
    \n\n};\n#line 13 \"cpp/tree.hpp\"\n\ntemplate <typename>\nstruct RootedTree;\n\
    template <typename>\nstruct DoublingClimbTree;\n\n/**\n * @brief \u6839\u306A\u3057\
    \u6728\n * \n * @tparam Cost = int \u8FBA\u306E\u91CD\u307F\n * \n * Graph<Cost>\u3092\
    \u7D99\u627F\u3057\u3001\u3059\u3079\u3066\u7121\u5411\u8FBA\u3067\u8868\u3059\
    \n*/\ntemplate <typename Cost = int>\nstruct Tree : private Graph<Cost> {\n  \
    \  // Graph<Cost>* g = new Tree<Cost>(); \u304C\u3067\u304D\u3066\u3057\u307E\u3046\
    \u3068\u3001delete\u6642\u306B\u30E1\u30E2\u30EA\u30EA\u30FC\u30AF\u304C\u767A\
    \u751F\n    // \u56DE\u907F\u3059\u308B\u305F\u3081private\u7D99\u627F\u306B\u3057\
    \u3066\u3001\u30E1\u30F3\u30D0\u3092\u3059\u3079\u3066using\u5BA3\u8A00\n    using\
    \ Edge = typename Graph<Cost>::Edge;\n    using Graph<Cost>::n;\n    using Graph<Cost>::m;\n\
    \    using Graph<Cost>::g;\n    using Graph<Cost>::Graph;\n    using Graph<Cost>::add_edge;\n\
    \    using Graph<Cost>::add_directed_edge;\n    using Graph<Cost>::read;\n   \
    \ using Graph<Cost>::operator[];\n    using Graph<Cost>::edges;\n    using Graph<Cost>::shortest_path;\n\
    \n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n\
    \     * @param n \u30CE\u30FC\u30C9\u6570\n     */\n    Tree(int n = 0) : Graph<Cost>(n)\
    \ {}\n\n    /**\n     * @brief \u8FBA\u306E\u60C5\u5831\u3092\u6A19\u6E96\u5165\
    \u529B\u304B\u3089\u53D7\u3051\u53D6\u3063\u3066\u8FFD\u52A0\u3059\u308B\n   \
    \  * @param padding  = -1 \u9802\u70B9\u756A\u53F7\u3092\u5165\u529B\u304B\u3089\
    \u3044\u304F\u3064\u305A\u3089\u3059\u304B\n     * @param weighted = false \u8FBA\
    \u306E\u91CD\u307F\u304C\u5165\u529B\u3055\u308C\u308B\u304B\n     */\n    void\
    \ read(int padding = -1, bool weighted = false) {\n        Graph<Cost>::read(this->n\
    \ - 1, padding, weighted, false);\n    }\n    \n    /**\n     * @brief \u6728\u306E\
    \u76F4\u5F84\n     * \n     * @param weighted = true \u91CD\u307F\u4ED8\u304D\u304B\
    \n     * @return std::vector<Edge> \u76F4\u5F84\u3092\u69CB\u6210\u3059\u308B\u8FBA\
    \u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<Edge> diameter(bool weighted\
    \ = true) const {\n        std::vector<Cost> dist = shortest_path(0, weighted).first;\n\
    \        int u = std::max_element(dist.begin(), dist.end()) - dist.begin();\n\
    \        std::vector<Edge> prev;\n        std::tie(dist, prev) = shortest_path(u,\
    \ weighted);\n        int v = std::max_element(dist.begin(), dist.end()) - dist.begin();\n\
    \        std::vector<Edge> path;\n        while(v != u) {\n            path.push_back(prev[v]);\n\
    \            v = prev[v].src;\n        }\n        reverse(path.begin(), path.end());\n\
    \        return path;\n    }\n\n    /**\n     * @brief \u6839\u4ED8\u304D\u6728\
    \u306B\u3059\u308B\n     * \n     * @param root \u6839\n     * @return RootedTree<Cost>\
    \ \u6839\u4ED8\u304D\u6728\u306E\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     */\n\
    \    [[nodiscard]]\n    RootedTree<Cost> set_root(int root) const& {\n       \
    \ return RootedTree<Cost>(*this, root);\n    }\n    /**\n     * @brief \u6839\u4ED8\
    \u304D\u6728\u306B\u3057\u3066\u8FD4\u3059\n     * \n     * @param root \u6839\
    \n     * @return RootedTree<Cost> \u6839\u4ED8\u304D\u6728\u306E\u30AA\u30D6\u30B8\
    \u30A7\u30AF\u30C8\n     */\n    [[nodiscard]]\n    RootedTree<Cost> set_root(int\
    \ root) && {\n        return RootedTree<Cost>(std::move(*this), root);\n    }\n\
    \n    /**\n     * @brief \u30C0\u30D6\u30EA\u30F3\u30B0LCA\u304C\u4F7F\u3048\u308B\
    \u6839\u4ED8\u304D\u6728\u3092\u8FD4\u3059\n     * \n     * @param root \u6839\
    \n     * @return DoublingClimbTree<Cost> \u30C0\u30D6\u30EA\u30F3\u30B0\u6E08\u307F\
    \u6839\u4ED8\u304D\u6728\u306E\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     */\n\
    \    [[nodiscard]]\n    DoublingClimbTree<Cost> build_lca(int root) const& {\n\
    \        RootedTree rooted_tree(*this, root);\n        return DoublingClimbTree<Cost>(std::move(rooted_tree));\n\
    \    }\n    /**\n     * @brief \u30C0\u30D6\u30EA\u30F3\u30B0LCA\u304C\u4F7F\u3048\
    \u308B\u6839\u4ED8\u304D\u6728\u3092\u8FD4\u3059\n     * \n     * @param root\
    \ \u6839\n     * @return DoublingClimbTree<Cost> \u30C0\u30D6\u30EA\u30F3\u30B0\
    \u6E08\u307F\u6839\u4ED8\u304D\u6728\u306E\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\
    \n     */\n    [[nodiscard]]\n    DoublingClimbTree<Cost> build_lca(int root)\
    \ && {\n        RootedTree rooted_tree(std::move(*this), root);        \n    \
    \    return DoublingClimbTree<Cost>(std::move(rooted_tree));\n    }\n};\n\n/**\n\
    \ * @brief \u6839\u4ED8\u304D\u6728\n * \n * @tparam Cost = int \u8FBA\u306E\u30B3\
    \u30B9\u30C8\n */\ntemplate <typename Cost = int>\nstruct RootedTree : private\
    \ Tree<Cost> {\n    using Edge = typename Tree<Cost>::Edge;\n    using Tree<Cost>::n;\n\
    \    using Tree<Cost>::m;\n    using Tree<Cost>::g;\n    using Tree<Cost>::operator[];\n\
    \    using Tree<Cost>::edges;\n    using Tree<Cost>::shortest_path;\n    using\
    \ Tree<Cost>::Tree;\n\n    int root; //!< \u6839\n    std::vector<Edge> par; //!<\
    \ \u89AA\u3078\u5411\u304B\u3046\u8FBA\n    std::vector<std::vector<Edge>> child;\
    \ //!< \u5B50\u3078\u5411\u304B\u3046\u8FBA\u306E\u30EA\u30B9\u30C8\n    std::vector<Cost>\
    \ depth; //!< \u6DF1\u3055\u306E\u30EA\u30B9\u30C8\n    std::vector<Cost> height;\
    \ //!< \u90E8\u5206\u6728\u306E\u9AD8\u3055\u306E\u30EA\u30B9\u30C8\n    std::vector<int>\
    \ sz; //!< \u90E8\u5206\u671F\u306E\u9802\u70B9\u6570\u306E\u30EA\u30B9\u30C8\n\
    \    std::vector<int> preorder; //!< \u5148\u884C\u9806\u5DE1\u56DE\n    std::vector<int>\
    \ postorder; //!< \u5F8C\u884C\u9806\u5DE1\u56DE\n    std::vector<std::pair<int,\
    \ int>> euler_tour; //!< \u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC DFS\u4E2D\u306B\
    \u3068\u304A\u3063\u305F\u9802\u70B9\u306E(\u9802\u70B9\u756A\u53F7,\u305D\u306E\
    \u9802\u70B9\u3092\u901A\u3063\u305F\u56DE\u6570)\u306E\u30EA\u30B9\u30C8\n\n\
    \    RootedTree() = delete;\n    \n    /**\n     * @brief \u89AA\u306E\u9802\u70B9\
    \u306E\u30EA\u30B9\u30C8\u304B\u3089\u6839\u304C0\u306E\u6839\u4ED8\u304D\u6728\
    \u3092\u69CB\u7BC9\u3059\u308B\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n   \
    \  * \n     * @param par_ \u9802\u70B90\u4EE5\u5916\u306E\u89AA\u306E\u9802\u70B9\
    \u306E\u30EA\u30B9\u30C8\n     * @param padding = -1 par\u306E\u9802\u70B9\u756A\
    \u53F7\u3092\u3044\u304F\u3064\u305A\u3089\u3059\u304B\n     */\n    RootedTree(const\
    \ std::vector<int>& par_, int padding = -1) : Tree<Cost>(par_.size() + 1), root(0)\
    \ {\n        for(int i = 0; i < (int)par_.size(); i++) {\n            this->add_edge(i\
    \ + 1, par_[i] + padding);\n        }\n        build();\n    }\n    /**\n    \
    \ * @brief Tree\u304B\u3089\u6839\u4ED8\u304D\u6728\u3092\u69CB\u7BC9\u3059\u308B\
    \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF(\u30B3\u30D4\u30FC)\n     *\n     *\
    \ @param tree Tree\n     * @param root \u6839\n     */\n    RootedTree(const Tree<Cost>&\
    \ tree, int root) : Tree<Cost>(tree), root(root) {\n        build();\n    }\n\
    \    /**\n     * @brief Tree\u304B\u3089\u6839\u4ED8\u304D\u6728\u3092\u69CB\u7BC9\
    \u3059\u308B\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF(\u30E0\u30FC\u30D6)\n \
    \    *\n     * @param tree Tree\n     * @param root \u6839\n     */\n    RootedTree(Tree<Cost>&&\
    \ tree, int root) : Tree<Cost>(std::move(tree)), root(root) {\n        build();\n\
    \    }\n    \n    /**\n     * @brief \u30C0\u30D6\u30EA\u30F3\u30B0LCA\u304C\u4F7F\
    \u3048\u308B\u6839\u4ED8\u304D\u6728\u3092\u5F97\u308B\n     * \n     * @return\
    \ DoublingClimbTree<Cost> \u30C0\u30D6\u30EA\u30F3\u30B0\u6E08\u307F\u6839\u4ED8\
    \u304D\u6728\u306E\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     */\n    [[nodiscard]]\n\
    \    DoublingClimbTree<Cost> build_lca() const& {\n        return DoublingClimbTree<Cost>(*this);\n\
    \    }\n\n    /**\n     * @brief \u30C0\u30D6\u30EA\u30F3\u30B0LCA\u304C\u4F7F\
    \u3048\u308B\u6839\u4ED8\u304D\u6728\u3092\u5F97\u308B\n     * \n     * @return\
    \ DoublingClimbTree<Cost> \u30C0\u30D6\u30EA\u30F3\u30B0\u6E08\u307F\u6839\u4ED8\
    \u304D\u6728\u306E\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n     */\n    [[nodiscard]]\n\
    \    DoublingClimbTree<Cost> build_lca() && {\n        return DoublingClimbTree<Cost>(std::move(*this));\n\
    \    }\n\nprivate:\n    void build() {\n        int n = this->n;\n        par.resize(n);\n\
    \        par[root] = {root, -1, 0, -1};\n        child.resize(n);\n        depth.resize(n);\n\
    \        height.resize(n);\n        sz.resize(n);\n        std::vector<int> iter(n);\n\
    \        std::stack<std::pair<int, int>> stk;\n        stk.emplace(root, 0);\n\
    \        while(!stk.empty()) {\n            auto [u, cnt] = stk.top(); stk.pop();\n\
    \            euler_tour.emplace_back(u, cnt);\n            if(iter[u] == 0) preorder.push_back(u);\n\
    \            while(iter[u] < (int)this->g[u].size() && this->g[u][iter[u]].dst\
    \ == par[u]) iter[u]++;\n            if(iter[u] == (int)this->g[u].size()) {\n\
    \                postorder.push_back(u);\n                sz[u] = 1;\n       \
    \         height[u] = 0;\n                for(auto& e : child[u]) {\n        \
    \            sz[u] += sz[e.dst];\n                    if(height[u] < height[e.dst]\
    \ + e.cost) {\n                        height[u] = height[e.dst] + e.cost;\n \
    \                   }\n                }\n            } else {\n             \
    \   auto& e = this->g[u][iter[u]++];\n                par[e.dst] = {e.dst, u,\
    \ e.cost, e.id};\n                child[u].push_back(e);\n                depth[e.dst]\
    \ = depth[u] + e.cost;\n                stk.emplace(u, cnt + 1);\n           \
    \     stk.emplace(e.dst, 0);\n            }\n        }\n    }\n};\n\n/**\n * @brief\
    \ \u89AA\u9802\u70B9\u30C0\u30D6\u30EA\u30F3\u30B0\u6E08\u307F\u6839\u4ED8\u304D\
    \u6728\n * \n * @tparam Cost = int \u8FBA\u306E\u91CD\u307F(\u6CE8: climb\u3067\
    \u306F\u6839\u306E\u91CD\u307F\u306F\u8003\u3048\u306A\u3044)\n */\ntemplate <typename\
    \ Cost = int>\nstruct DoublingClimbTree : private RootedTree<Cost> {\n    using\
    \ Edge = typename RootedTree<Cost>::Edge;\n    using RootedTree<Cost>::n;\n  \
    \  using RootedTree<Cost>::m;\n    using RootedTree<Cost>::g;\n    using RootedTree<Cost>::operator[];\n\
    \    using RootedTree<Cost>::edges;\n    using RootedTree<Cost>::shortest_path;\n\
    \    using RootedTree<Cost>::RootedTree;\n    using RootedTree<Cost>::root;\n\
    \    using RootedTree<Cost>::par;\n    using RootedTree<Cost>::child;\n    using\
    \ RootedTree<Cost>::depth;\n    using RootedTree<Cost>::height;\n    using RootedTree<Cost>::sz;\n\
    \    using RootedTree<Cost>::preorder;\n    using RootedTree<Cost>::postorder;\n\
    \    using RootedTree<Cost>::euler_tour;\n\n    int h; //!< \u30C0\u30D6\u30EA\
    \u30F3\u30B0\u306E\u56DE\u6570\n    std::vector<std::vector<int>> doubling_par;\
    \ //!< j\u304B\u3089(1<<i)\u9802\u70B9\u767B\u3063\u305F\u9802\u70B9(\u5B58\u5728\
    \u3057\u306A\u3044\u5834\u5408\u306F-1)\n\n    DoublingClimbTree() = delete;\n\
    \    \n    /**\n     * @brief RootedTree\u304B\u3089\u30C0\u30D6\u30EA\u30F3\u30B0\
    \u6E08\u307F\u6839\u4ED8\u304D\u6728\u3092\u69CB\u7BC9\u3059\u308B\u30B3\u30F3\
    \u30B9\u30C8\u30E9\u30AF\u30BF(\u30B3\u30D4\u30FC)\n     *\n     * @param tree\
    \ RootedTree\n     */\n    DoublingClimbTree(const RootedTree<Cost>& tree) : RootedTree<Cost>(tree)\
    \ {\n        build();\n    }\n\n    /**\n     * @brief RootedTree\u304B\u3089\u30C0\
    \u30D6\u30EA\u30F3\u30B0\u6E08\u307F\u6839\u4ED8\u304D\u6728\u3092\u69CB\u7BC9\
    \u3059\u308B\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF(\u30E0\u30FC\u30D6)\n \
    \    *\n     * @param tree RootedTree\n     */\n    DoublingClimbTree(RootedTree<Cost>&&\
    \ tree) : RootedTree<Cost>(std::move(tree)) {\n        build();\n    }\n    \n\
    \    /**\n     * @brief \u9802\u70B9u\u304B\u3089k\u56DE\u3092\u6839\u306E\u65B9\
    \u5411\u306B\u9061\u3063\u305F\u9802\u70B9\n     * \n     * @param u \u5143\u306E\
    \u9802\u70B9\n     * @param k \u767B\u308B\u6BB5\u6570\n     * @return int k\u56DE\
    \u767B\u3063\u305F\u9802\u70B9\n     */\n    int climb(int u, int k) const {\n\
    \        for(int i = 0; i < h; i++) {\n            if(k >> i & 1) u = doubling_par[i][u];\n\
    \            if(u == -1) return -1;\n        }\n        return u;\n    }\n   \
    \ \n    /**\n     * @brief \u6700\u5C0F\u5171\u901A\u7956\u5148\n     * \n   \
    \  * @param u \u9802\u70B91\n     * @param v \u9802\u70B92\n     * @return int\
    \ LCA\u306E\u9802\u70B9\u756A\u53F7\n     */\n    int lca(int u, int v) const\
    \ {\n        if(this->depth[u] > this->depth[v]) std::swap(u, v);\n        v =\
    \ climb(v, this->depth[v] - this->depth[u]);\n        if(this->depth[u] > this->depth[v])\
    \ u = climb(u, this->depth[u] - this->depth[v]);\n        if(u == v) return u;\n\
    \        for(int i = h - 1; i >= 0; i--) {\n            int nu = doubling_par[i][u];\n\
    \            int nv = doubling_par[i][v];\n            if(nu == -1) continue;\n\
    \            if(nu != nv) {\n                u = nu;\n                v = nv;\n\
    \            }\n        }\n        return this->par[u];\n    }\n    \n    /**\n\
    \     * @brief \u9802\u70B9\u9593\u8DDD\u96E2(\u91CD\u307F\u306A\u3057)\n    \
    \ * \n     * @param u \u9802\u70B91\n     * @param v \u9802\u70B92\n     * @return\
    \ int u\u3068v\u9593\u306E\u6700\u77ED\u7D4C\u8DEF\u306E\u8FBA\u306E\u672C\u6570\
    \n     */\n    int dist(int u, int v) const {\n        return this->depth[u] +\
    \ this->depth[v] - this->depth[lca(u, v)] * 2;\n    }\n    \nprivate:\n    void\
    \ build() {\n        int n = this->n;\n        h = 0;\n        while((1 << h)\
    \ < n) h++;\n        doubling_par.assign(h, std::vector<int>(n, -1));\n      \
    \  for(int i = 0; i < n; i++) doubling_par[0][i] = this->par[i];\n        for(int\
    \ i = 0; i < h - 1; i++) {\n            for(int j = 0; j < n; j++) {\n       \
    \         if(doubling_par[i][j] != -1) {\n                    doubling_par[i+1][j]\
    \ = doubling_par[i][doubling_par[i][j]];\n                }\n            }\n \
    \       }\n    }\n};\n#line 2 \"cpp/segtree.hpp\"\n\n/**\n * @file segtree.hpp\n\
    \ * @brief \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n */\n\n#include <cassert>\n#include\
    \ <functional>\n#line 11 \"cpp/segtree.hpp\"\n#include <numeric>\n#include <ostream>\n\
    #line 14 \"cpp/segtree.hpp\"\n\n/**\n * @brief \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\
    \u306ECRTP\u57FA\u5E95\u30AF\u30E9\u30B9\n * \n * @tparam S \u30E2\u30CE\u30A4\
    \u30C9\u306E\u578B\n * @tparam ActualSegTree \u6D3E\u751F\u30AF\u30E9\u30B9\n\
    \ */\ntemplate <typename S, typename ActualSegTree>\nclass SegTreeBase {\n   \
    \ S op(const S& a, const S& b) const { return static_cast<const ActualSegTree&>(*this).op(a,\
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
    \        S sum = e();\n        while(f(op(sum, data[l]))) {\n            sum =\
    \ op(sum, data[l]);\n            l++;\n            while (l % 2 == 0) l >>= 1;\n\
    \            if (l == 1) return n;\n        }\n        while (l < sz) {\n    \
    \        if (!f(op(sum, data[l * 2]))) l *= 2;\n            else {\n         \
    \       sum = op(sum, data[l * 2]);\n                l = l * 2 + 1;\n        \
    \    }\n        }\n        return l - sz;\n    }\n    /**\n     * @brief (l =\
    \ 0 or f(prod([l, r))) = true) and (l = r or f(prod([l-1, r))) = false)\u3068\u306A\
    \u308Bl\u3092\u8FD4\u3059\n     * f\u304C\u5358\u8ABF\u306A\u3089\u3001f(prod([l,\
    \ r))) = true\u3068\u306A\u308B\u6700\u5C0F\u306El\n     * \n     * @tparam F\n\
    \     * @param r \u534A\u958B\u533A\u9593\u306E\u7D42\u7AEF\n     * @param f \u5224\
    \u5B9A\u95A2\u6570 f(e) = true\n     * @return int\n     */\n    template <typename\
    \ F>\n    int min_left(int r, F f) const {\n        assert(f(e()));\n        if\
    \ (r == 0) return 0;\n        r += sz;\n        while (r % 2 == 0) r >>= 1;\n\
    \        S sum = e();\n        while(f(op(data[r-1], sum))) {\n            sum\
    \ = op(data[r-1], sum);\n            r--;\n            while (r % 2 == 0) r >>=\
    \ 1;\n            if (r == 1) return 0;\n        }\n        while (r < sz) {\n\
    \            if (!f(op(data[r * 2 - 1], sum))) r *= 2;\n            else {\n \
    \               sum = op(data[r * 2 - 1], sum);\n                r = r * 2 - 1;\n\
    \            }\n        }\n        return r - sz;\n    }\n};\n\n/**\n * @brief\
    \ \u7A4D\u306E\u30D5\u30A1\u30F3\u30AF\u30BF\u304C\u9759\u7684\u306A\u5834\u5408\
    \u306E\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u306E\u5B9F\u88C5\n * \n * @tparam\
    \ S \u30E2\u30CE\u30A4\u30C9\u306E\u578B\n * @tparam Op \u7A4D\u306E\u30D5\u30A1\
    \u30F3\u30AF\u30BF\n * @tparam E \u7A4D\u306E\u5358\u4F4D\u5143\u3092\u8FD4\u3059\
    \u30D5\u30A1\u30F3\u30AF\u30BF\n */\ntemplate <typename S, typename Op, typename\
    \ E>\nclass StaticSegTree : public SegTreeBase<S, StaticSegTree<S, Op, E>> {\n\
    \    using BaseType = SegTreeBase<S, StaticSegTree<S, Op, E>>;\n\n    inline static\
    \ Op operator_object;\n    inline static E identity_object;\npublic:\n    S op(const\
    \ S& a, const S& b) const { return operator_object(a, b); }\n    S e() const {\
    \ return identity_object(); }\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\
    \u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n    */\n    StaticSegTree()\
    \ = default;\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\
    \n     * \n     * @param n \u8981\u7D20\u6570\n     */\n    explicit StaticSegTree(int\
    \ n) : BaseType(n) {\n        this->construct_data();\n    }\n    /**\n     *\
    \ @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     * \n     * @param v\
    \ \u521D\u671F\u306E\u8981\u7D20\n     */\n    explicit StaticSegTree(const std::vector<S>&\
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
    \    template <typename S, std::enable_if_t<std::is_integral_v<S>>* = nullptr>\n\
    \    struct Gcd {\n        constexpr S operator()(const S& a, const S& b) const\
    \ { return std::gcd(a, b); }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MaxLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::max(); }\n    };\n    template <typename S, std::enable_if_t<std::is_scalar_v<S>>*\
    \ = nullptr>\n    struct MinLimit {\n        constexpr S operator() () const {\
    \ return std::numeric_limits<S>::lowest(); }\n    };\n    template <typename S>\n\
    \    struct Zero {\n        S operator() () const { return S(0); }\n    };\n \
    \   template <typename S>\n    struct One {\n        S operator()() const { return\
    \ S(1); }\n    };\n    template <typename S>\n    struct None {\n        S operator()()\
    \ const { return S{}; }\n    };\n}\n/**\n * @brief RangeMaxQuery\n * \n * @tparam\
    \ S \u578B\n */\ntemplate <typename S>\nusing RMaxQ = StaticSegTree<S, segtree::Max<S>,\
    \ segtree::MinLimit<S>>;\n/**\n * @brief RangeMinQuery\n * \n * @tparam S \u578B\
    \n */\ntemplate <typename S>\nusing RMinQ = StaticSegTree<S, segtree::Min<S>,\
    \ segtree::MaxLimit<S>>;\n/**\n * @brief RangeSumQuery\n * \n * @tparam S \u578B\
    \n */\ntemplate <typename S>\nusing RSumQ = StaticSegTree<S, std::plus<S>, segtree::None<S>>;\n\
    /**\n * @brief RangeProdQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RProdQ = StaticSegTree<S, std::multiplies<S>, segtree::One<S>>;\n\
    /**\n * @brief RangeXorQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename\
    \ S>\nusing RXorQ = StaticSegTree<S, std::bit_xor<S>, segtree::Zero<S>>;\n/**\n\
    \ * @brief RangeGcdQuery\n *\n * @tparam S \u578B\n */\ntemplate <typename S>\n\
    using RGcdQ = StaticSegTree<S, segtree::Gcd<S>, segtree::Zero<S>>;\n#line 7 \"\
    test/yosupo-lca.2.test.cpp\"\n\nint main(void) {\n    std::cin.tie(nullptr);\n\
    \    std::ios::sync_with_stdio(0);\n    int n, q; std::cin >> n >> q;\n    std::vector<int>\
    \ par(n-1);\n    for(int i = 0; i < n-1; i++) std::cin >> par[i];\n    RootedTree\
    \ tree(par, 0);\n    RMinQ<long long> et_depth(tree.euler_tour.size());\n    std::vector<int>\
    \ pre_idx(n);\n    for(int i = 0; i < (int)tree.euler_tour.size(); i++) {\n  \
    \      auto [u, cnt] = tree.euler_tour[i];\n        et_depth[i] = (long long)tree.depth[u]\
    \ * n + u;\n        if(cnt == 0) pre_idx[u] = i;\n    }\n    while(q--) {\n  \
    \      int u, v; std::cin >> u >> v;\n        if(pre_idx[u] > pre_idx[v]) std::swap(u,\
    \ v);\n        std::cout << et_depth.prod(pre_idx[u], pre_idx[v]+1) % n << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#include \"../cpp/tree.hpp\"\n#include \"../cpp/segtree.hpp\"\n\nint main(void)\
    \ {\n    std::cin.tie(nullptr);\n    std::ios::sync_with_stdio(0);\n    int n,\
    \ q; std::cin >> n >> q;\n    std::vector<int> par(n-1);\n    for(int i = 0; i\
    \ < n-1; i++) std::cin >> par[i];\n    RootedTree tree(par, 0);\n    RMinQ<long\
    \ long> et_depth(tree.euler_tour.size());\n    std::vector<int> pre_idx(n);\n\
    \    for(int i = 0; i < (int)tree.euler_tour.size(); i++) {\n        auto [u,\
    \ cnt] = tree.euler_tour[i];\n        et_depth[i] = (long long)tree.depth[u] *\
    \ n + u;\n        if(cnt == 0) pre_idx[u] = i;\n    }\n    while(q--) {\n    \
    \    int u, v; std::cin >> u >> v;\n        if(pre_idx[u] > pre_idx[v]) std::swap(u,\
    \ v);\n        std::cout << et_depth.prod(pre_idx[u], pre_idx[v]+1) % n << '\\\
    n';\n    }\n}"
  dependsOn:
  - cpp/tree.hpp
  - cpp/graph.hpp
  - cpp/segtree.hpp
  isVerificationFile: true
  path: test/yosupo-lca.2.test.cpp
  requiredBy: []
  timestamp: '2024-03-06 15:05:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-lca.2.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-lca.2.test.cpp
- /verify/test/yosupo-lca.2.test.cpp.html
title: test/yosupo-lca.2.test.cpp
---
