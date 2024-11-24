#define PROBLEM "https://atcoder.jp/contests/abc256/tasks/abc256_e"

#include <iostream>

#include "../cpp/functional-graph.hpp"

int main(void) {
    int N;
    std::cin >> N;
    FunctionalGraph fg(N);
    fg.read();
    std::vector<int> C(N);
    for (int& c : C) std::cin >> c;
    long long ans = 0;
    for (const auto& cycle : fg.cycle_list) {
        int tmp = 1 << 30;
        for (int u : cycle)
            if (C[u] < tmp) tmp = C[u];
        ans += tmp;
    }
    std::cout << ans << std::endl;
}
