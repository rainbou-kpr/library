#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>

#include "../cpp/tree.hpp"
#include "../cpp/segtree.hpp"

int main(void) {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(0);
    int n, q; std::cin >> n >> q;
    std::vector<int> par(n-1);
    for(int i = 0; i < n-1; i++) std::cin >> par[i];
    RootedTree tree(par, 0);
    RMinQ<long long> et_depth(tree.euler_tour.size());
    std::vector<int> pre_idx(n);
    for(int i = 0; i < (int)tree.euler_tour.size(); i++) {
        auto [u, cnt] = tree.euler_tour[i];
        et_depth[i] = (long long)tree.depth[u] * n + u;
        if(cnt == 0) pre_idx[u] = i;
    }
    while(q--) {
        int u, v; std::cin >> u >> v;
        if(pre_idx[u] > pre_idx[v]) std::swap(u, v);
        std::cout << et_depth.prod(pre_idx[u], pre_idx[v]+1) % n << '\n';
    }
}