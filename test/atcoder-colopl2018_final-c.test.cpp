#include "../cpp/convex.hpp"
#include <iostream>

int main() {
    using ll = long long;
    int n; std::cin >> n;
    std::vector<ll> a(n);
    for(int i = 0; i < n; i++) std::cin >> a[i];
    auto f = [&](int i, int j) {
        return a[j] + (ll)(j-i)*(j-i);
    };
    std::vector<int> minj = monotone_minima(n, n, f);
    for(int i = 0; i < n; i++) {
        std::cout << f(i, minj[i]) << std::endl;
    }
}
