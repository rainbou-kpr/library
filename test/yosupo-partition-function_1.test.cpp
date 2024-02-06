#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../cpp/fps.hpp"

using mint = modint998244353;

int main() {
    long long n;
    std::cin >> n;
    FPS<mint> f(n + 1, 0);
    for(int i = 1; i <= n; i ++) {
        mint inv = mint(i).inv();
        for(int j = i; j <= n; j += i) f[j] += inv;
    }
    f = exp(f);
    for(auto x : f) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
