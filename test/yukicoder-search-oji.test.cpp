#define PROBLEM "https://yukicoder.me/problems/no/1340"

#include "../cpp/matrix.hpp"
#include "../cpp/modint.hpp"
#include <iostream>

using mint3 = static_modint<57>;

int main() {
    long long n, m, t;
    std::cin >> n >> m >> t;
    
    Matrix<modint1000000007> mat1(n, n, 0);
    Matrix<modint998244353> mat2(n, n, 0);
    Matrix<mint3> mat3(n, n, 0);

    for(int i = 0; i < m; i ++) {
        int a, b;
        std::cin >> a >> b;
        mat1[b][a] = 1;
        mat2[b][a] = 1;
        mat3[b][a] = 1;
    }
    
    std::vector<modint1000000007> v1(n, 0);
    std::vector<modint998244353> v2(n, 0);
    std::vector<mint3> v3(n, 0);
    v1[0] = 1;
    v2[0] = 1;
    v3[0] = 1;

    v1 = mat1.pow(t) * v1;
    v2 = mat2.pow(t) * v2;
    v3 = mat3.pow(t) * v3;

    int ans = 0;
    for(int i = 0; i < n; i ++) {
        if(v1[i].value() || v2[i].value() || v3[i].value()) ans ++;
    }
    std::cout << ans << std::endl;

    return 0;
}

