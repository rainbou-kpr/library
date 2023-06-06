---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/graph.hpp
    title: "\u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9"
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B
  bundledCode: "#line 1 \"test/aoj-grl-5-b.test.cpp\"\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B\"\
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
    \    using Tree<Cost>::m;\n    using Tree<Cost>::g;\n    using Tree<Cost>::add_edge;\n\
    \    using Tree<Cost>::add_directed_edge;\n    using Tree<Cost>::read;\n    using\
    \ Tree<Cost>::operator[];\n    using Tree<Cost>::edges;\n    using Tree<Cost>::shortest_path;\n\
    \    using Tree<Cost>::Tree;\n\n    int root; //!< \u6839\n    std::vector<Edge>\
    \ par; //!< \u89AA\u3078\u5411\u304B\u3046\u8FBA\n    std::vector<std::vector<Edge>>\
    \ child; //!< \u5B50\u3078\u5411\u304B\u3046\u8FBA\u306E\u30EA\u30B9\u30C8\n \
    \   std::vector<Cost> depth; //!< \u6DF1\u3055\u306E\u30EA\u30B9\u30C8\n    std::vector<Cost>\
    \ height; //!< \u90E8\u5206\u6728\u306E\u9AD8\u3055\u306E\u30EA\u30B9\u30C8\n\
    \    std::vector<int> sz; //!< \u90E8\u5206\u671F\u306E\u9802\u70B9\u6570\u306E\
    \u30EA\u30B9\u30C8\n    std::vector<int> preorder; //!< \u5148\u884C\u9806\u5DE1\
    \u56DE\n    std::vector<int> postorder; //!< \u5F8C\u884C\u9806\u5DE1\u56DE\n\
    \    std::vector<std::pair<int, int>> euler_tour; //!< \u30AA\u30A4\u30E9\u30FC\
    \u30C4\u30A2\u30FC DFS\u4E2D\u306B\u3068\u304A\u3063\u305F\u9802\u70B9\u306E(\u9802\
    \u70B9\u756A\u53F7,\u305D\u306E\u9802\u70B9\u3092\u901A\u3063\u305F\u56DE\u6570\
    )\u306E\u30EA\u30B9\u30C8\n    \n    /**\n     * @brief \u89AA\u306E\u9802\u70B9\
    \u306E\u30EA\u30B9\u30C8\u304B\u3089\u6839\u304C0\u306E\u6839\u4ED8\u304D\u6728\
    \u3092\u69CB\u7BC9\u3059\u308B\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n   \
    \  * \n     * @param par_ \u9802\u70B90\u4EE5\u5916\u306E\u89AA\u306E\u9802\u70B9\
    \u306E\u30EA\u30B9\u30C8\n     * @param padding = -1 par\u306E\u9802\u70B9\u756A\
    \u53F7\u3092\u3044\u304F\u3064\u305A\u3089\u3059\u304B\n     */\n    RootedTree(const\
    \ std::vector<int>& par_, int padding = -1) : Tree<Cost>(par_.size() + 1), root(0)\
    \ {\n        for(int i = 0; i < (int)par_.size(); i++) {\n            this->add_edge(i\
    \ + 1, par_[i] + padding);\n        }\n        build();\n    }\n    // Tree::set_root()\u304B\
    \u3089\u547C\u3070\u308C\u308B\n    // \u76F4\u63A5\u306F\u547C\u3070\u306A\u3044\
    \n    RootedTree(const Tree<Cost>& tree, int root) : Tree<Cost>(tree), root(root)\
    \ {\n        build();\n    }\n    // Tree::set_root\u304B\u3089\u547C\u3070\u308C\
    \u308B\n    // \u76F4\u63A5\u306F\u547C\u3070\u306A\u3044\n    RootedTree(Tree<Cost>&&\
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
    \  using RootedTree<Cost>::m;\n    using RootedTree<Cost>::g;\n    using RootedTree<Cost>::add_edge;\n\
    \    using RootedTree<Cost>::add_directed_edge;\n    using RootedTree<Cost>::read;\n\
    \    using RootedTree<Cost>::operator[];\n    using RootedTree<Cost>::edges;\n\
    \    using RootedTree<Cost>::shortest_path;\n    using RootedTree<Cost>::RootedTree;\n\
    \    using RootedTree<Cost>::root;\n    using RootedTree<Cost>::par;\n    using\
    \ RootedTree<Cost>::child;\n    using RootedTree<Cost>::depth;\n    using RootedTree<Cost>::height;\n\
    \    using RootedTree<Cost>::sz;\n    using RootedTree<Cost>::preorder;\n    using\
    \ RootedTree<Cost>::postorder;\n    using RootedTree<Cost>::euler_tour;\n\n  \
    \  int h; //!< \u30C0\u30D6\u30EA\u30F3\u30B0\u306E\u56DE\u6570\n    std::vector<std::vector<int>>\
    \ doubling_par; //!< j\u304B\u3089(1<<i)\u9802\u70B9\u767B\u3063\u305F\u9802\u70B9\
    (\u5B58\u5728\u3057\u306A\u3044\u5834\u5408\u306F-1)\n    \n    // Tree::build_lca()\u3084\
    RootedTree::build_lca()\u304B\u3089\u547C\u3070\u308C\u308B\n    // \u76F4\u63A5\
    \u306F\u547C\u3070\u306A\u3044\n    DoublingClimbTree(const RootedTree<Cost>&\
    \ tree) : RootedTree<Cost>(tree) {\n        build();\n    }\n    // Tree::build_lca()\u3084\
    RootedTree::build_lca()\u304B\u3089\u547C\u3070\u308C\u308B\n    // \u76F4\u63A5\
    \u306F\u547C\u3070\u306A\u3044\n    DoublingClimbTree(RootedTree<Cost>&& tree)\
    \ : RootedTree<Cost>(std::move(tree)) {\n        build();\n    }\n    \n    /**\n\
    \     * @brief \u9802\u70B9u\u304B\u3089k\u56DE\u3092\u6839\u306E\u65B9\u5411\u306B\
    \u9061\u3063\u305F\u9802\u70B9\n     * \n     * @param u \u5143\u306E\u9802\u70B9\
    \n     * @param k \u767B\u308B\u6BB5\u6570\n     * @return int k\u56DE\u767B\u3063\
    \u305F\u9802\u70B9\n     */\n    int climb(int u, int k) const {\n        for(int\
    \ i = 0; i < h; i++) {\n            if(k >> i & 1) u = doubling_par[i][u];\n \
    \           if(u == -1) return -1;\n        }\n        return u;\n    }\n    \n\
    \    /**\n     * @brief \u6700\u5C0F\u5171\u901A\u7956\u5148\n     * \n     *\
    \ @param u \u9802\u70B91\n     * @param v \u9802\u70B92\n     * @return int LCA\u306E\
    \u9802\u70B9\u756A\u53F7\n     */\n    int lca(int u, int v) const {\n       \
    \ if(this->depth[u] > this->depth[v]) std::swap(u, v);\n        v = climb(v, this->depth[v]\
    \ - this->depth[u]);\n        if(this->depth[u] > this->depth[v]) u = climb(u,\
    \ this->depth[u] - this->depth[v]);\n        if(u == v) return u;\n        for(int\
    \ i = h - 1; i >= 0; i--) {\n            int nu = doubling_par[i][u];\n      \
    \      int nv = doubling_par[i][v];\n            if(nu == -1) continue;\n    \
    \        if(nu != nv) {\n                u = nu;\n                v = nv;\n  \
    \          }\n        }\n        return this->par[u];\n    }\n    \n    /**\n\
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
    \       }\n    }\n};\n#line 6 \"test/aoj-grl-5-b.test.cpp\"\n\nint main(void)\
    \ {\n    int n; std::cin >> n;\n    Tree<int> tree(n); tree.read(0, true);\n \
    \   RootedTree<int> rooted_tree = tree.set_root(0);\n    std::vector<int> dp(n);\n\
    \    std::vector<int> ans(n);\n    for(int i = 0; i < n; i++) {\n        int u\
    \ = rooted_tree.preorder[i];\n        ans[u] = std::max(dp[u], rooted_tree.height[u]);\n\
    \        auto& child = rooted_tree.child[u];\n        int s = child.size();\n\
    \        std::vector<int> height_lmax(s+1), height_rmax(s+1);\n        for(int\
    \ j = 0; j < s; j++) {\n            auto& e = child[j];\n            height_lmax[j+1]\
    \ = std::max(height_lmax[j], rooted_tree.height[e] + e.cost);\n        }\n   \
    \     for(int j = s-1; j >= 0; j--) {\n            auto& e = child[j];\n     \
    \       height_rmax[j] = std::max(height_rmax[j+1], rooted_tree.height[e] + e.cost);\n\
    \        }\n        for(int j = 0; j < s; j++) {\n            auto& e = child[j];\n\
    \            dp[e] = std::max(dp[u], std::max(height_lmax[j], height_rmax[j+1]))\
    \ + e.cost;\n        }\n    }\n    for(int i = 0; i < n; i++) {\n        std::cout\
    \ << ans[i] << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B\"\
    \n\n#include <iostream>\n\n#include \"../cpp/tree.hpp\"\n\nint main(void) {\n\
    \    int n; std::cin >> n;\n    Tree<int> tree(n); tree.read(0, true);\n    RootedTree<int>\
    \ rooted_tree = tree.set_root(0);\n    std::vector<int> dp(n);\n    std::vector<int>\
    \ ans(n);\n    for(int i = 0; i < n; i++) {\n        int u = rooted_tree.preorder[i];\n\
    \        ans[u] = std::max(dp[u], rooted_tree.height[u]);\n        auto& child\
    \ = rooted_tree.child[u];\n        int s = child.size();\n        std::vector<int>\
    \ height_lmax(s+1), height_rmax(s+1);\n        for(int j = 0; j < s; j++) {\n\
    \            auto& e = child[j];\n            height_lmax[j+1] = std::max(height_lmax[j],\
    \ rooted_tree.height[e] + e.cost);\n        }\n        for(int j = s-1; j >= 0;\
    \ j--) {\n            auto& e = child[j];\n            height_rmax[j] = std::max(height_rmax[j+1],\
    \ rooted_tree.height[e] + e.cost);\n        }\n        for(int j = 0; j < s; j++)\
    \ {\n            auto& e = child[j];\n            dp[e] = std::max(dp[u], std::max(height_lmax[j],\
    \ height_rmax[j+1])) + e.cost;\n        }\n    }\n    for(int i = 0; i < n; i++)\
    \ {\n        std::cout << ans[i] << '\\n';\n    }\n}\n"
  dependsOn:
  - cpp/tree.hpp
  - cpp/graph.hpp
  isVerificationFile: true
  path: test/aoj-grl-5-b.test.cpp
  requiredBy: []
  timestamp: '2023-06-06 14:52:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj-grl-5-b.test.cpp
layout: document
redirect_from:
- /verify/test/aoj-grl-5-b.test.cpp
- /verify/test/aoj-grl-5-b.test.cpp.html
title: test/aoj-grl-5-b.test.cpp
---
