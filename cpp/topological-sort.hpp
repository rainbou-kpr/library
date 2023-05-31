#pragma once

#include "graph.hpp"

/**
 * @brief 有向グラフをトポロジカルソートする
 * @param G トポロジカルソートするグラフ
 * @return ソートされたノード番号のvector DAGでなければ長さがG.n未満になる
 */
template<typename Cost>
std::vector<int> topological_sort(const Graph<Cost> &G) {
    std::vector<int> indeg(G.n), sorted;
    std::queue<int> q;
    for (int i = 0; i < G.n; i++) {
        for (int dst : G[i]) indeg[dst]++;
    }
    for (int i = 0; i < G.n; i++) {
        if (!indeg[i]) q.push(i);
    }
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int dst : G[cur]) {
            if (!--indeg[dst]) q.push(dst);
        }
        sorted.push_back(cur);
    }
    return sorted;
}
