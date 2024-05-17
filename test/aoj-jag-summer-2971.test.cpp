#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2971"

#include <array>
#include <iostream>

#include "../cpp/modint.hpp"
#include "../cpp/potentialized-unionfind.hpp"

template <typename mint>
bool solve(int n, const std::vector<std::array<int, 3>>& abx) {
    UnionFindMul<mint> uf(n);
    for (auto [a, b, x] : abx) {
        mint mx = x;
        if (mx != 0) {
            if (uf.same(a, b)) {
                if (uf.diff(a, b) != mx) {
                    return false;
                }
            } else {
                uf.merge(a, b, mx);
            }
        }
    }
    return true;
}

int main() {
    using mint3 = modint998244353;
    using mint7 = modint1000000007;
    using mint9 = static_modint<1000000009U>;
    int n, m;
    std::cin >> n >> m;
    std::vector<std::array<int, 3>> abx(m);
    for (auto& [a, b, x] : abx) {
        std::cin >> a >> b >> x;
        a--;
        b--;
    }
    if (solve<mint3>(n, abx) && solve<mint7>(n, abx) && solve<mint9>(n, abx)) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
}
