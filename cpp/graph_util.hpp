#pragma once

/**
 * @file graph_util.hpp
 * @brief グラフに関する関数
 */

#include <stack>

#include "graph.hpp"

/**
 * @brief 無向グラフについて、二部グラフなら0と1に彩色した結果をひとつ返し、二部グラフでないなら空のvectorを返す。
 * 連結成分のうち、インデックスの最も小さいものを0にする。
 * @return std::vector<int> 各頂点の彩色結果
 */
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
 * @brief 無向グラフについて、二部グラフかどうかを判定する。
 * @return bool 二部グラフならtrue、二部グラフでないならfalseを返す。
 */
template <typename Cost = int>
bool is_bipartite(const Graph<Cost>& graph) {
    return !bipartite_coloring(graph).empty();
}

/**
 * @brief 無向グラフについて、連結成分分解する。
 * @return std::vector<std::vector<int>> 「同じ連結成分となる頂点のリスト」のリスト
 */
template <typename Cost = int>
std::vector<std::vector<int>> connected_components(const Graph<Cost>& graph) {
    std::vector<std::vector<int>> groups;
    std::vector<bool> visited(graph.n);
    for (int i = 0; i < graph.n; i++) {
        if (visited[i]) continue;
        std::stack<int> stk;
        stk.push(i);
        visited[i] = true;
        groups.push_back({i});
        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();
            for (int v : graph[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                stk.push(v);
                groups.back().push_back(v);
            }
        }
    }
    return groups;
}

/**
 * @brief 無向グラフについて、連結グラフかどうかを判定する。
 * @return bool 連結グラフならtrue、連結グラフでないならfalseを返す。
 */
template <typename Cost = int>
bool is_connected(const Graph<Cost>& graph) {
    return connected_components(graph).size() == 1;
}

/**
 * @brief 無向グラフについて、木かどうかを判定する。
 * @return bool 木ならtrue、木でないならfalseを返す。
 */
template <typename Cost = int>
bool is_tree(const Graph<Cost>& graph) {
    return graph.m == graph.n - 1 && is_connected(graph);
}
