#pragma once

#include <vector>
#include <algorithm>

template<class T> struct Grid {
    std::vector<T> v;
    int n, m;
    constexpr Grid(std::vector<T> v) noexcept : v(v), n(v.size()) { m = (n ? (int)v[0].size() : 0); }
    constexpr Grid transpose() noexcept {
        if(n == 0) return *this;
        std::vector<T> ret(m);
        for(int i = 0; i < m; i ++) {
            ret[i].resize(n);
            for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];
        }
        return Grid(ret);
    }
    constexpr Grid rev_lr() noexcept {
        std::vector<T> ret = v;
        for(int i = 0; i < n; i ++) reverse(ret[i].begin(), ret[i].end());
        return Grid(ret);
    }
    constexpr Grid rev_ud() noexcept {
        std::vector<T> ret = v;
        reverse(ret.begin(), ret.end());
        return Grid(ret);
    }
    constexpr Grid rotate(int k) noexcept {
        k %= 4;
        if(k == 0) return *this;
        if(k < 0) k += 4;
        if(k == 2) return this->rev_lr().rev_ud();
        std::vector<T> ret(m);
        if(k == 1) {
            for(int i = 0; i < m; i ++) {
                ret[i].resize(n);
                for(int j = 0; j < n; j ++) ret[i][j] = v[n - j - 1][i];
            }
        } else {
            for(int i = 0; i < m; i ++) {
                ret[i].resize(n);
                for(int j = 0; j < n; j ++) ret[i][j] = v[j][m - i - 1];
            }
        }
        return Grid(ret);
    }
};