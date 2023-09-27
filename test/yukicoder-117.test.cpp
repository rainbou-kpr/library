#define PROBLEM "https://yukicoder.me/problems/no/117"

#include "../cpp/combinatorics.hpp"
#include "../cpp/modint.hpp"

#include <iostream>

int main() {
    int t; std::cin >> t;
    using C = Combination<modint1000000007>;
    while(t--) {
        std::string s; std::cin >> s;
        s.pop_back();
        int i = 2;
        while(isdigit(s[i])) ++i;
        int n = std::stoi(s.substr(2, i - 2));
        int m = std::stoi(s.substr(i+1));
        if(s[0] == 'C') {
            std::cout << C::C(n, m) << std::endl;
        } else if(s[0] == 'P') {
            std::cout << C::P(n, m) << std::endl;
        } else {
            std::cout << C::H(n, m) << std::endl;
        }
    }
}
