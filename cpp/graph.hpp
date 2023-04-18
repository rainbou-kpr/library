#pragma once

#include <iostream>
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
     * operator int()を定義しているので、int型にキャストすると勝手にtoになる
     * 例えば、
     * for (auto& e : g[v]) をすると、vから出る辺が列挙されるが、
     * for (int to : g[v]) とすると、vから出る辺の行き先が列挙される
     */
    struct Edge {
        int from; //!< 始点
        int to; //!< 終点
        Cost cost; //!< コスト
        int id; //!< 辺の番号(追加された順、無向辺の場合はidが同じで方向が逆のものが2つ存在する)
        Edge() = default;
        Edge(int from, int to, Cost cost=1, int id=-1) : from(from), to(to), cost(cost), id(id) {}
        operator int() const { return to; }
    };

    int n; //!< 頂点数
    int m; //!< 辺数
    std::vector<std::vector<Edge>> g; //!< グラフの隣接リスト表現
    /**
     * @brief コンストラクタ
     *
     * @param n 頂点数
     */
    Graph(int n=0) : n(n), m(0), g(n) {}
    /**
     * @brief 無向辺を追加する
     *
     * @param from 始点
     * @param to 終点
     * @param cost コスト 省略したら1
     * @return int 追加された辺の番号
     */
    void add_edge(int u, int v, Cost w=1) {
        g[u].push_back({u, v, w, m});
        g[v].push_back({v, u, w, m++});
    }
    /**
     * @brief 有向辺を追加する
     *
     * @param from 始点
     * @param to 終点
     * @param cost コスト 省略したら1
     * @return int 追加された辺の番号
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
     * @return std::vector<Cost> 各頂点への最短路長
     */
    std::vector<Cost> shortest_path(int s) const {
        std::vector<Cost> dist(n, std::numeric_limits<Cost>::max());
        dist[s] = 0;
        std::vector<bool> used(n, false);
        while(true) {
            int v = -1;
            for(int u = 0; u < n; u++) {
                if(!used[u] && (v == -1 || dist[u] < dist[v])) v = u;
            }
            if(v == -1) break;
            used[v] = true;
            for(auto& e : g[v]) {
                dist[e.to] = std::min(dist[e.to], dist[v] + e.cost);
            }
        }
        return dist;
    }
    /**
     * @brief ある頂点から各頂点への最短路
     *
     * @param s 始点
     * @return std::vector<Cost> 各頂点への最短路長
     */
    std::vector<Cost> shortest_path(int s) {
        std::vector<Cost> dist(n, std::numeric_limits<Cost>::max());
        dist[s] = 0;
        std::vector<bool> used(n, false);
        while(true) {
            int v = -1;
            for(int u = 0; u < n; u++) {
                if(!used[u] && (v == -1 || dist[u] < dist[v])) v = u;
            }
            if(v == -1) break;
            used[v] = true;
            for(auto& e : g[v]) {
                dist[e.to] = std::min(dist[e.to], dist[v] + e.cost);
            }
        }
        return dist;
    }
    /**
     * @brief ある頂点から各頂点への最短路
     *
     * @param s 始点
     * @return std::pair<std::vector<Cost>, std::vector<Edge>> first:各頂点への最短路長 second:各頂点への最短路上の直前の辺
     */
    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path_with_prev(int s) const {
        std::vector<Cost> dist(n, std::numeric_limits<Cost>::max());
        dist[s] = 0;
        std::vector<Edge> prev(n, {-1, -1, 0, -1});
        std::vector<bool> used(n, false);
        while(true) {
            int v = -1;
            for(int u = 0; u < n; u++) {
                if(!used[u] && (v == -1 || dist[u] < dist[v])) v = u;
            }
            if(v == -1) break;
            used[v] = true;
            for(auto& e : g[v]) {
                if(dist[e.to] > dist[v] + e.cost) {
                    dist[e.to] = dist[v] + e.cost;
                    prev[e.to] = e;
                }
            }
        }
        return {dist, prev};
    }
    /**
     * @brief ある頂点から各頂点への最短路
     *
     * @param s 始点
     * @param weighted 1以外のコストの辺が存在するか 省略するとfalse
     * @param inf コストのminの単位元 省略するとstd::numeric_limits<Cost>::max() pairなどをコストにしている場合は設定する必要があり
     * @return std::pair<std::vector<Cost>, std::vector<Edge>> first:各頂点への最短路長 second:各頂点への最短路上の直前の辺
     */
    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path(int s, bool weignted = false, Cost inf = std::numeric_limits<Cost>::max()) {
        if(weignted) return shortest_path_dijkstra(s, inf);
        return shortest_path_bfs(s);
    }

private:
    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path_bfs(int s) {
        std::vector<Cost> dist(n, std::numeric_limits<Cost>::max());
        std::vector<Edge> prev(n);
        std::queue<int> que;
        dist[s] = 0;
        que.push(s);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(auto& e : g[u]) {
                if(dist[e.to] < dist[e.from] + 1) {
                    dist[e.to] = dist[e.from] + 1;
                    prev[e.to] = e;
                    que.push(e.to);
                }
            }
        }
        return {dist, prev};
    }
    std::pair<std::vector<Cost>, std::vector<Edge>> shortest_path_dijkstra(int s, Cost inf) {
        std::vector<Cost> dist(n, inf);
        std::vector<Edge> prev(n);
        using Node = std::pair<Cost, int>;
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> que;
        dist[s] = 0;
        que.push(s);
        while(!que.empty()) {
            auto [d, u] = que.front(); que.pop();
            if(d > dist[u]) continue;
            for(auto& e : g[u]) {
                if(dist[e.to] < dist[e.from] + e.cost) {
                    dist[e.to] = dist[e.from] + e.cost;
                    prev[e.to] = e;
                    que.push(e.to);
                }
            }
        }
        return {dist, prev};
    }
};
