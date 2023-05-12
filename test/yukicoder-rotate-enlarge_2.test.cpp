#define PROBLEM "https://yukicoder.me/problems/no/565"

#include "../cpp/matrix.hpp"
#include <iostream>
#include <string>

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

    for(auto s : Matrix(c).rotate(r / 90).vstr()) {
        std::string t = extend(s, k);
        for(int i = 0; i < k; i ++) std::cout << t << std::endl;
    }
    return 0;
}

