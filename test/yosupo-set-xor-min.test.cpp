#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <iostream>

#include "../cpp/binary-trie.hpp"

int main(void) {
    
    int Q;
    std::cin >> Q;
    BinaryTrie<30> A;
    while (Q--) {
        int q, x;
        std::cin >> q >> x;
        switch (q) {
        case 0:
            if (A.count(x) == 0) {
                A.insert(x);
            }
            break;
        case 1:
            A.erase(x);
            break;
        case 2:
            A.apply_xor(x);
            std::cout << A.nth_element(0) << std::endl;
            A.apply_xor(x);
            break;
        }
    }

}