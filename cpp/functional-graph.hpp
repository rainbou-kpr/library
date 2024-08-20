#pragma once

/**
 * @file functional-graph.hpp
 * @brief ファンクショナルグラフ
 */
#include <iostream>
#include <vector>

/**
 * @brief N頂点N辺の有向グラフで、すべての頂点の出次数が1
 */
struct FunctionalGraph {
    int n;
    std::vector<int> g;
    std::vector<bool> is_cycle;                //!< サイクル上の頂点か
    std::vector<int> depth;                    //!< サイクル上の頂点までの距離
    std::vector<int> root;                     //!< 最も近いサイクル上の頂点
    std::vector<std::vector<int>> cycle_list;  //!< サイクルリスト
    std::vector<int> cycle_id;                 //!< その頂点が属するサイクルリストのindex
    std::vector<int> root_idx;                 //!< rootのcycle_list上のindex

    void build() {
        is_cycle.resize(n);
        depth.resize(n);
        root.resize(n);
        cycle_id.resize(n);
        root_idx.resize(n);
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
     * @param n 頂点数
     * @param g i -> g[i]
     */
    explicit FunctionalGraph(int n, std::vector<int> g) : n(n), g(g) {
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
    int hop(int x, int k) const {
    }
    /**
     * @brief 頂点xから0回以上の移動でたどり着ける頂点の個数
     */
    int hopable(int x) const {
        return depth[x] + cycle_list[cycle_id[x]].size();
    }
};
