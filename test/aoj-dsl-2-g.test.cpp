#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"

#include <iostream>

#include "../cpp/lazy-segtree.hpp"

int main(void) {
    int n, q; std::cin >> n >> q;
    RAddSumQ<long long> seg(n);
    while(q--) {
        int op; std::cin >> op;
        if(op == 0) {
            int s, t; long long x; std::cin >> s >> t >> x; s--;
            seg.apply(s, t, x);
        } else {
            int s, t; std::cin >> s >> t; s--;
            std::cout << seg.prod(s, t) << '\n';
        }
    }
}