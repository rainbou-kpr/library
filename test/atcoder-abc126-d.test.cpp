#define PROBLEM "https://atcoder.jp/contests/abc126/tasks/abc126_d"

#include "../cpp/graph_util.hpp"

int main() {
    int N;
    std::cin >> N;
    Graph<int> graph(2 * N);
    int tmp = N;
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;
        if (w % 2) {
            graph.add_edge(u, tmp);
            graph.add_edge(v, tmp);
            tmp++;
        } else {
            graph.add_edge(u, v);
        }
    }
    std::vector<int> color = bipartite_coloring(graph);
    for (int i = 0; i < N; i++) {
        std::cout << color[i] << std::endl;
    }
}