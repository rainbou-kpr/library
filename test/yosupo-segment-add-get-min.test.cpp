#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include "../cpp/convex-hull-trick.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

int main(void) {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, q; std::cin >> n >> q;
    std::vector<std::tuple<int, long long, long, long long, long long>> qs(n+q);
    std::vector<long long> xs;
    for(int i = 0; i < n; i++) {
        long long l, r, a, b; std::cin >> l >> r >> a >> b;
        qs[i] = std::make_tuple(0, l, r, a, b);
        xs.push_back(l);
        xs.push_back(r);
    }
    for(int i = 0; i < q; i++) {
        int op; std::cin >> op;
        if(op == 0) {
            long long l, r, a, b; std::cin >> l >> r >> a >> b;
            qs[n+i] = std::make_tuple(0, l, r, a, b);
        } else {
            long long p; std::cin >> p;
            qs[n+i] = std::make_tuple(1, p, 0, 0, 0);
            xs.push_back(p);
        }
    }
    std::sort(xs.begin(), xs.end());
    LiChaoTree<long long> cht(xs);
    for(auto [op, l, r, a, b] : qs) {
        if(op == 0) {
            int li = std::lower_bound(xs.begin(), xs.end(), l) - xs.begin();
            int ri = std::lower_bound(xs.begin(), xs.end(), r) - xs.begin();
            cht.add_segment(a, b, li, ri);
        } else {
            int i = std::lower_bound(xs.begin(), xs.end(), l) - xs.begin();
            long long res = cht.get_min(i);
            if(res == std::numeric_limits<long long>::max()) {
                std::cout << "INFINITY\n";
            } else {
                std::cout << res << '\n';
            }
        }
    }
}
