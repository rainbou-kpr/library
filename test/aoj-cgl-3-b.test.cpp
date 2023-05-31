#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"

#include "../cpp/io.hpp"
#include "../cpp/vector.hpp"

int main(void) {
    int n; std::cin >> n;
    std::vector<Vector<>> polygon(n); std::cin >> polygon;
    std::cout << polygon_is_convex(polygon) << std::endl;
}