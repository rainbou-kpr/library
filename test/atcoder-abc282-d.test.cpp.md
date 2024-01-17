---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/graph.hpp
    title: "\u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9"
  - icon: ':heavy_check_mark:'
    path: cpp/graph_util.hpp
    title: "\u30B0\u30E9\u30D5\u306B\u95A2\u3059\u308B\u95A2\u6570"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc282/tasks/abc282_d
    links:
    - https://atcoder.jp/contests/abc282/tasks/abc282_d
  bundledCode: "#line 1 \"test/atcoder-abc282-d.test.cpp\"\n#define PROBLEM \"https://atcoder.jp/contests/abc282/tasks/abc282_d\"\
    \n\n#include <algorithm>\n#include <array>\n\n#line 2 \"cpp/graph_util.hpp\"\n\
    \n/**\n * @file graph_util.hpp\n * @brief \u30B0\u30E9\u30D5\u306B\u95A2\u3059\
    \u308B\u95A2\u6570\n */\n\n#include <stack>\n\n#line 2 \"cpp/graph.hpp\"\n\n#include\
    \ <iostream>\n#include <limits>\n#include <queue>\n#include <vector>\n\n/**\n\
    \ * @brief \u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9\n *\n * @tparam\
    \ Cost \u8FBA\u306E\u30B3\u30B9\u30C8\u306E\u578B\n */\ntemplate <typename Cost=int>\n\
    struct Graph {\n    /**\n     * @brief \u6709\u5411\u8FBA\u306E\u69CB\u9020\u4F53\
    \n     *\n     * operator int()\u3092\u5B9A\u7FA9\u3057\u3066\u3044\u308B\u306E\
    \u3067\u3001int\u578B\u306B\u30AD\u30E3\u30B9\u30C8\u3059\u308B\u3068\u52DD\u624B\
    \u306Bdst\u306B\u306A\u308B\n     * \u4F8B\u3048\u3070\u3001\n     * for (auto&\
    \ e : g[v]) \u3092\u3059\u308B\u3068\u3001v\u304B\u3089\u51FA\u308B\u8FBA\u304C\
    \u5217\u6319\u3055\u308C\u308B\u304C\u3001\n     * for (int dst : g[v]) \u3068\
    \u3059\u308B\u3068\u3001v\u304B\u3089\u51FA\u308B\u8FBA\u306E\u884C\u304D\u5148\
    \u304C\u5217\u6319\u3055\u308C\u308B\n     */\n    struct Edge {\n        int\
    \ src; //!< \u59CB\u70B9\n        int dst; //!< \u7D42\u70B9\n        Cost cost;\
    \ //!< \u30B3\u30B9\u30C8\n        int id; //!< \u8FBA\u306E\u756A\u53F7(\u8FFD\
    \u52A0\u3055\u308C\u305F\u9806\u3001\u7121\u5411\u8FBA\u306E\u5834\u5408\u306F\
    id\u304C\u540C\u3058\u3067\u65B9\u5411\u304C\u9006\u306E\u3082\u306E\u304C2\u3064\
    \u5B58\u5728\u3059\u308B)\n        Edge() = default;\n        Edge(int src, int\
    \ dst, Cost cost=1, int id=-1) : src(src), dst(dst), cost(cost), id(id) {}\n \
    \       operator int() const { return dst; }\n    };\n\n    int n; //!< \u9802\
    \u70B9\u6570\n    int m; //!< \u8FBA\u6570\n    std::vector<std::vector<Edge>>\
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
    \n\n};\n#line 11 \"cpp/graph_util.hpp\"\n\n/**\n * @brief \u7121\u5411\u30B0\u30E9\
    \u30D5\u306B\u3064\u3044\u3066\u3001\u4E8C\u90E8\u30B0\u30E9\u30D5\u306A\u3089\
    0\u30681\u306B\u5F69\u8272\u3057\u305F\u7D50\u679C\u3092\u3072\u3068\u3064\u8FD4\
    \u3057\u3001\u4E8C\u90E8\u30B0\u30E9\u30D5\u3067\u306A\u3044\u306A\u3089\u7A7A\
    \u306Evector\u3092\u8FD4\u3059\u3002\n * \u9023\u7D50\u6210\u5206\u306E\u3046\u3061\
    \u3001\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u306E\u6700\u3082\u5C0F\u3055\u3044\
    \u3082\u306E\u30920\u306B\u3059\u308B\u3002\n * @return std::vector<int> \u5404\
    \u9802\u70B9\u306E\u5F69\u8272\u7D50\u679C\n */\ntemplate <typename Cost = int>\n\
    std::vector<int> bipartite_coloring(const Graph<Cost>& graph) {\n    std::vector<int>\
    \ color(graph.n, -1);\n    for (int i = 0; i < graph.n; i++) {\n        if (color[i]\
    \ != -1) continue;\n        std::stack<int> stk;\n        stk.push(i);\n     \
    \   color[i] = 0;\n        while (!stk.empty()) {\n            int u = stk.top();\n\
    \            stk.pop();\n            for (int v : graph[u]) {\n              \
    \  if (color[v] == -1) {\n                    color[v] = color[u] ^ 1;\n     \
    \               stk.push(v);\n                } else {\n                    if\
    \ (color[u] == color[v]) return {};\n                }\n            }\n      \
    \  }\n    }\n    return color;\n}\n\n/**\n * @brief \u7121\u5411\u30B0\u30E9\u30D5\
    \u306B\u3064\u3044\u3066\u3001\u4E8C\u90E8\u30B0\u30E9\u30D5\u304B\u3069\u3046\
    \u304B\u3092\u5224\u5B9A\u3059\u308B\u3002\n * @return bool \u4E8C\u90E8\u30B0\
    \u30E9\u30D5\u306A\u3089true\u3001\u4E8C\u90E8\u30B0\u30E9\u30D5\u3067\u306A\u3044\
    \u306A\u3089false\u3092\u8FD4\u3059\u3002\n */\ntemplate <typename Cost = int>\n\
    bool is_bipartite(const Graph<Cost>& graph) {\n    return !bipartite_coloring(graph).empty();\n\
    }\n\n/**\n * @brief \u7121\u5411\u30B0\u30E9\u30D5\u306B\u3064\u3044\u3066\u3001\
    \u9023\u7D50\u6210\u5206\u5206\u89E3\u3059\u308B\u3002\n * @return std::vector<std::vector<int>>\
    \ \u300C\u540C\u3058\u9023\u7D50\u6210\u5206\u3068\u306A\u308B\u9802\u70B9\u306E\
    \u30EA\u30B9\u30C8\u300D\u306E\u30EA\u30B9\u30C8\n */\ntemplate <typename Cost\
    \ = int>\nstd::vector<std::vector<int>> connected_components(const Graph<Cost>&\
    \ graph) {\n    std::vector<std::vector<int>> groups;\n    std::vector<bool> visited(graph.n);\n\
    \    for (int i = 0; i < graph.n; i++) {\n        if (visited[i]) continue;\n\
    \        std::stack<int> stk;\n        stk.push(i);\n        visited[i] = true;\n\
    \        groups.push_back({i});\n        while (!stk.empty()) {\n            int\
    \ u = stk.top();\n            stk.pop();\n            for (int v : graph[u]) {\n\
    \                if (visited[v]) continue;\n                visited[v] = true;\n\
    \                stk.push(v);\n                groups.back().push_back(v);\n \
    \           }\n        }\n    }\n    return groups;\n}\n\n/**\n * @brief \u7121\
    \u5411\u30B0\u30E9\u30D5\u306B\u3064\u3044\u3066\u3001\u9023\u7D50\u30B0\u30E9\
    \u30D5\u304B\u3069\u3046\u304B\u3092\u5224\u5B9A\u3059\u308B\u3002\n * @return\
    \ bool \u9023\u7D50\u30B0\u30E9\u30D5\u306A\u3089true\u3001\u9023\u7D50\u30B0\u30E9\
    \u30D5\u3067\u306A\u3044\u306A\u3089false\u3092\u8FD4\u3059\u3002\n */\ntemplate\
    \ <typename Cost = int>\nbool is_connected(const Graph<Cost>& graph) {\n    return\
    \ connected_components(graph).size() == 1;\n}\n\n/**\n * @brief \u7121\u5411\u30B0\
    \u30E9\u30D5\u306B\u3064\u3044\u3066\u3001\u6728\u304B\u3069\u3046\u304B\u3092\
    \u5224\u5B9A\u3059\u308B\u3002\n * @return bool \u6728\u306A\u3089true\u3001\u6728\
    \u3067\u306A\u3044\u306A\u3089false\u3092\u8FD4\u3059\u3002\n */\ntemplate <typename\
    \ Cost = int>\nbool is_tree(const Graph<Cost>& graph) {\n    return graph.m ==\
    \ graph.n - 1 && is_connected(graph);\n}\n\n/**\n * @brief \u6709\u5411\u30B0\u30E9\
    \u30D5\u3092\u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\u30FC\u30C8\u3059\u308B\
    \n * @param G \u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\u30FC\u30C8\u3059\u308B\
    \u30B0\u30E9\u30D5\n * @return \u30BD\u30FC\u30C8\u3055\u308C\u305F\u30CE\u30FC\
    \u30C9\u756A\u53F7\u306Evector DAG\u3067\u306A\u3051\u308C\u3070\u9577\u3055\u304C\
    G.n\u672A\u6E80\u306B\u306A\u308B\n */\ntemplate<typename Cost>\nstd::vector<int>\
    \ topological_sort(const Graph<Cost> &G) {\n    std::vector<int> indeg(G.n), sorted;\n\
    \    std::queue<int> q;\n    for (int i = 0; i < G.n; i++) {\n        for (int\
    \ dst : G[i]) indeg[dst]++;\n    }\n    for (int i = 0; i < G.n; i++) {\n    \
    \    if (!indeg[i]) q.push(i);\n    }\n    while (!q.empty()) {\n        int cur\
    \ = q.front(); q.pop();\n        for (int dst : G[cur]) {\n            if (!--indeg[dst])\
    \ q.push(dst);\n        }\n        sorted.push_back(cur);\n    }\n    return sorted;\n\
    }\n#line 7 \"test/atcoder-abc282-d.test.cpp\"\n\nint main(void) {\n    int N,\
    \ M;\n    std::cin >> N >> M;\n    Graph<int> graph(N);\n    graph.read(M);\n\
    \    std::vector<int> c = bipartite_coloring(graph);\n    if (c.empty()) {\n \
    \       std::cout << 0 << std::endl;\n        return 0;\n    }\n    std::vector<std::vector<int>>\
    \ groups = connected_components(graph);\n    long long ans = (long long)N * (N\
    \ - 1) / 2 - M;\n    for (const std::vector<int>& group : groups) {\n        std::array<long\
    \ long, 2> wb = {};\n        std::for_each(group.begin(), group.end(), [&](int\
    \ x) { wb[c[x]]++; });\n        auto [w, b] = wb;\n        ans -= w * (w - 1)\
    \ / 2 + b * (b - 1) / 2;\n    }\n    std::cout << ans << std::endl;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc282/tasks/abc282_d\"\n\n\
    #include <algorithm>\n#include <array>\n\n#include \"../cpp/graph_util.hpp\"\n\
    \nint main(void) {\n    int N, M;\n    std::cin >> N >> M;\n    Graph<int> graph(N);\n\
    \    graph.read(M);\n    std::vector<int> c = bipartite_coloring(graph);\n   \
    \ if (c.empty()) {\n        std::cout << 0 << std::endl;\n        return 0;\n\
    \    }\n    std::vector<std::vector<int>> groups = connected_components(graph);\n\
    \    long long ans = (long long)N * (N - 1) / 2 - M;\n    for (const std::vector<int>&\
    \ group : groups) {\n        std::array<long long, 2> wb = {};\n        std::for_each(group.begin(),\
    \ group.end(), [&](int x) { wb[c[x]]++; });\n        auto [w, b] = wb;\n     \
    \   ans -= w * (w - 1) / 2 + b * (b - 1) / 2;\n    }\n    std::cout << ans <<\
    \ std::endl;\n}"
  dependsOn:
  - cpp/graph_util.hpp
  - cpp/graph.hpp
  isVerificationFile: true
  path: test/atcoder-abc282-d.test.cpp
  requiredBy: []
  timestamp: '2023-11-30 23:29:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/atcoder-abc282-d.test.cpp
layout: document
redirect_from:
- /verify/test/atcoder-abc282-d.test.cpp
- /verify/test/atcoder-abc282-d.test.cpp.html
title: test/atcoder-abc282-d.test.cpp
---
