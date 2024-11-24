#define PROBLEM "https://atcoder.jp/contests/abc228/tasks/abc228_b"

#include <iostream>

#include "../cpp/functional-graph.hpp"

int main(void) {
    int N, X;
    std::cin >> N >> X;
    FunctionalGraph fg(N);
    fg.read();
    std::cout << fg.hopable(X - 1) << std::endl;
}
