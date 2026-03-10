#pragma once

/**
 * @file functional-graph.hpp
 * @brief ファンクショナルグラフ
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

/**
 * @brief N頂点N辺の有向グラフで、すべての頂点の出次数が1
 */
struct FunctionalGraph {
    int n;                                         //!< 頂点数
    std::vector<int> g;                            //!< グラフ
    std::vector<bool> is_cycle;                    //!< サイクル上の頂点か
    std::vector<int> depth;                        //!< サイクル上の頂点までの距離
    std::vector<int> root;                         //!< 最も近いサイクル上の頂点
    std::vector<std::vector<int>> connected_list;  //!< 各連結成分のリスト
    std::vector<std::vector<int>> cycle_list;      //!< 各連結成分のサイクル
    std::vector<int> connected_id;                 //!< その頂点が属する連結成分のindex
    std::vector<int> root_idx;                     //!< rootのcycle_list上のindex
    std::vector<std::vector<int>> doubling;        //!< DoublingClimbTree

    void build() {
        is_cycle.resize(n);
        depth.resize(n);
        root.assign(n, -1);
        connected_id.resize(n);
        root_idx.resize(n);
        std::vector<bool> visited(n);
        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            std::vector<int> v;
            int u = i;
            while (!visited[u]) {
                visited[u] = true;
                v.push_back(u);
                u = g[u];
            }
            if (root[u] == -1) {
                int k = std::find(v.begin(), v.end(), u) - v.begin();
                cycle_list.push_back({});
                connected_list.push_back({});
                for (int j = 0; j < k; j++) {
                    is_cycle[v[j]] = false;
                    root[v[j]] = u;
                    root_idx[v[j]] = 0;
                    connected_id[v[j]] = cycle_list.size() - 1;
                    depth[v[j]] = k - j;
                    connected_list.back().push_back(v[j]);
                }
                for (int j = k; j < (int)v.size(); j++) {
                    is_cycle[v[j]] = true;
                    root[v[j]] = v[j];
                    cycle_list.back().push_back(v[j]);
                    root_idx[v[j]] = cycle_list.back().size() - 1;
                    connected_id[v[j]] = cycle_list.size() - 1;
                    depth[v[j]] = 0;
                    connected_list.back().push_back(v[j]);
                }
            } else {
                for (int j = 0; j < (int)v.size(); j++) {
                    is_cycle[v[j]] = false;
                    root[v[j]] = root[u];
                    root_idx[v[j]] = root_idx[u];
                    connected_id[v[j]] = connected_id[u];
                    depth[v[j]] = depth[u] + v.size() - j;
                    connected_list[connected_id[u]].push_back(v[j]);
                }
            }
        }
        doubling.resize(n);
        std::vector<int> tmp;
        for (int i = 0; i < n; i++) {
            if (is_cycle[i]) continue;
            tmp.push_back(i);
            doubling[i].push_back(g[i]);
        }
        for (int k = 0; !tmp.empty(); k++) {
            std::vector<int> next_tmp;
            for (int i : tmp) {
                if (k < (int)doubling[doubling[i][k]].size()) {
                    doubling[i].push_back(doubling[doubling[i][k]][k]);
                    next_tmp.push_back(i);
                }
            }
            tmp.swap(next_tmp);
        }
    }

    /**
     * @brief デフォルトコンストラクタ
     */
    FunctionalGraph() : n(0), g(0) {}
    /**
     * @brief コンストラクタ
     * @param n 頂点数
     */
    explicit FunctionalGraph(int n) : n(n), g(n) {}
    /**
     * @brief コンストラクタ
     * @param g i -> g[i]
     */
    explicit FunctionalGraph(std::vector<int> g) : n(g.size()), g(g) {
        build();
    }
    /**
     * @brief 辺の情報を標準入力から受け取って追加する
     * @param padding 頂点番号を入力からいくつずらすか 省略したら-1
     */
    void read(int padding = -1) {
        for (int i = 0; i < n; i++) {
            std::cin >> g[i];
            g[i] += padding;
        }
        build();
    }
    /**
     * @brief 頂点xからk回移動した頂点
     *
     * @param x 0 <= x < n
     * @param k 0 <= k
     * @return int 頂点番号
     */
    int hop(int x, long long k) const {
        if (k >= depth[x]) {
            k -= depth[x];
            x = root[x];
            k %= cycle_list[connected_id[x]].size();
            int y = root_idx[x] + k;
            if ((int)cycle_list[connected_id[x]].size() <= y) {
                y -= cycle_list[connected_id[x]].size();
            }
            return cycle_list[connected_id[x]][y];
        }
        for (int i = 0; k; i++) {
            if (k & 1) {
                x = doubling[x][i];
            }
            k >>= 1;
        }
        return x;
    }
    /**
     * @brief 頂点xから0回以上の移動でたどり着ける頂点の個数
     */
    int hopable(int x) const {
        return depth[x] + (int)cycle_list[connected_id[x]].size();
    }
};
