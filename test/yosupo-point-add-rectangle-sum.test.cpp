#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../cpp/segtree-2d.hpp"

#include <iostream>

int main(void) {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, q; std::cin >> n >> q;
    std::vector<std::tuple<int, int>> set_queries;
    std::vector<std::tuple<int, int, int, int>> prod_queries;
    std::vector<std::tuple<int, int, int, int, int>> queries;
    std::vector<int> xs, ys;
    for (int i = 0; i < n; i++) {
        int x, y, w; std::cin >> x >> y >> w;
        set_queries.emplace_back(x, y);
        queries.emplace_back(0, x, y, w, 0);
        xs.push_back(x);
        ys.push_back(y);
    }
    for(int i = 0; i < q; i++) {
        int op; std::cin >> op;
        if(op == 0) {
            int x, y, w; std::cin >> x >> y >> w;
            set_queries.emplace_back(x, y);
            queries.emplace_back(0, x, y, w, 0);
            xs.push_back(x);
            ys.push_back(y);
        } else {
            int l, d, r, u; std::cin >> l >> d >> r >> u;
            prod_queries.emplace_back(l, r, d, u);
            queries.emplace_back(1, l, d, r, u);
            xs.push_back(l);
            xs.push_back(r);
            ys.push_back(d);
            ys.push_back(u);
        }
    }
    std::sort(xs.begin(), xs.end());
    std::sort(ys.begin(), ys.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
    for(auto& [x, y] : set_queries) {
        x = std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        y = std::lower_bound(ys.begin(), ys.end(), y) - ys.begin();
    }
    for(auto& [lx, rx, ly, ry] : prod_queries) {
        lx = std::lower_bound(xs.begin(), xs.end(), lx) - xs.begin();
        rx = std::lower_bound(xs.begin(), xs.end(), rx) - xs.begin();
        ly = std::lower_bound(ys.begin(), ys.end(), ly) - ys.begin();
        ry = std::lower_bound(ys.begin(), ys.end(), ry) - ys.begin();
    }
    RSumQ2D<long long> seg(xs.size(), ys.size(), set_queries, prod_queries);
    for(auto& [op, a, b, c, d] : queries) {
        if(op == 0) {
            a = std::lower_bound(xs.begin(), xs.end(), a) - xs.begin();
            b = std::lower_bound(ys.begin(), ys.end(), b) - ys.begin();
            seg.apply(a, b, c);
        } else {
            a = std::lower_bound(xs.begin(), xs.end(), a) - xs.begin();
            b = std::lower_bound(ys.begin(), ys.end(), b) - ys.begin();
            c = std::lower_bound(xs.begin(), xs.end(), c) - xs.begin();
            d = std::lower_bound(ys.begin(), ys.end(), d) - ys.begin();
            std::cout << seg.prod(a, c, b, d) << '\n';
        }
    }
}
