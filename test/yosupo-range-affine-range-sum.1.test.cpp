#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <iostream>

#include "../cpp/modint.hpp"
#include "../cpp/lazy-segtree.hpp"

int main(void) {
    int n, q; std::cin >> n >> q;
    using MI = modint998244353;
    std::vector<MI> a(n);
    for(int i = 0; i < n; i++) std::cin >> a[i];
    struct Affine { MI a, b; };
    struct Mapping {
        MI operator() (const Affine& f, MI x, int sz) {
            return f.a * x + f.b * MI(sz);
        }
    };
    struct Composition {
        Affine operator() (const Affine& f, const Affine& g) {
            return {f.a * g.a, f.a * g.b + f.b};
        }
    };
    struct Id {
        Affine operator() () {
            return {1, 0};
        }
    };
    StaticLazySegTree<MI, std::plus<MI>, lazy_segtree::Zero<MI>, Affine, Mapping, Composition, Id> seg(a);
    while(q--) {
        int op; std::cin >> op;
        if(op == 0) {
            int l, r; MI b, c; std::cin >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            int l, r; std::cin >> l >> r;
            std::cout << seg.prod(l, r) << '\n';
        }
    }
}