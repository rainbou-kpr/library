#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include "../cpp/combinatorics.hpp"
#include "../cpp/number-theory.hpp"

#include <iostream>

int main() {
    int t, m; std::cin >> t >> m;
    std::vector<std::pair<int, int>> factors;
    {
        int mm = m;
        for(int i = 2; i * i <= mm; ++i) {
            if(mm % i == 0) {
                int cnt = 0;
                while(mm % i == 0) {
                    mm /= i;
                    cnt++;
                }
                factors.emplace_back(i, cnt);
            }
        }
        if(mm > 1) factors.emplace_back(mm, 1);
    }
    std::vector<CombinationPQ> combpq;
    for(int i = 0; i < factors.size(); ++i) {
        auto [p, e] = factors[i];
        combpq.emplace_back(p, e);
    }
    while(t--) {
        long long n, k; std::cin >> n >> k;
        std::vector<long long> x, y;
        for(int i = 0; i < factors.size(); ++i) {
            auto [p, e] = factors[i];
            x.push_back(combpq[i].C(n, k));
            y.push_back(combpq[i].pq);
        }
        std::cout << crt(x, y).first << std::endl;
    }
}
