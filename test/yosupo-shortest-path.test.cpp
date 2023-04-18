#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../cpp/graph.hpp"

int main() {
    int n, m, s, t; std::cin >> n >> m >> s >> t;
    Graph<long long> g(n); g.read(m, 0);
    auto [dist, prev] = g.shortest_path(s);
    std::vector<std::pair<int, int>> route;
    while(t != s) {
        route.emplace_back(prev[t].from, prev[t].to);
        t = prev[t];
    }
    for(auto it = route.rbegin(); it != route.rend(); it++) {
        std::cout << it->first << ' ' << it->second << '\n';
    }
}

