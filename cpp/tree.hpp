#pragma once

/**
 * @file tree.hpp
 * @brief 木の汎用テンプレート
*/

#include <algorithm>
#include <stack>
#include <tuple>

#include "graph.hpp"

template <typename>
struct RootedTree;
template <typename>
struct DoublingClimbTree;

/**
 * @brief 根なし木
 * 
 * @tparam Cost = int 辺の重み
 * 
 * Graph<Cost>を継承し、すべて無向辺で表す
*/
template <typename Cost = int>
struct Tree : private Graph<Cost> {
    // Graph<Cost>* g = new Tree<Cost>(); ができてしまうと、delete時にメモリリークが発生
    // 回避するためprivate継承にして、メンバをすべてusing宣言
    using Edge = typename Graph<Cost>::Edge;
    using Graph<Cost>::n;
    using Graph<Cost>::m;
    using Graph<Cost>::g;
    using Graph<Cost>::Graph;
    using Graph<Cost>::add_edge;
    using Graph<Cost>::add_directed_edge;
    using Graph<Cost>::read;
    using Graph<Cost>::operator[];
    using Graph<Cost>::edges;
    using Graph<Cost>::shortest_path;

    /**
     * @brief コンストラクタ
     * 
     * @param n ノード数
     */
    Tree(int n = 0) : Graph<Cost>(n) {}

    /**
     * @brief 辺の情報を標準入力から受け取って追加する
     * @param padding  = -1 頂点番号を入力からいくつずらすか
     * @param weighted = false 辺の重みが入力されるか
     */
    void read(int padding = -1, bool weighted = false) {
        Graph<Cost>::read(this->n - 1, padding, weighted, false);
    }
    
