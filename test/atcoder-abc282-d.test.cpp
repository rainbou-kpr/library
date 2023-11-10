#define PROBLEM "https://atcoder.jp/contests/abc282/tasks/abc282_d"

#include <array>

#include "../cpp/graph_util.hpp"

int main(void) {
    int N, M;
    std::cin >> N >> M;
    Graph<int> graph(N);
    graph.read(M);
    std::vector<int> c = bipartite_coloring(graph);
    if (c.empty()) {
        std::cout << 0 << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> groups = connected_components(graph);
    long long ans = (long long)N * (N - 1) / 2 - M;
    for (const std::vector<int>& group : groups) {
        std::array<long long, 2> wb = {};
        std::for_each(group.begin(), group.end(), [&](int x) { wb[c[x]]++; });
        auto [w, b] = wb;
        ans -= w * (w - 1) / 2 + b * (b - 1) / 2;
    }
    std::cout << ans << std::endl;
}