#define PROBLEM "https://atcoder.jp/contests/abc331/tasks/abc331_f"

#include <iostream>

#include "../cpp/rolling-hash.hpp"
#include "../cpp/segtree.hpp"

RollingHash rh;
struct E {
    RHString operator()() const { return RHString(rh); }
};

int main() {
    int N, Q;
    std::string S;
    std::cin >> N >> Q >> S;
    std::vector<RHString> init;
    for (char c : S) {
        init.emplace_back(rh, std::string{c});
    }
    StaticSegTree<RHString, std::plus<RHString>, E> seg(init);
    while (Q--) {
        int q;
        std::cin >> q;
        if (q == 1) {
            int x;
            char c;
            std::cin >> x >> c;
            seg.set(x - 1, RHString(rh, std::string{c}));
        } else {
            int L, R;
            std::cin >> L >> R;
            std::cout << (seg.prod(L - 1, R).is_palindrome() ? "Yes" : "No") << std::endl;
        }
    }
}