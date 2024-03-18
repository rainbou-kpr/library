#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <array>
#include <iostream>
#include <vector>

#include "../cpp/merge-sort-tree.hpp"

int main() {
    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::array<int, 3>> XYW(N);
    for (auto& [X, Y, W] : XYW) {
        std::cin >> X >> Y >> W;
    }
    std::sort(XYW.begin(), XYW.end());
    std::vector<int> v(N), key(N);
    std::vector<long long> value(N);
    for (int i = 0; i < N; i++) {
        v[i] = XYW[i][0];
        key[i] = XYW[i][1];
        value[i] = XYW[i][2];
    }
    MSTreeSum<long long, int> mstree(value, key);
    while (Q--) {
        int L, D, R, U;
        std::cin >> L >> D >> R >> U;
        int l = std::lower_bound(v.begin(), v.end(), L) - v.begin();
        int r = std::lower_bound(v.begin(), v.end(), R) - v.begin();
        std::cout << mstree.prod(l, r, D, U) << std::endl;
    }
}