    /**
     * @brief 木の直径
     * 
     * @param weighted = true 重み付きか
     * @return std::vector<Edge> 直径を構成する辺のリスト
     */
    std::vector<Edge> diameter(bool weighted = true) const {
        std::vector<Cost> dist = shortest_path(0, weighted).first;
        int u = std::max_element(dist.begin(), dist.end()) - dist.begin();
        std::vector<Edge> prev;
        std::tie(dist, prev) = shortest_path(u, weighted);
        int v = std::max_element(dist.begin(), dist.end()) - dist.begin();
        std::vector<Edge> path;
        while(v != u) {
            path.push_back(prev[v]);
            v = prev[v].src;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    /**
     * @brief 根付き木にする
     * 
     * @param root 根
     * @return RootedTree<Cost> 根付き木のオブジェクト
     */
    [[nodiscard]]
    RootedTree<Cost> set_root(int root) const& {
        return RootedTree<Cost>(*this, root);
    }
    /**
     * @brief 根付き木にして返す
     * 
     * @param root 根
     * @return RootedTree<Cost> 根付き木のオブジェクト
     */
    [[nodiscard]]
    RootedTree<Cost> set_root(int root) && {
        return RootedTree<Cost>(std::move(*this), root);
    }

    /**
     * @brief ダブリングLCAが使える根付き木を返す
     * 
     * @param root 根
     * @return DoublingClimbTree<Cost> ダブリング済み根付き木のオブジェクト
     */
    [[nodiscard]]
    DoublingClimbTree<Cost> build_lca(int root) const& {
        RootedTree rooted_tree(*this, root);
        return DoublingClimbTree<Cost>(std::move(rooted_tree));
    }
    /**
     * @brief ダブリングLCAが使える根付き木を返す
     * 
     * @param root 根
     * @return DoublingClimbTree<Cost> ダブリング済み根付き木のオブジェクト
     */
    [[nodiscard]]
    DoublingClimbTree<Cost> build_lca(int root) && {
        RootedTree rooted_tree(std::move(*this), root);        
        return DoublingClimbTree<Cost>(std::move(rooted_tree));
    }
};

/**
 * @brief 根付き木
 * 
 * @tparam Cost = int 辺のコスト
 */
template <typename Cost = int>
struct RootedTree : private Tree<Cost> {
    using Edge = typename Tree<Cost>::Edge;
    using Tree<Cost>::n;
    using Tree<Cost>::m;
    using Tree<Cost>::g;
    using Tree<Cost>::add_edge;
    using Tree<Cost>::add_directed_edge;
    using Tree<Cost>::read;
    using Tree<Cost>::operator[];
    using Tree<Cost>::edges;
    using Tree<Cost>::shortest_path;
    using Tree<Cost>::Tree;

    int root; //!< 根
    std::vector<Edge> par; //!< 親へ向かう辺
    std::vector<std::vector<Edge>> child; //!< 子へ向かう辺のリスト
    std::vector<Cost> depth; //!< 深さのリスト
    std::vector<Cost> height; //!< 部分木の高さのリスト
    std::vector<int> sz; //!< 部分期の頂点数のリスト
    std::vector<int> preorder; //!< 先行順巡回
    std::vector<int> postorder; //!< 後行順巡回
    std::vector<std::pair<int, int>> euler_tour; //!< オイラーツアー DFS中にとおった頂点の(頂点番号,その頂点を通った回数)のリスト
    
    /**
     * @brief 親の頂点のリストから根が0の根付き木を構築するコンストラクタ
     * 
     * @param par_ 頂点0以外の親の頂点のリスト
     * @param padding = -1 parの頂点番号をいくつずらすか
     */
    RootedTree(const std::vector<int>& par_, int padding = -1) : Tree<Cost>(par_.size() + 1), root(0) {
        for(int i = 0; i < (int)par_.size(); i++) {
            this->add_edge(i + 1, par_[i] + padding);
        }
        build();
    }
    // Tree::set_root()から呼ばれる
    // 直接は呼ばない
    RootedTree(const Tree<Cost>& tree, int root) : Tree<Cost>(tree), root(root) {
        build();
    }
    // Tree::set_rootから呼ばれる
    // 直接は呼ばない
    RootedTree(Tree<Cost>&& tree, int root) : Tree<Cost>(std::move(tree)), root(root) {
        build();
    }
    
    /**
     * @brief ダブリングLCAが使える根付き木を得る
     * 
     * @return DoublingClimbTree<Cost> ダブリング済み根付き木のオブジェクト
     */
    [[nodiscard]]
    DoublingClimbTree<Cost> build_lca() const& {
        return DoublingClimbTree<Cost>(*this);
    }

    /**
     * @brief ダブリングLCAが使える根付き木を得る
     * 
     * @return DoublingClimbTree<Cost> ダブリング済み根付き木のオブジェクト
     */
    [[nodiscard]]
    DoublingClimbTree<Cost> build_lca() && {
        return DoublingClimbTree<Cost>(std::move(*this));
    }

private:
    void build() {
        int n = this->n;
        par.resize(n);
        par[root] = {root, -1, 0, -1};
        child.resize(n);
        depth.resize(n);
        height.resize(n);
        sz.resize(n);
        std::vector<int> iter(n);
        std::stack<std::pair<int, int>> stk;
        stk.emplace(root, 0);
        while(!stk.empty()) {
            auto [u, cnt] = stk.top(); stk.pop();
            euler_tour.emplace_back(u, cnt);
            if(iter[u] == 0) preorder.push_back(u);
            while(iter[u] < (int)this->g[u].size() && this->g[u][iter[u]].dst == par[u]) iter[u]++;
            if(iter[u] == (int)this->g[u].size()) {
                postorder.push_back(u);
                sz[u] = 1;
                height[u] = 0;
                for(auto& e : child[u]) {
                    sz[u] += sz[e.dst];
                    if(height[u] < height[e.dst] + e.cost) {
                        height[u] = height[e.dst] + e.cost;
                    }
                }
            } else {
                auto& e = this->g[u][iter[u]++];
                par[e.dst] = {e.dst, u, e.cost, e.id};
                child[u].push_back(e);
                depth[e.dst] = depth[u] + e.cost;
                stk.emplace(u, cnt + 1);
                stk.emplace(e.dst, 0);
            }
        }
    }
};

/**
 * @brief 親頂点ダブリング済み根付き木
 * 
 * @tparam Cost = int 辺の重み(注: climbでは根の重みは考えない)
 */
template <typename Cost = int>
struct DoublingClimbTree : private RootedTree<Cost> {
    using Edge = typename RootedTree<Cost>::Edge;
    using RootedTree<Cost>::n;
    using RootedTree<Cost>::m;
    using RootedTree<Cost>::g;
    using RootedTree<Cost>::add_edge;
    using RootedTree<Cost>::add_directed_edge;
    using RootedTree<Cost>::read;
    using RootedTree<Cost>::operator[];
    using RootedTree<Cost>::edges;
    using RootedTree<Cost>::shortest_path;
    using RootedTree<Cost>::RootedTree;
    using RootedTree<Cost>::root;
    using RootedTree<Cost>::par;
    using RootedTree<Cost>::child;
    using RootedTree<Cost>::depth;
    using RootedTree<Cost>::height;
    using RootedTree<Cost>::sz;
    using RootedTree<Cost>::preorder;
    using RootedTree<Cost>::postorder;
    using RootedTree<Cost>::euler_tour;

    int h; //!< ダブリングの回数
    std::vector<std::vector<int>> doubling_par; //!< jから(1<<i)頂点登った頂点(存在しない場合は-1)
    
    // Tree::build_lca()やRootedTree::build_lca()から呼ばれる
    // 直接は呼ばない
    DoublingClimbTree(const RootedTree<Cost>& tree) : RootedTree<Cost>(tree) {
        build();
    }
    // Tree::build_lca()やRootedTree::build_lca()から呼ばれる
    // 直接は呼ばない
    DoublingClimbTree(RootedTree<Cost>&& tree) : RootedTree<Cost>(std::move(tree)) {
        build();
    }
    
    /**
     * @brief 頂点uからk回を根の方向に遡った頂点
     * 
     * @param u 元の頂点
     * @param k 登る段数
     * @return int k回登った頂点
     */
    int climb(int u, int k) const {
        for(int i = 0; i < h; i++) {
            if(k >> i & 1) u = doubling_par[i][u];
            if(u == -1) return -1;
        }
        return u;
    }
    
    /**
     * @brief 最小共通祖先
     * 
     * @param u 頂点1
     * @param v 頂点2
     * @return int LCAの頂点番号
     */
    int lca(int u, int v) const {
        if(this->depth[u] > this->depth[v]) std::swap(u, v);
        v = climb(v, this->depth[v] - this->depth[u]);
        if(this->depth[u] > this->depth[v]) u = climb(u, this->depth[u] - this->depth[v]);
        if(u == v) return u;
        for(int i = h - 1; i >= 0; i--) {
            int nu = doubling_par[i][u];
            int nv = doubling_par[i][v];
            if(nu == -1) continue;
            if(nu != nv) {
                u = nu;
                v = nv;
            }
        }
        return this->par[u];
    }
    
    /**
     * @brief 頂点間距離(重みなし)
     * 
     * @param u 頂点1
     * @param v 頂点2
     * @return int uとv間の最短経路の辺の本数
     */
    int dist(int u, int v) const {
        return this->depth[u] + this->depth[v] - this->depth[lca(u, v)] * 2;
    }
    
private:
    void build() {
        int n = this->n;
        h = 0;
        while((1 << h) < n) h++;
        doubling_par.assign(h, std::vector<int>(n, -1));
        for(int i = 0; i < n; i++) doubling_par[0][i] = this->par[i];
        for(int i = 0; i < h - 1; i++) {
            for(int j = 0; j < n; j++) {
                if(doubling_par[i][j] != -1) {
                    doubling_par[i+1][j] = doubling_par[i][doubling_par[i][j]];
                }
            }
        }
    }
};