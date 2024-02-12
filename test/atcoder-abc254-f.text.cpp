#define PROBLEM "https://atcoder.jp/contests/abc254/tasks/abc254_f"

#include <iostream>

#include "../cpp/segtree.hpp"

int main(void) {
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N), B(N), dA, dB;
    for (size_t i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    for (size_t i = 0; i < N; i++) {
        std::cin >> B[i];
    }
    dA.reserve(N - 1);
    dB.reserve(N - 1);
    for (size_t i = 0; i < N - 1; i++) {
        dA.push_back(A[i + 1] - A[i]);
        dB.push_back(B[i + 1] - B[i]);
    }
    RGcdQ<int> seg1(dA), seg2(dB);
    while (Q--) {
        int h1, h2, w1, w2;
        std::cin >> h1 >> h2 >> w1 >> w2;
        int g = A[h1 - 1] + B[w1 - 1];
        g = std::gcd(g, seg1.prod(h1 - 1, h2 - 1));
        g = std::gcd(g, seg2.prod(w1 - 1, w2 - 1));
        std::cout << g << std::endl;
    }
}