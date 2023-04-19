#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../cpp/graph.hpp"

int main() {
    int n, m, s, t; std::cin >> n >> m >> s >> t;
    Graph<long long> g(n); g.read(m, 0, true, true);
    auto [dist, prev] = g.shortest_path(s);
    if(dist[t] == std::numeric_limits<long long>::max()) {
        std::cout << -1 << '\n';
        return 0;
    }
    std::vector<std::pair<int, int>> route;
    int cur = t;
    while(cur != s) {
        route.emplace_back(prev[cur].from, prev[cur].to);
        cur = prev[cur].from;
    }
    std::cout << dist[t] << ' ' << route.size() << '\n';
    for(auto it = route.rbegin(); it != route.rend(); it++) {
        std::cout << it->first << ' ' << it->second << '\n';
    }
}

