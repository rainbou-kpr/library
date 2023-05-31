#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../cpp/number-theory.hpp"

using mint = modint998244353;

int main() {
    long long n, m, x;
    std::cin >> n >> m;
    std::vector<mint> a(n), b(m);
    for(int i = 0; i < n; ++ i) {
        std::cin >> x;
        a[i] = mint(x);
    }
    for(int i = 0; i < m; ++ i) {
        std::cin >> x;
        b[i] = mint(x);
    }
    auto c = convolution(a, b);
    for(auto e : c) std::cout << e.value() << " ";
    std::cout << std::endl;

    return 0;

}


