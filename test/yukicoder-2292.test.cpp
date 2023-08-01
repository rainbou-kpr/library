#define PROBLEM "https://yukicoder.me/problems/9177"

#include "../cpp/lazy-segtree.hpp"
#include <iostream>

int main() {
    int n, q; std::cin >> n >> q;
    std::vector<int> x;
    std::vector<std::tuple<int, int, int>> qs(q);
    for(int i = 0; i < q; i++) {
        int t; std::cin >> t;
        if(t <= 2) {
            int l, r; std::cin >> l >> r; l--; r--;
            x.push_back(l);
            x.push_back(r);
            qs[i] = {t, l, r};
        } else if(t == 3) {
            int u, v; std::cin >> u >> v; u--; v--;
            if(u > v) std::swap(u, v);
            x.push_back(u);
            x.push_back(v);
            qs[i] = {t, u, v};
        } else {
            int v; std::cin >> v; v--;
            x.push_back(v);
            qs[i] = {t, v, 0};
        }
    }
    std::sort(x.begin(), x.end());
    x.erase(std::unique(x.begin(), x.end()), x.end());
    int m = x.size();
    RUpdateMinQ<int> seg(std::vector<int>(m, 0));
    for(auto [t, u, v] : qs) {
        if(t == 1) {
            u = std::lower_bound(x.begin(), x.end(), u) - x.begin();
            v = std::lower_bound(x.begin(), x.end(), v) - x.begin();
            seg.apply(u, v, 1);
        } else if(t == 2) {
            u = std::lower_bound(x.begin(), x.end(), u) - x.begin();
            v = std::lower_bound(x.begin(), x.end(), v) - x.begin();
            seg.apply(u, v, 0);
        } else if(t == 3) {
            u = std::lower_bound(x.begin(), x.end(), u) - x.begin();
            v = std::lower_bound(x.begin(), x.end(), v) - x.begin();
            std::cout << (u == v ? 1 : seg.prod(u, v)) << "\n";
        } else {
            u = std::lower_bound(x.begin(), x.end(), u) - x.begin();
            int r = seg.max_right(u, [&](int x) { return x > 0; });
            int l = seg.min_left(u, [&](int x) { return x > 0; });
            std::cout << x[r] - x[l] + 1 << "\n";
        }
    }
}
