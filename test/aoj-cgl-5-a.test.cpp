#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A"
#define ERROR "1e-6"

#include <iomanip>
#include <iostream>

#include "../cpp/vector.hpp"

int main(void) {
    int n; std::cin >> n;
    std::vector<Vector<double>> points(n);
    for(int i = 0; i < n; i++) std::cin >> points[i];
    std::cout << std::fixed << std::setprecision(7) << std::get<0>(closest_point_pair(points)) << std::endl;
}