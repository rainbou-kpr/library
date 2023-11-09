#pragma once

/**
 * @file graph.hpp
 * @brief 木の汎用テンプレート
 */

#include <stack>

#include "graph.hpp"

/**
 * 無向グラフについて、二部グラフなら0と1に彩色した結果をひとつ返し、二部グラフでないなら空のvectorを返す。
 **/
template <typename Cost = int>
std::vector<int> bipartite_coloring(const Graph<Cost>& graph) {
    std::vector<int> color(graph.n, -1);
    for (int i = 0; i < graph.n; i++) {
        if (color[i] != -1) continue;
        std::stack<int> stk;
        stk.push(i);
        color[i] = 0;
        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();
            for (int v : graph[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    stk.push(v);
                } else {
                    if (color[u] == color[v]) return {};
                }
            }
        }
    }
    return color;
}

/**
 * 無向グラフについて、二部グラフならtrue、二部グラフでないならfalseを返す。
 **/
template <typename Cost = int>
bool is_bipartite_graph(const Graph<Cost>& graph) {
    return !bipartite_coloring(graph).empty();
}