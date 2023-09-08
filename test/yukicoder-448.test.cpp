#define PROBLEM "https://yukicoder.me/problems/no/448"

#include "../cpp/number-theory.hpp"

#include <algorithm>
#include <iostream>

int main() {
    int n; std::cin >> n;
    std::vector<long long> x(n), y(n);
    for (int i = 0; i < n; ++i) std::cin >> x[i] >> y[i];
    long long res = garner(x, y, 1000000007);
    if(res == -1) std::cout << -1 << std::endl;
    else if(std::all_of(x.begin(), x.end(), [](auto x) { return x == 0; })) {
        modint1000000007 ans = 1;
        for (int i = 0; i < n; ++i) ans *= y[i];
        std::cout << ans << std::endl;
    } else {
        std::cout << res << std::endl;
    }
}
