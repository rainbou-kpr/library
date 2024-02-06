#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../cpp/fps.hpp"

using mint = modint998244353;

int main() {
    long long n;
    std::cin >> n;
    FPS<mint> f(n + 1, 0);
    for(int i = 0;; i ++) {
        if(i * (3 * i - 1) > n * 2) break;
        f[i * (3 * i - 1) / 2] = (i % 2 ? -1 : 1);
    }
    for(int i = -1;; i --) {
        if(i * (3 * i - 1) > n * 2) break;
        f[i * (3 * i - 1) / 2] = (i % 2 ? -1 : 1);
    }
    f = inv(f);
    for(auto x : f) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
