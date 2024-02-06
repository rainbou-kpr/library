#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../cpp/fps.hpp"

using mint = modint998244353;
const int mod = 998244353;

int main() {
    long long n, t;
    std::cin >> n >> t;
    std::vector<mint> inv(t + 1, 1);
    for(int i = 2; i <= t; i ++) inv[i] = -inv[mod % i] * (mod / i);
    std::vector<int> cnt(t + 1, 0);
    for(int i = 0; i < n; i ++) {
        int x; std::cin >> x;
        cnt[x] ++;
    }
    FPS<mint> f(t + 1);
    for(int i = 1; i <= t; i ++) for(int j = 1; i * j <= t; j ++) {
        f[i * j] += mint(cnt[i]) * inv[j] * (j & 1 ? 1 : -1);
    }
    f = exp(f);
    for(int i = 1; i <= t; i ++) std::cout << f[i] << " ";
    std::cout << std::endl;
    return 0;
}
