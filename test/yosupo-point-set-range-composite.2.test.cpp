#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <iostream>

#include "../cpp/modint.hpp"
#include "../cpp/segtree.hpp"

int main(void) {
    int n, q; std::cin >> n >> q;
    using S = std::pair<modint998244353, modint998244353>;
    std::vector<S> v(n);
    for(int i = 0; i < n; i++) std::cin >> v[i].first >> v[i].second;
    SegTree seg(v, [](const S& l, const S& r) {
            return std::make_pair(r.first * l.first, r.first * l.second + r.second);
        },
        std::make_pair(modint998244353(1), modint998244353(0))
    );
    while(q--) {
        int op; std::cin >> op;
        if(op == 0) {
            int p; modint998244353 c, d; std::cin >> p >> c >> d;
            seg.set(p, std::make_pair(c, d));
        } else {
            int l, r; modint998244353 x; std::cin >> l >> r >> x;
            S f = seg.prod(l, r);
            std::cout << f.first * x + f.second << '\n';
        }
    }
}