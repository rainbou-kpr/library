#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B"

#include <iostream>

#include "../cpp/potentialized-unionfind.hpp"

int main() {
    int n, q;
    std::cin >> n >> q;
    UnionFindPlus<long long> uf(n);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int x, y, z;
            std::cin >> x >> y >> z;
            uf.merge(x, y, z);
        } else {
            int x, y;
            std::cin >> x >> y;
            if (uf.same(x, y))
                std::cout << uf.diff(x, y) << std::endl;
            else
                std::cout << '?' << std::endl;
        }
    }
}
