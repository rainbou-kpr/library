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
    Matrix<char> mat(c);
    for(int i = 0; i < r; i += 90) mat = mat.transpose().rev_lr();
    for(auto s : mat.vstr()) {
        std::string t = extend(s, k);
        for(int i = 0; i < k; i ++) std::cout << t << std::endl;
    }
    return 0;
}

