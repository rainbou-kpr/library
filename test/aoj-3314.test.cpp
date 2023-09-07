#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3314"
#define ERROR 1e-6

#include "../cpp/matrix.hpp"
#include "../cpp/vector.hpp"

#include <iomanip>
#include <iostream>

int main() {
    // https://qiita.com/KowerKoint/items/e697f896c749f756235f
    double phi = (1 + std::sqrt(5)) / 2;
    std::vector<Vector<double, 3>> base = {
        {0., 1., phi},
        {phi, 0., 1.},
        {1., phi, 0.},
        {-1., phi, 0.},
        {-phi, 0., 1.},
        {0., -1., phi},
        {phi, 0., -1.},
        {0., 1., -phi},
        {-phi, 0., -1.},
        {-1., -phi, 0.},
        {1., -phi, 0.},
        {0., -1., -phi}
    };
    Vector<double, 3> base_g = (base[0] + base[1] + base[2]) / 3;
    double k = base_g.abs() * (base[1]-base[0]).abs() / (cross(base[1]-base[0], base[2]-base[0])).abs();
    Matrix<double> base_abc(3, 3);
    for(int i = 0; i < 3; i++) base_abc[i].assign(base[i].v.begin(), base[i].v.end());

    Vector<double, 3> a, b, c; std::cin >> a >> b >> c;
    auto g = (a + b + c) / 3;
    auto t = cross((b - a), (c - a)) * (-k / (b - a).abs()) + g;
    Matrix<double> trans_abc(3, 3);
    for(int j = 0; j < 3; j++) trans_abc[0][j] = a[j] - t[j];
    for(int j = 0; j < 3; j++) trans_abc[1][j] = b[j] - t[j];
    for(int j = 0; j < 3; j++) trans_abc[2][j] = c[j] - t[j];
    auto s = base_abc.inv() * trans_abc;

    std::cout << std::fixed << std::setprecision(10);
    int n; std::cin >> n;
    while(n--) {
        int v; std::cin >> v; v--;
        auto p = std::vector<double>(base[3+v].v.begin(), base[3+v].v.end()) * s;
        std::cout << Vector<double, 3>{p[0], p[1], p[2]} + t << std::endl;
    }
}
