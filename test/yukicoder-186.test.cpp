#define PROBLEM "https://yukicoder.me/problems/no/186"

#include "../cpp/number-theory.hpp"

int main() {
    std::vector<long long> x(3), y(3);
    for (int i = 0; i < 3; ++i) std::cin >> x[i] >> y[i];
    auto [ans, l] = crt(x, y);
    if(l == 0) std::cout << -1 << '\n';
    else if(ans == 0) std::cout << l << '\n';
    else std::cout << ans << '\n';
}

