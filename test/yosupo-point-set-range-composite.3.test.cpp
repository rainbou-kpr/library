#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <iostream>

#include "../cpp/modint.hpp"
#include "../cpp/segtree.hpp"

int main() {
    int n, q;
    std::cin >> n >> q;
    using MI = modint998244353;
    struct RangeComposite {
        using S = std::pair<MI, MI>;
        S op(const S& l, const S& r) {
            return std::make_pair(r.first * l.first, r.first * l.second + r.second);
        }
        S e() {
            return std::make_pair(MI(1), MI(0));
        }
    };
    std::vector<std::pair<MI, MI>> v(n);
    for (int i = 0; i < n; i++) std::cin >> v[i].first >> v[i].second;
    TemplateSegTree<RangeComposite> seg(v);
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int p;
            MI c, d;
            std::cin >> p >> c >> d;
            seg.set(p, std::make_pair(c, d));
        } else {
            int l, r;
            MI x;
            std::cin >> l >> r >> x;
            auto f = seg.prod(l, r);
            std::cout << f.first * x + f.second << '\n';
        }
    }
}
