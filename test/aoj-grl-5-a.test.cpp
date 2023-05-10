#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_A"

#include <iostream>

#include "../cpp/tree.hpp"

int main(void) {
    int n; std::cin >> n;
    Tree<int> tree(n); tree.read(0, true);
    auto diameter = tree.diameter();
    int ans = 0;
    for(auto& e : diameter) ans += e.cost;
    std::cout << ans << '\n';
}