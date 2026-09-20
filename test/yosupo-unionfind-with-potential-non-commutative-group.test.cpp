#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential_non_commutative_group"

#include <iostream>

#include "../cpp/modint.hpp"
#include "../cpp/potentialized-unionfind.hpp"

using mint = modint998244353;
struct Matrix_2x2 {
    mint a, b, c, d;
};

bool operator==(const Matrix_2x2& t1, const Matrix_2x2& t2) {
    return t1.a == t2.a && t1.b == t2.b && t1.c == t2.c && t1.d == t2.d;
}

struct Op {
    Matrix_2x2 operator()(const Matrix_2x2& f, const Matrix_2x2& g) const {
        return {f.a * g.a + f.b * g.c,
                f.a * g.b + f.b * g.d,
                f.c * g.a + f.d * g.c,
                f.c * g.b + f.d * g.d};
    }
};
struct E {
    Matrix_2x2 operator()() const {
        return {1, 0, 0, 1};
    }
};
struct Inv {
    Matrix_2x2 operator()(const Matrix_2x2& f) const {
        mint detinv = (f.a * f.d - f.b * f.c).inv();
        return {f.d * detinv, -f.b * detinv, -f.c * detinv, f.a * detinv};
    }
};

template <typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix_2x2& m) {
    is >> m.a >> m.b >> m.c >> m.d;
    return is;
}
template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix_2x2& m) {
    os << m.a << CharT(' ') << m.b << CharT(' ') << m.c << CharT(' ') << m.d;
    return os;
}

int main() {
    int N, Q;
    std::cin >> N >> Q;
    PotentializedUnionFind<Matrix_2x2, Op, E, Inv> uf(N);
    while (Q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int u, v, x00, x01, x10, x11;
            std::cin >> u >> v >> x00 >> x01 >> x10 >> x11;
            Matrix_2x2 m{x00, x01, x10, x11};
            if (uf.same(u, v)) {
                if (uf.diff(v, u) == m) {
                    std::cout << 1 << std::endl;
                } else {
                    std::cout << 0 << std::endl;
                }
            } else {
                uf.merge(v, u, m);
                std::cout << 1 << std::endl;
            }
        } else {
            int u, v;
            std::cin >> u >> v;
            if (uf.same(u, v)) {
                std::cout << uf.diff(v, u) << std::endl;
            } else {
                std::cout << -1 << std::endl;
            }
        }
    }
}
