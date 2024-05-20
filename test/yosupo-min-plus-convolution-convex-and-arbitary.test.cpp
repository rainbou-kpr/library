#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"
#include "../cpp/convex.hpp"
#include <iostream>

int main() {
    int n, m; std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    for(int i = 0; i < n; i++) std::cin >> a[i];
    for(int i = 0; i < m; i++) std::cin >> b[i];
    std::vector<int> c = min_plus_convolution_convex_arbitary(a, b);
    for(int i = 0; i < n+m-1; i++) {
        std::cout << c[i] << (i==n+m-2 ? '\n' : ' ');
    }
}
