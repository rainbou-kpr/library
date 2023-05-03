#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"

#include "../cpp/sqrt.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    std::vector<long long> v1, v2;
    long long m = sqrtll(n);
    for(long long i = 1; i <= m; i ++) {
        v1.push_back(n / i);
        v2.push_back(i);
    }
    if(v1.back() == v2.back()) v1.pop_back();

    std::cout << v1.size() + v2.size() << std::endl;
    reverse(v1.begin(), v1.end());
    for(long long e : v2) std::cout << e << " ";
    for(long long e : v1) std::cout << e << " ";
    std::cout << std::endl;

    return 0;
}


