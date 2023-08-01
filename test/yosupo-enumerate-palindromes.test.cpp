#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../cpp/rolling-hash.hpp"

#include <iostream>

int main(void) {
    std::string s; std::cin >> s;
    int n = s.length();
    RollingHash rh;
    auto hash1 = rh.build(s);
    auto hash2 = rh.build(s.rbegin(), s.rend());
    std::vector<int> ans(n*2-1);
    for(int i = 0; i < n; i++) {
        int ok = 0, ng = std::min(i+1, n-i);
        while(ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if(rh.query(hash1, i-mid, i+mid+1) == rh.query(hash2, s.length()-i-mid-1, s.length()-i+mid)) ok = mid;
            else ng = mid;
        }
        ans[i*2] = ok*2+1;
    }
    for(int i = 0; i < n-1; i++) {
        int ok = 0, ng = std::min(i+2, n-i);
        while(ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if(rh.query(hash1, i-mid+1, i+mid+1) == rh.query(hash2, s.length()-i-mid-1, s.length()-i+mid-1)) ok = mid;
            else ng = mid;
        }
        ans[i*2+1] = ok*2;
    }
    for(int i = 0; i < n*2-1; i++) std::cout << ans[i] << " \n"[i+1==n*2-1];
}
