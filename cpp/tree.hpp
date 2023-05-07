#pragma once

/**
 * @file tree.hpp
 * @brief 木の汎用テンプレート
*/

#include <stack>

#include "graph.hpp"

template <typename>
struct RootedTree;
template <typename>
struct DoublingClimbTree;

/**
 * @brief 根なし木
 * 
 * @tparam T = int 辺の重み
 * 
 * Graph<T>を継承し、すべて無向辺で表す
*/
template <typename T = int>
struct Tree : public Graph<T> {
    /**
     * @brief コンストラクタ
     * 
     * @param n ノード数
     */
    Tree(int n = 0) : Graph<T>(n) {}

    /**
     * @brief 辺の情報を標準入力から受け取って追加する
     * @param padding  = -1 頂点番号を入力からいくつずらすか
     * @param weighted = false 辺の重みが入力されるか
     */
    void read(int padding = -1, bool weighted = false) {
        Graph<T>::read(this->n - 1, padding, weighted, false);
    }

    /**
     * @brief 根付き木にする
     * 
     * @param root 根
     * @return RootedTree<T> 根付き木のオブジェクト
     */
    [[nodiscard]]
    RootedTree<T> set_root(int root) const {
        return RootedTree<T>(*this, root);
    }
    /**
     * @brief 根付き木にして返す
     * 
     * @param root 根
     * @return RootedTree<T> 根付き木のオブジェクト
     * 
     * set_root()に比べてコピーコストがかからないが、
     * ムーブされるため、このオブジェクトは使用不可になる
     * 複数種類の根を持った根付き木を得たい場合、set_root()を使う
     */
    [[nodiscard]]
    RootedTree<T> set_root_move(int root) {
        return RootedTree<T>(std::move(*this), root);
    }

    /**
     * @brief ダブリングLCAが使える根付き木を返す
     * 
     * @param root 根
     * @return DoublingClimbTree<T> ダブリング済み根付き木のオブジェクト
     */
    [[nodiscard]]
    DoublingClimbTree<T> build_lca(int root) const {
        RootedTree rooted_tree(*this, root);
        return DoublingClimbTree<T>(std::move(rooted_tree));
    }
    /**
     * @brief ダブリングLCAが使える根付き木を返す
     * 
     * @param root 根
     * @return DoublingClimbTree<T> ダブリング済み根付き木のオブジェクト
     *
     * build_lca()に比べてコピーコストがかからないが、
     * ムーブされるため、このオブジェクトは使用不可になる
     * 複数種類の根を持った根付き木を得たい場合、build_lca()を使う
     */
    [[nodiscard]]
    DoublingClimbTree<T> build_lca_move(int root) {
        RootedTree rooted_tree(std::move(*this), root);        
        return DoublingClimbTree<T>(std::move(rooted_tree));
    }
};

/**
 * @brief 根付き木
 * 
 * @tparam T = int 辺のコスト
 */
template <typename T = int>
struct RootedTree : public Tree<T> {
    using Edge = typename Graph<T>::Edge;

    int root; //!< 根
    std::vector<Edge> par; //!< 親へ向かう辺
    std::vector<std::vector<Edge>> child; //!< 子へ向かう辺のリスト
    std::vector<T> depth; //!< 深さのリスト
    std::vector<T> height; //!< 部分木の高さのリスト
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
    RootedTree(std::vector<int>& par_, int padding = -1) : Tree<T>(par_.size() + 1), root(0) {
        for(int i = 0; i < (int)par_.size(); i++) {
            this->add_edge(i + 1, par_[i] + padding);
        }
        build();
    }
    // Tree::set_root()から呼ばれる
    // 直接は呼ばない
    RootedTree(const Tree<T>& tree, int root) : Tree<T>(tree), root(root) {
        build();
    }
    // Tree::set_root_move()から呼ばれる
    // 直接は呼ばない
    RootedTree(Tree<T>&& tree, int root) : Tree<T>(std::move(tree)), root(root) {
        build();
    }
    
    /**
     * @brief ダブリングLCAが使える根付き木を得る
     * 
     * @return DoublingClimbTree<T> ダブリング済み根付き木のオブジェクト
     */
    [[nodiscard]]
    DoublingClimbTree<T> build_lca() {
        return DoublingClimbTree<T>(std::move(*this));
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
                for(int v : child[u]) {
                    sz[u] += sz[v];
                    if(height[u] < height[v] + 1) {
                        height[u] = height[v] + 1;
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
 * @tparam T = int 辺の重み(注: climbでは根の重みは考えない)
 */
template <typename T = int>
struct DoublingClimbTree : public RootedTree<T> {
    int height; //!< ダブリングの回数
    std::vector<std::vector<int>> doubling_par; //!< jから(1<<i)頂点登った頂点(存在しない場合は-1)
    
    // Tree::build_lca()やRootedTree::build_lca()から呼ばれる
    // 直接は呼ばない
    DoublingClimbTree(RootedTree<T>&& tree) : RootedTree<T>(std::move(tree)) {
        int n = this->n;
        height = 0;
        while((1 << height) < n) height++;
        doubling_par.assign(height, std::vector<int>(n, -1));
        for(int i = 0; i < n; i++) doubling_par[0][i] = this->par[i];
        for(int i = 0; i < height - 1; i++) {
            for(int j = 0; j < n; j++) {
                if(doubling_par[i][j] != -1) {
                    doubling_par[i+1][j] = doubling_par[i][doubling_par[i][j]];
                }
            }
        }
    }
    
    /**
     * @brief 頂点uからk回を根の方向に遡った頂点
     * 
     * @param u 元の頂点
     * @param k 登る段数
     * @return int k回登った頂点
     */
    int climb(int u, int k) const {
        for(int i = 0; i < height; i++) {
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
        for(int i = height - 1; i >= 0; i--) {
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
};