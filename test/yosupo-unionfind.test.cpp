#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../cpp/unionfind.hpp"

int main() {
    int N, Q;
    std::cin >> N >> Q;
    UnionFind g(N);
    int t, u, v;
    for (int i = 0; i < Q; i++) {
        std::cin >> t >> u >> v;
        if (t == 0) {
            g.merge(u, v);
        } else {
            std::cout << g.same(u, v) << '\n';
        }
    }
    return 0;
}
