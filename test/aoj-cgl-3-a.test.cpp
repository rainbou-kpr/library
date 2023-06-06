#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"

#include <iomanip>

#include "../cpp/io.hpp"
#include "../cpp/vector.hpp"

int main(void) {
    int n; std::cin >> n;
    std::vector<Vector<>> polygon(n); std::cin >> polygon;
    std::cout << std::fixed << std::setprecision(1) << polygon_area(polygon) << std::endl;
}