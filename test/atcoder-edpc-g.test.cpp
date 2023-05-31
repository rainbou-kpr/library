#define PROBLEM "https://atcoder.jp/contests/dp/tasks/dp_g"

#include <iostream>
#include <algorithm>

#include "../cpp/topological-sort.hpp"

int main(void){

    int N, M;
    std::cin >> N >> M;
    Graph G(N);
    G.read(M, -1, false, true);

    std::vector<int> dist(N), ord(topological_sort(G));
    for(int x : ord){
        for(int y : G[x]) dist[y] = std::max(dist[y], dist[x] + 1);
    }
    std::cout << *std::max_element(dist.begin(), dist.end()) << std::endl;

}
