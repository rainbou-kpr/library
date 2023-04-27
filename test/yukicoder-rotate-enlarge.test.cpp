#define PROBLEM "https://yukicoder.me/problems/no/565"

#include "../cpp/transpose.hpp"
#include <iostream>
#include <string>
#include <algorithm>

std::string extend(std::string s, int k) {
    std::string ret = "";
    for(char c : s) ret += std::string(k, c);
    return ret;
}

int main() {
    int r, k, h, w;
    std::cin >> r >> k >> h >> w;
    std::vector<std::string> c(h);
    for(int i = 0; i < h; i ++) std::cin >> c[i];

    for(int i = 0; i < r; i += 90) {
        c = transpose(c);
        for(auto& s : c) std::reverse(s.begin(), s.end());
    }
    for(auto s : c) {
        std::string t = extend(s, k);
        for(int i = 0; i < k; i ++) std::cout << t << std::endl;
    }
    return 0;
}

