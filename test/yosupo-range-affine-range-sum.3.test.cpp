#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <iostream>
#include <utility>

#include "../cpp/lazy-segtree.hpp"
#include "../cpp/modint.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    using MI = modint998244353;
    std::vector<MI> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    struct RangeAffineRangeSum {
        using S = MI;
        S op(const S& a, const S& b) const {
            return a + b;
        }
        S e() const {
            return 0;
        }
        using F = std::pair<MI, MI>;
        S mapping(const F& f, const S& x, int sz) const {
            return f.first * x + f.second * MI(sz);
        }
        F composition(const F& f, const F& g) const {
            return {f.first * g.first, f.first * g.second + f.second};
        }
        F id() const {
            return {1, 0};
        };
    };
    TemplateLazySegTree<RangeAffineRangeSum> seg(a);
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int l, r;
            MI b, c;
            std::cin >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.prod(l, r) << '\n';
        }
    }
}
