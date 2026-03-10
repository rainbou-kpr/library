#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595"

#include <iostream>

#include "../cpp/rerooting-dp.hpp"

int main() {
    int N;
    std::cin >> N;
    Tree<long long> tree(N);
    tree.read();
    auto ans = farthest_node_dist(tree);
    for (int i = 0; i < N; i++) {
        std::cout << 2 * N - 2 - ans[i] << std::endl;
    }
}
