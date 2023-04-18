#pragma once

#include <iostream>
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
};
