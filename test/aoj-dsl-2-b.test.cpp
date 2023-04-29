#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B"

#include <iostream>

#include "../cpp/segtree.hpp"

int main(void) {
    int n, q; std::cin >> n >> q;
    RSumQ<int> seg(n);
    while(q--) {
        int com, x, y; std::cin >> com >> x >> y;
        if(com == 0) seg.apply(x, y);
        else std::cout << seg.prod(x, y + 1) << '\n';
    }
}