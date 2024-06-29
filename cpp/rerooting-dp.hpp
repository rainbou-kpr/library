#pragma once

/**
 * @file rerooting-dp.hpp
 * @brief 全方位木DP
 */
#include <algorithm>
#include <type_traits>
#include "tree.hpp"

/**
 * @brief 全方位木DP
 * dp[u] = addnode(merge(addedge(dp[v1], g_uv1, uv1.id), merge(addedge(dp[v2], g_uv2, uv2.id), ...)), u) v_iはuの子
 *
 * @tparam E 可換モノイド
 * @tparam V DPの型
 * @param tree
 * @param e 可換モノイドの単位元
 * @param merge (E,E)->E 可換
 * @param addedge (V,Cost,int)->E
 * @param addnode (E,int)->V
 * @return std::vector<V>
 */
template <typename E, typename V = E, class Merge, class AddEdge, class AddNode, typename Cost>
std::vector<V> rerooting_dp(const Tree<Cost>& tree, E e, Merge merge, AddEdge addedge, AddNode addnode) {
    static_assert(std::is_invocable_r_v<E, Merge, E, E>);
    static_assert(std::is_invocable_r_v<E, AddEdge, V, Cost, int>);
    static_assert(std::is_invocable_r_v<V, AddNode, E, int>);
    RootedTree<Cost> rooted(tree, 0);
    std::vector<V> subdp(rooted.n);
    for (int u : rooted.postorder) {
        E tmp = e;
        for (auto edge : rooted.child[u]) {
            tmp = merge(tmp, addedge(subdp[edge.dst], edge.cost, edge.id));
        }
        subdp[u] = addnode(tmp, u);
    }
    std::vector<V> dp(rooted.n);
    std::vector<E> pe(rooted.n, e);
    for (int u : rooted.preorder) {
        const auto& ch = rooted.child[u];
        std::vector<E> ri(ch.size() + 1, e);
        for (size_t i = ch.size(); i > 0; i--) {
            ri[i - 1] = merge(ri[i], addedge(subdp[ch[i - 1].dst], ch[i - 1].cost, ch[i - 1].id));
        }
        dp[u] = addnode(merge(pe[u], ri[0]), u);
        E le = e;
        for (size_t i = 0; i < ch.size(); i++) {
            pe[ch[i].dst] = addedge(addnode(merge(pe[u], merge(le, ri[i + 1])), u), ch[i].cost, ch[i].id);
            le = merge(le, addedge(subdp[ch[i].dst], ch[i].cost, ch[i].id));
        }
    }
    return dp;
}

/**
 * @brief 最も遠い頂点までの距離
 */
template <typename Cost>
inline std::vector<Cost> farthest_node_dist(const Tree<Cost>& tree) {
    return rerooting_dp(
        tree,
        Cost{},
        [](Cost a, Cost b) { return std::max<Cost>(a, b); },
        [](Cost a, Cost c, int) { return a + c; },
        [](Cost a, int) { return a; });
}

/**
 * @brief 他の全ての頂点との距離の合計
 */
template <typename Cost>
inline std::vector<Cost> distance_sums(const Tree<Cost>& tree) {
    using P = typename std::pair<Cost, int>;
    auto tmp = rerooting_dp(
        tree,
        P{{}, 0},
        [](P a, P b) { return P{a.first + b.first, a.second + b.second}; },
        [](P a, Cost c, int) { return P{a.first + a.second * c, a.second}; },
        [](P a, int) { return P{a.first, a.second + 1}; });
    std::vector<Cost> res;
    res.reserve(tree.n);
    for (const P& s : tmp) res.push_back(s.first);
    return res;
}

/**
 * @brief その頂点を含む連結な部分グラフの個数
 */
template <typename V, typename Cost>
inline std::vector<V> connected_subgraph_count(const Tree<Cost>& tree) {
    return rerooting_dp(
        tree,
        V(1),
        [](V a, V b) { return a * b; },
        [](V a, Cost c, int) { return a + 1; },
        [](V a, int) { return a; });
}
