#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B"

#include <iostream>

#include "../cpp/topological-sort.hpp"

int main(void){

    int N, M;
    std::cin >> N >> M;
    Graph G(N);
    G.read(M, 0, false, true);

    for(int x : topological_sort(G)) std::cout << x << std::endl;

}