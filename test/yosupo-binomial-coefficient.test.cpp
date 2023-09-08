#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"
#define IGNORE

#include "../cpp/modint.hpp"
#include "../cpp/combinatorics.hpp"
#include "../cpp/number-theory.hpp"

#include <iostream>

int main() {
    int t, m; std::cin >> t >> m;
    modint::set_mod(m);
    using Comb = Combination<modint>;
    while(t--) {
        long long n, k; std::cin >> n >> k;
        // TODO
        std::cout << Comb::C_lucas(n, k) << '\n';
    }
}
