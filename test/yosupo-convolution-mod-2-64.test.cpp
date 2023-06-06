#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include "../cpp/io.hpp"
#include "../cpp/convolution.hpp"

int main(void) {
    int n, m; std::cin >> n >> m;
    std::vector<long long> a0(n), a1(n), a2(n), b0(m), b1(m), b2(m);
    for(int i = 0; i < n; i++) {
        unsigned long long a; std::cin >> a;
        a0[i] = a & ((1ULL << 31) - 1);
        a1[i] = a >> 31 & ((1ULL << 31) - 1);
        a2[i] = a >> 62;
    }
    for(int i = 0; i < m; i++) {
        unsigned long long b; std::cin >> b;
        b0[i] = b & ((1ULL << 31) - 1);
        b1[i] = b >> 31 & ((1ULL << 31) - 1);
        b2[i] = b >> 62;
    }
    std::vector<unsigned long long> c(n+m-1);
    std::vector<long long> c00 = convolution_ll(a0, b0);
    for(int i = 0; i < n+m-1; i++) {
        c[i] += (unsigned long long)c00[i];
    }
    std::vector<long long> c01 = convolution_ll(a0, b1);
    for(int i = 0; i < n+m-1; i++) {
        c[i] += (unsigned long long)c01[i] << 31;
    }
    std::vector<long long> c02 = convolution_ll(a0, b2);
    for(int i = 0; i < n+m-1; i++) {
        c[i] += (unsigned long long)c02[i] << 62;
    }
    std::vector<long long> c10 = convolution_ll(a1, b0);
    for(int i = 0; i < n+m-1; i++) {
        c[i] += (unsigned long long)c10[i] << 31;
    }
    std::vector<long long> c11 = convolution_ll(a1, b1);
    for(int i = 0; i < n+m-1; i++) {
        c[i] += (unsigned long long)c11[i] << 62;
    }
    std::vector<long long> c20 = convolution_ll(a2, b0);
    for(int i = 0; i < n+m-1; i++) {
        c[i] += (unsigned long long)c20[i] << 62;
    }
    std::cout << c << std::endl;
}
