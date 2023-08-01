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
    std::vector<std::tuple<int, long long, long>> qs(n+q);
    std::vector<long long> xs;
    for(int i = 0; i < n; i++) {
        long long a, b; std::cin >> a >> b;
        qs[i] = std::make_tuple(0, a, b);
    }
    for(int i = 0; i < q; i++) {
        int op; std::cin >> op;
        if(op == 0) {
            long long a, b; std::cin >> a >> b;
            qs[n+i] = std::make_tuple(0, a, b);
        } else {
            long long p; std::cin >> p;
            qs[n+i] = std::make_tuple(1, p, 0);
            xs.push_back(p);
        }
    }
    std::sort(xs.begin(), xs.end());
    LiChaoTree<long long> cht(xs);
    for(auto [op, a, b] : qs) {
        if(op == 0) {
            cht.add_line(a, b);
        } else {
            int i = std::lower_bound(xs.begin(), xs.end(), a) - xs.begin();
            std::cout << cht.get_min(i) << '\n';
        }
    }
}
