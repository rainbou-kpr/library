#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../cpp/fps.hpp"

using mint = modint998244353;

int main() {
    long long n, c;
    std::cin >> n >> c;
    FPS<mint> a(n);
    for(auto& x : a) std::cin >> x;
    auto f = taylor_shift(a, c);
    for(auto e : f) std::cout << e << " ";
    std::cout << std::endl;
    return 0;
}
