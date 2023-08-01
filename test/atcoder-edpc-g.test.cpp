#define PROBLEM "https://atcoder.jp/contests/dp/tasks/dp_g"

#include <iostream>
#include <algorithm>

#include "../cpp/graph.hpp"

int main(void){

    int N, M;
    std::cin >> N >> M;
    Graph G(N);
    G.read(M, -1, false, true);

    std::vector<int> dist(N);
    for(int x : G.topological_sort()){
        for(int y : G[x]) dist[y] = std::max(dist[y], dist[x] + 1);
    }
    std::cout << *std::max_element(dist.begin(), dist.end()) << std::endl;

}
