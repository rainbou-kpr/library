#define PROBLEM "https://yukicoder.me/problems/no/705"
#include "../cpp/convex.hpp"
#include <iostream>

int main() {
    using ll = long long;
    int n; std::cin >> n;
    std::vector<ll> a(n), x(n), y(n);
    for(int i = 0; i < n; i++) std::cin >> a[i];
    for(int i = 0; i < n; i++) std::cin >> x[i];
    for(int i = 0; i < n; i++) std::cin >> y[i];
    auto f = [&](int i, int j) {
        ll dx = std::abs(x[i] - a[j-1]);
        ll dy = std::abs(y[i]);
        return dx*dx*dx + dy*dy*dy;
    };
    std::cout << online_offline_dp(n, f)[n] << std::endl;
}
