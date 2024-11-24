#define PROBLEM "https://atcoder.jp/contests/abc367/tasks/abc367_e"

#include <iostream>

#include "../cpp/functional-graph.hpp"

int main(void) {
    int N;
    long long K;
    std::cin >> N >> K;
    FunctionalGraph fg(N);
    fg.read();
    std::vector<int> A(N);
    for (int& a : A) std::cin >> a;
    for (int i = 0; i < N; i++) {
        std::cout << A[fg.hop(i, K)];
        if (i == N - 1) {
            std::cout << std::endl;
        } else {
            std::cout << ' ';
        }
    }
}
