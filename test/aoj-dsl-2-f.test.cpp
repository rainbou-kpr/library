#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F"

#include <iostream>

#include "../cpp/lazy-segtree.hpp"

int main(void) {
    int n, q; std::cin >> n >> q;
    RUpdateMinQ<int> seg(n);
    while(q--) {
        int op; std::cin >> op;
        if(op == 0) {
            int s, t, x; std::cin >> s >> t >> x; t++;
            seg.apply(s, t, x);
        } else {
            int s, t; std::cin >> s >> t; t++;
            std::cout << seg.prod(s, t) << '\n';
        }
    }
}