#pragma once

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

/**
 * @brief グラフの汎用クラス
 *
 * @tparam Cost 辺のコストの型
 */
template <typename Cost=int>
struct Graph {
    /**
     * @brief 有向辺の構造体
     *
     * operator int()を定義しているので、int型にキャストすると勝手にdstになる
     * 例えば、
     * for (auto& e : g[v]) をすると、vから出る辺が列挙されるが、
     * for (int dst : g[v]) とすると、vから出る辺の行き先が列挙される
     */
    struct Edge {
        int src; //!< 始点
        int dst; //!< 終点
        Cost cost; //!< コスト
        int id; //!< 辺の番号(追加された順、無向辺の場合はidが同じで方向が逆のものが2つ存在する)
        Edge() = default;
        Edge(int src, int dst, Cost cost=1, int id=-1) : src(src), dst(dst), cost(cost), id(id) {}
        operator int() const { return dst; }
    };

    int n; //!< 頂点数
    int m; //!< 辺数
    std::vector<std::vector<Edge>> g; //!< グラフの隣接リスト表現

    /**
     * @brief デフォルトコンストラクタ
     */
    Graph() : n(0), m(0), g(0) {}
    /**
     * @brief コンストラクタ
     * @param n 頂点数
     */
    explicit Graph(int n) : n(n), m(0), g(n) {}
    /**
     * @brief 無向辺を追加する
     * @param u 始点
     * @param v 終点
     * @param w コスト 省略したら1
     */
    void add_edge(int u, int v, Cost w=1) {
        g[u].push_back({u, v, w, m});
        g[v].push_back({v, u, w, m++});
    }
    /**
     * @brief 有向辺を追加する
     * @param u 始点
     * @param v 終点
     * @param w コスト 省略したら1
     */
    void add_directed_edge(int u, int v, Cost w=1) {
        g[u].push_back({u, v, w, m++});
    }
    /**
     * @brief 辺の情報を標準入力から受け取って追加する
     * @param m 辺の数
     * @param padding 頂点番号を入力からいくつずらすか 省略したら-1
     * @param weighted 辺の重みが入力されるか 省略したらfalseとなり、重み1で辺が追加される
     * @param directed 有向グラフかどうか 省略したらfalse
     */
    void read(int m, int padding=-1, bool weighted=false, bool directed=false) {
        for(int i = 0; i < m; i++) {
            int u, v; std::cin >> u >> v; u += padding, v += padding;
            Cost c(1);
            if(weighted) std::cin >> c;
            if(directed) add_directed_edge(u, v, c);
            else add_edge(u, v, c);
        }
    }
    /**
     * @brief ある頂点から出る辺を列挙する
     * @param v 頂点番号
     * @return std::vector<Edge>& vから出る辺のリスト
     */
    std::vector<Edge>& operator[](int v) {
        return g[v];
    }
    /**
     * @brief ある頂点から出る辺を列挙する
     * @param v 頂点番号
     * @return const std::vector<Edge>& vから出る辺のリスト
     */
    const std::vector<Edge>& operator[](int v) const {
        return g[v];
    }
    /**
     * @brief 辺のリスト
     * @return std::vector<Edge> 辺のリスト(idの昇順)
     *
     * 無向辺は代表して1つだけ格納される
     */
    std::vector<Edge> edges() const {
        std::vector<Edge> res(m);
        for(int i = 0; i < n; i++) {
            for(auto& e : g[i]) {
                res[e.id] = e;
            }
        }
        return res;
    }
    /**
     * @brief ある頂点から各頂点への最短路
     *
     * @param s 始点
     * @param weighted 1以外のコストの辺が存在するか 省略するとtrue
     * @param inf コストのminの単位元 未到達の頂点への距離はinfになる 省略すると-1
     * @return std::pair<std::vector<Cost>, std::vector<Edge>> first:各頂点への最短路長 second:各頂点への最短路上の直前の辺
     */
    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path(int s, bool weignted = true, Cost inf = -1) const {
        if(weignted) return shortest_path_dijkstra(s, inf);
        return shortest_path_bfs(s, inf);
    }
    
    std::vector<int> topological_sort() {
        std::vector<int> indeg(n), sorted;
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            for (int dst : g[i]) indeg[dst]++;
        }
        for (int i = 0; i < n; i++) {
            if (!indeg[i]) q.push(i);
        }
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (int dst : g[cur]) {
                if (!--indeg[dst]) q.push(dst);
            }
            sorted.push_back(cur);
        }
        return sorted;
    }

private:
    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path_bfs(int s, Cost inf) const {
        std::vector<Cost> dist(n, inf);
        std::vector<Edge> prev(n);
        std::queue<int> que;
        dist[s] = 0;
        que.push(s);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(auto& e : g[u]) {
                if(dist[e.dst] == inf) {
                    dist[e.dst] = dist[e.src] + 1;
                    prev[e.dst] = e;
                    que.push(e.dst);
                }
            }
        }
        return {dist, prev};
    }
    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path_dijkstra(int s, Cost inf) const {
        std::vector<Cost> dist(n, inf);
        std::vector<Edge> prev(n);
        using Node = std::pair<Cost, int>;
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> que;
        dist[s] = 0;
        que.push({0, s});
        while(!que.empty()) {
            auto [d, u] = que.top(); que.pop();
            if(d > dist[u]) continue;
            for(auto& e : g[u]) {
                if(dist[e.dst] == inf || dist[e.dst] > dist[e.src] + e.cost) {
                    dist[e.dst] = dist[e.src] + e.cost;
                    prev[e.dst] = e;
                    que.push({dist[e.dst], e.dst});
                }
            }
        }
        return {dist, prev};
    }


};
