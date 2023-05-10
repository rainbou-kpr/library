#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B"

#include <iostream>

#include "../cpp/tree.hpp"

int main(void) {
    int n; std::cin >> n;
    Tree<int> tree(n); tree.read(0, true);
    RootedTree<int> rooted_tree = tree.set_root(0);
    std::vector<int> dp(n);
    std::vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        int u = rooted_tree.preorder[i];
        ans[u] = std::max(dp[u], rooted_tree.height[u]);
        auto& child = rooted_tree.child[u];
        int s = child.size();
        std::vector<int> height_lmax(s+1), height_rmax(s+1);
        for(int j = 0; j < s; j++) {
            auto& e = child[j];
            height_lmax[j+1] = std::max(height_lmax[j], rooted_tree.height[e] + e.cost);
        }
        for(int j = s-1; j >= 0; j--) {
            auto& e = child[j];
            height_rmax[j] = std::max(height_rmax[j+1], rooted_tree.height[e] + e.cost);
        }
        for(int j = 0; j < s; j++) {
            auto& e = child[j];
            dp[e] = std::max(dp[u], std::max(height_lmax[j], height_rmax[j+1])) + e.cost;
        }
    }
    for(int i = 0; i < n; i++) {
        std::cout << ans[i] << '\n';
    }
}
