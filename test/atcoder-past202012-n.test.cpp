#define PROBLEM "https://atcoder.jp/contests/past202012-open/tasks/past202012_n"

#include "../cpp/segtree.hpp"
#include <iostream>

int main() {
    int n, q; std::cin >> n >> q;
    std::vector<std::pair<int, int>> lr(n-1);
    for(int i = 0; i < n-1; i++) {
        int l, r; std::cin >> l >> r;
        lr[i] = {l, r};
    }
    SegTree seg(lr, [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return std::pair<int, int>(std::max(a.first, b.first), std::min(a.second, b.second));
            }, std::pair<int,int>(0, 1e9));
    while(q--) {
        int a, b; std::cin >> a >> b; b--;
        int r = seg.max_right(b, [&](const std::pair<int, int>& x) { return x.first <= a && a <= x.second; });
        int l = seg.min_left(b, [&](const std::pair<int, int>& x) { return x.first <= a && a <= x.second; });
        std::cout << r - l + 1 << std::endl;
    }
}
