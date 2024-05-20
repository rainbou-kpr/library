#define PROBLEM "https://atcoder.jp/contests/abc177/tasks/abc177_f"

#include <iostream>

#include "../cpp/lazy-segtree.hpp"

int main(void) {
    int h, w; std::cin >> h >> w;
    struct Mapping {
        int operator() (int f, int x, int l, int r) {
            int id = more_functional::MaxLimit<int>{}();
            return f == id ? x : f + l;
        }
    };
    struct Composition {
        int operator() (int f, int g) {
            int id = more_functional::MaxLimit<int>{}();
            return f == id ? g : f;
        }
    };
    StaticLazySegTree<int, more_functional::Min<int>, more_functional::MaxLimit<int>, int, Mapping, Composition, more_functional::MaxLimit<int>> seg(std::vector<int>(w, 0));
    for(int i = 0; i < h; i++) {
        int a, b; std::cin >> a >> b; a--;
        if(a == 0) {
            // unreachable to [a,b)
            seg.apply(a, b, 1000000000);
        } else {
            seg.apply(a, b, seg[a-1] + 1 - a);
        }
        int ans = seg.all_prod();
        std::cout << (ans >= 1000000000 ? -1 : ans+i+1) << '\n';
    }
}
