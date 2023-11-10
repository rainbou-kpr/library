#define PROBLEM "https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_c"

#include <array>

#include "../cpp/graph_util.hpp"

int main() {
    long long N, M;
    std::cin >> N >> M;
    Graph<int> graph(N);
    graph.read(M, -1);
    std::vector<int> color = bipartite_coloring(graph);

    if (color.empty()) {
        std::cout << N * (N - 1) / 2 - M << std::endl;
    } else {
        std::array<long long, 2> cnt = {0, 0};
        cnt[0] = count(color.begin(), color.end(), 0);
        cnt[1] = count(color.begin(), color.end(), 1);
        std::cout << cnt[0] * cnt[1] - M << std::endl;
    }
}