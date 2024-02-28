#define PROBLEM "https://atcoder.jp/contests/abc185/tasks/abc185_f"

#include <iostream>

#include "../cpp/segtree.hpp"

int main(void) {
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (int& a : A) {
        std::cin >> a;
    }
    RXorQ seg(A);
    while (Q--) {
        int T, X, Y;
        std::cin >> T >> X >> Y;
        if (T == 1) {
            seg.apply(X - 1, Y);
        } else {
            int ans;
            ans = seg.prod(X - 1, Y);
            std::cout << ans << std::endl;
        }
    }
}
