#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../cpp/string.hpp"

#include <iostream>
#include <string>

int main(void) {
    std::string s; std::cin >> s;
    std::vector<int> z = z_algorithm(s);
    for(int i = 0; i < (int)z.size(); i++) {
        std::cout << z[i] << " \n"[i + 1 == (int)z.size()];
    }
}
