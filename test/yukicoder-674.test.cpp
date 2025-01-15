#define PROBLEM "https://yukicoder.me/problems/no/674"

#include "../cpp/monoid-unionfind.hpp"
#include "../cpp/more_functional.hpp"

#include <iostream>
#include <set>

using ll = long long;

int main() {
    ll D, Q;
    std::cin >> D >> Q;
    std::vector<std::pair<ll, ll>> AB(Q);
    std::set<ll> s;
    for (auto& [A, B] : AB) {
        std::cin >> A >> B;
        s.insert(A);
        s.insert(A - 1);
        s.insert(B);
        s.insert(B + 1);
    }
    std::vector<ll> v(s.begin(), s.end());
    std::vector<bool> f(s.size());
    std::vector<std::pair<int, int>> init;
    for (std::size_t i = 0; i < v.size(); i++) {
        init.push_back({i, i});
    }
    MonoidUnionFind<std::pair<int, int>, more_functional::MinMax<int>> uf(init);
    ll ans = 0;
    for (auto [A, B] : AB) {
        int k = std::lower_bound(v.begin(), v.end(), A) - v.begin();
        std::pair<int, int> p = uf.prod(k);
        while (v[p.second + 1] <= B) {
            uf.merge(k, p.second + 1);
            k = p.second + 1;
            p = uf.prod(k);
        }
        if (f[p.first - 1]) {
            uf.merge(p.first - 1, p.first);
        }
        if (f[p.second + 1]) {
            uf.merge(p.second, p.second + 1);
        }
        f[p.first] = true;
        f[p.second] = true;
        p = uf.prod(k);
        if (ans < v[p.second] - v[p.first] + 1) {
            ans = v[p.second] - v[p.first] + 1;
        }
        std::cout << ans << std::endl;
    }
}
