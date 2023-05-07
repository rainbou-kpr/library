#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>

#include "../cpp/tree.hpp"

int main(void) {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(0);
    int n, q; std::cin >> n >> q;
    std::vector<int> par(n-1);
    for(int i = 0; i < n-1; i++) std::cin >> par[i];
    RootedTree tmp_tree(par, 0);
    auto tree = tmp_tree.build_lca();
    while(q--) {
        int u, v; std::cin >> u >> v;
        std::cout << tree.lca(u, v) << '\n';
    }
}