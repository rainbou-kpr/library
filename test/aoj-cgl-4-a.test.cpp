#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"

#include <iostream>

#include "../cpp/vector.hpp"

int main(void) {
    int n; std::cin >> n;
    std::vector<Vector<int>> points(n);
    for(int i = 0; i < n; ++i) std::cin >> points[i];
    std::vector<Vector<int>> polygon = convex_hull(points, true);
    int j = 0;
    for(int i = 0; i < (int)polygon.size(); i++) {
        if(polygon[i][1] < polygon[j][1]) j = i;
        if(polygon[i][1] == polygon[j][1] && polygon[i][0] < polygon[j][0]) j = i;        
    }
    std::rotate(polygon.begin(), polygon.begin() + j, polygon.end());
    std::cout << polygon.size() << '\n';
    for(auto& p : polygon) std::cout << p << '\n';
}