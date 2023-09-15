---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: cpp/tree.hpp
    title: "\u6728\u306E\u6C4E\u7528\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj-grl-5-a.test.cpp
    title: test/aoj-grl-5-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj-grl-5-b.test.cpp
    title: test/aoj-grl-5-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/atcoder-edpc-g.test.cpp
    title: test/atcoder-edpc-g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-lca.1.test.cpp
    title: test/yosupo-lca.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-lca.2.test.cpp
    title: test/yosupo-lca.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-shortest-path.test.cpp
    title: test/yosupo-shortest-path.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9"
    links: []
  bundledCode: "#line 2 \"cpp/graph.hpp\"\n\n#include <iostream>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\n/**\n * @brief \u30B0\u30E9\u30D5\u306E\
    \u6C4E\u7528\u30AF\u30E9\u30B9\n *\n * @tparam Cost \u8FBA\u306E\u30B3\u30B9\u30C8\
    \u306E\u578B\n */\ntemplate <typename Cost=int>\nstruct Graph {\n    /**\n   \
    \  * @brief \u6709\u5411\u8FBA\u306E\u69CB\u9020\u4F53\n     *\n     * operator\
    \ int()\u3092\u5B9A\u7FA9\u3057\u3066\u3044\u308B\u306E\u3067\u3001int\u578B\u306B\
    \u30AD\u30E3\u30B9\u30C8\u3059\u308B\u3068\u52DD\u624B\u306Bdst\u306B\u306A\u308B\
    \n     * \u4F8B\u3048\u3070\u3001\n     * for (auto& e : g[v]) \u3092\u3059\u308B\
    \u3068\u3001v\u304B\u3089\u51FA\u308B\u8FBA\u304C\u5217\u6319\u3055\u308C\u308B\
    \u304C\u3001\n     * for (int dst : g[v]) \u3068\u3059\u308B\u3068\u3001v\u304B\
    \u3089\u51FA\u308B\u8FBA\u306E\u884C\u304D\u5148\u304C\u5217\u6319\u3055\u308C\
    \u308B\n     */\n    struct Edge {\n        int src; //!< \u59CB\u70B9\n     \
    \   int dst; //!< \u7D42\u70B9\n        Cost cost; //!< \u30B3\u30B9\u30C8\n \
    \       int id; //!< \u8FBA\u306E\u756A\u53F7(\u8FFD\u52A0\u3055\u308C\u305F\u9806\
    \u3001\u7121\u5411\u8FBA\u306E\u5834\u5408\u306Fid\u304C\u540C\u3058\u3067\u65B9\
    \u5411\u304C\u9006\u306E\u3082\u306E\u304C2\u3064\u5B58\u5728\u3059\u308B)\n \
    \       Edge() = default;\n        Edge(int src, int dst, Cost cost=1, int id=-1)\
    \ : src(src), dst(dst), cost(cost), id(id) {}\n        operator int() const {\
    \ return dst; }\n    };\n\n    int n; //!< \u9802\u70B9\u6570\n    int m; //!<\
    \ \u8FBA\u6570\n    std::vector<std::vector<Edge>> g; //!< \u30B0\u30E9\u30D5\u306E\
    \u96A3\u63A5\u30EA\u30B9\u30C8\u8868\u73FE\n\n    /**\n     * @brief \u30C7\u30D5\
    \u30A9\u30EB\u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     */\n    Graph()\
    \ : n(0), m(0), g(0) {}\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\
    \u30AF\u30BF\n     * @param n \u9802\u70B9\u6570\n     */\n    explicit Graph(int\
    \ n) : n(n), m(0), g(n) {}\n    /**\n     * @brief \u7121\u5411\u8FBA\u3092\u8FFD\
    \u52A0\u3059\u308B\n     * @param u \u59CB\u70B9\n     * @param v \u7D42\u70B9\
    \n     * @param w \u30B3\u30B9\u30C8 \u7701\u7565\u3057\u305F\u30891\n     */\n\
    \    void add_edge(int u, int v, Cost w=1) {\n        g[u].push_back({u, v, w,\
    \ m});\n        g[v].push_back({v, u, w, m++});\n    }\n    /**\n     * @brief\
    \ \u6709\u5411\u8FBA\u3092\u8FFD\u52A0\u3059\u308B\n     * @param u \u59CB\u70B9\
    \n     * @param v \u7D42\u70B9\n     * @param w \u30B3\u30B9\u30C8 \u7701\u7565\
    \u3057\u305F\u30891\n     */\n    void add_directed_edge(int u, int v, Cost w=1)\
    \ {\n        g[u].push_back({u, v, w, m++});\n    }\n    /**\n     * @brief \u8FBA\
    \u306E\u60C5\u5831\u3092\u6A19\u6E96\u5165\u529B\u304B\u3089\u53D7\u3051\u53D6\
    \u3063\u3066\u8FFD\u52A0\u3059\u308B\n     * @param m \u8FBA\u306E\u6570\n   \
    \  * @param padding \u9802\u70B9\u756A\u53F7\u3092\u5165\u529B\u304B\u3089\u3044\
    \u304F\u3064\u305A\u3089\u3059\u304B \u7701\u7565\u3057\u305F\u3089-1\n     *\
    \ @param weighted \u8FBA\u306E\u91CD\u307F\u304C\u5165\u529B\u3055\u308C\u308B\
    \u304B \u7701\u7565\u3057\u305F\u3089false\u3068\u306A\u308A\u3001\u91CD\u307F\
    1\u3067\u8FBA\u304C\u8FFD\u52A0\u3055\u308C\u308B\n     * @param directed \u6709\
    \u5411\u30B0\u30E9\u30D5\u304B\u3069\u3046\u304B \u7701\u7565\u3057\u305F\u3089\
    false\n     */\n    void read(int m, int padding=-1, bool weighted=false, bool\
    \ directed=false) {\n        for(int i = 0; i < m; i++) {\n            int u,\
    \ v; std::cin >> u >> v; u += padding, v += padding;\n            Cost c(1);\n\
    \            if(weighted) std::cin >> c;\n            if(directed) add_directed_edge(u,\
    \ v, c);\n            else add_edge(u, v, c);\n        }\n    }\n    /**\n   \
    \  * @brief \u3042\u308B\u9802\u70B9\u304B\u3089\u51FA\u308B\u8FBA\u3092\u5217\
    \u6319\u3059\u308B\n     * @param v \u9802\u70B9\u756A\u53F7\n     * @return std::vector<Edge>&\
    \ v\u304B\u3089\u51FA\u308B\u8FBA\u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<Edge>&\
    \ operator[](int v) {\n        return g[v];\n    }\n    /**\n     * @brief \u3042\
    \u308B\u9802\u70B9\u304B\u3089\u51FA\u308B\u8FBA\u3092\u5217\u6319\u3059\u308B\
    \n     * @param v \u9802\u70B9\u756A\u53F7\n     * @return const std::vector<Edge>&\
    \ v\u304B\u3089\u51FA\u308B\u8FBA\u306E\u30EA\u30B9\u30C8\n     */\n    const\
    \ std::vector<Edge>& operator[](int v) const {\n        return g[v];\n    }\n\
    \    /**\n     * @brief \u8FBA\u306E\u30EA\u30B9\u30C8\n     * @return std::vector<Edge>\
    \ \u8FBA\u306E\u30EA\u30B9\u30C8(id\u306E\u6607\u9806)\n     *\n     * \u7121\u5411\
    \u8FBA\u306F\u4EE3\u8868\u3057\u30661\u3064\u3060\u3051\u683C\u7D0D\u3055\u308C\
    \u308B\n     */\n    std::vector<Edge> edges() const {\n        std::vector<Edge>\
    \ res(m);\n        for(int i = 0; i < n; i++) {\n            for(auto& e : g[i])\
    \ {\n                res[e.id] = e;\n            }\n        }\n        return\
    \ res;\n    }\n    /**\n     * @brief \u3042\u308B\u9802\u70B9\u304B\u3089\u5404\
    \u9802\u70B9\u3078\u306E\u6700\u77ED\u8DEF\n     *\n     * @param s \u59CB\u70B9\
    \n     * @param weighted 1\u4EE5\u5916\u306E\u30B3\u30B9\u30C8\u306E\u8FBA\u304C\
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
    \n\n};\n"
  code: "#pragma once\n\n#include <iostream>\n#include <limits>\n#include <queue>\n\
    #include <vector>\n\n/**\n * @brief \u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\
    \u30E9\u30B9\n *\n * @tparam Cost \u8FBA\u306E\u30B3\u30B9\u30C8\u306E\u578B\n\
    \ */\ntemplate <typename Cost=int>\nstruct Graph {\n    /**\n     * @brief \u6709\
    \u5411\u8FBA\u306E\u69CB\u9020\u4F53\n     *\n     * operator int()\u3092\u5B9A\
    \u7FA9\u3057\u3066\u3044\u308B\u306E\u3067\u3001int\u578B\u306B\u30AD\u30E3\u30B9\
    \u30C8\u3059\u308B\u3068\u52DD\u624B\u306Bdst\u306B\u306A\u308B\n     * \u4F8B\
    \u3048\u3070\u3001\n     * for (auto& e : g[v]) \u3092\u3059\u308B\u3068\u3001\
    v\u304B\u3089\u51FA\u308B\u8FBA\u304C\u5217\u6319\u3055\u308C\u308B\u304C\u3001\
    \n     * for (int dst : g[v]) \u3068\u3059\u308B\u3068\u3001v\u304B\u3089\u51FA\
    \u308B\u8FBA\u306E\u884C\u304D\u5148\u304C\u5217\u6319\u3055\u308C\u308B\n   \
    \  */\n    struct Edge {\n        int src; //!< \u59CB\u70B9\n        int dst;\
    \ //!< \u7D42\u70B9\n        Cost cost; //!< \u30B3\u30B9\u30C8\n        int id;\
    \ //!< \u8FBA\u306E\u756A\u53F7(\u8FFD\u52A0\u3055\u308C\u305F\u9806\u3001\u7121\
    \u5411\u8FBA\u306E\u5834\u5408\u306Fid\u304C\u540C\u3058\u3067\u65B9\u5411\u304C\
    \u9006\u306E\u3082\u306E\u304C2\u3064\u5B58\u5728\u3059\u308B)\n        Edge()\
    \ = default;\n        Edge(int src, int dst, Cost cost=1, int id=-1) : src(src),\
    \ dst(dst), cost(cost), id(id) {}\n        operator int() const { return dst;\
    \ }\n    };\n\n    int n; //!< \u9802\u70B9\u6570\n    int m; //!< \u8FBA\u6570\
    \n    std::vector<std::vector<Edge>> g; //!< \u30B0\u30E9\u30D5\u306E\u96A3\u63A5\
    \u30EA\u30B9\u30C8\u8868\u73FE\n\n    /**\n     * @brief \u30C7\u30D5\u30A9\u30EB\
    \u30C8\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     */\n    Graph() : n(0),\
    \ m(0), g(0) {}\n    /**\n     * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\
    \n     * @param n \u9802\u70B9\u6570\n     */\n    explicit Graph(int n) : n(n),\
    \ m(0), g(n) {}\n    /**\n     * @brief \u7121\u5411\u8FBA\u3092\u8FFD\u52A0\u3059\
    \u308B\n     * @param u \u59CB\u70B9\n     * @param v \u7D42\u70B9\n     * @param\
    \ w \u30B3\u30B9\u30C8 \u7701\u7565\u3057\u305F\u30891\n     */\n    void add_edge(int\
    \ u, int v, Cost w=1) {\n        g[u].push_back({u, v, w, m});\n        g[v].push_back({v,\
    \ u, w, m++});\n    }\n    /**\n     * @brief \u6709\u5411\u8FBA\u3092\u8FFD\u52A0\
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
    \n\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: cpp/graph.hpp
  requiredBy:
  - cpp/tree.hpp
  timestamp: '2023-06-06 14:52:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj-grl-5-a.test.cpp
  - test/aoj-grl-5-b.test.cpp
  - test/yosupo-lca.2.test.cpp
  - test/yosupo-shortest-path.test.cpp
  - test/yosupo-lca.1.test.cpp
  - test/atcoder-edpc-g.test.cpp
documentation_of: cpp/graph.hpp
layout: document
redirect_from:
- /library/cpp/graph.hpp
- /library/cpp/graph.hpp.html
title: "\u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9"
---
