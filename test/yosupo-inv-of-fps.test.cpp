#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../cpp/fps.hpp"

using mint = modint998244353;

int main() {
    long long n;
    std::cin >> n;
    FPS<mint> a(n);
    for(auto& x : a) std::cin >> x;
    auto f = inv(a);
    for(auto e : f) std::cout << e << " ";
    std::cout << std::endl;
    return 0;
}
