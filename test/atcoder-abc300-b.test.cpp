#define PROBLEM "https://atcoder.jp/contests/abc300/tasks/abc300_b"

#include <iostream>

#include "../cpp/matrix.hpp"

int main(void) {
    int h, w; std::cin >> h >> w;
    std::vector<std::string> a(h), b(h);
    for(int i = 0; i < h; i ++) {
        std::cin >> a[i];
    }
    for(int i = 0; i < h; i ++) {
        std::cin >> b[i];
    }
    Matrix<char> A(a), B(b);
    for(int i = 0; i < h; i ++) {
        for(int j = 0; j < w; j ++) {
            if(A.shift(i, j) == B) {
                std::cout << "Yes" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "No" << std::endl;
    return 0;
}