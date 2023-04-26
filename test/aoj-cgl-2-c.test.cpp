#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"

#include <iomanip>
#include <iostream>

#include "../cpp/vector.hpp"

int main() {
    int q; std::cin >> q;
    std::cout << std::fixed << std::setprecision(10);
    while(q--) {
        Vector p0, p1, p2, p3; std::cin >> p0 >> p1 >> p2 >> p3;
        std::cout << segment_intersect(p0, p1, p2, p3).second << std::endl;
    }
}