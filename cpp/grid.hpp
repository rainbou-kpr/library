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
    constexpr int safe_mod(int x, int mod) noexcept {
        x %= mod;
        if (x < 0) x += mod;
        return x;
    }
    constexpr Grid shift(int dy, int dx) noexcept {
        std::vector<T> ret = v;
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                ret[safe_mod(i + dy, n)][safe_mod(j + dx, m)] = v[i][j];
            }
        }
        return Grid(ret);
    }
    constexpr Grid shift_l(int k) noexcept {
        return this->shift(0, -k);
    }
    constexpr Grid shift_r(int k) noexcept {
        return this->shift(0, k);
    }
    constexpr Grid shift_u(int k) noexcept {
        return this->shift(-k, 0);
    }
    constexpr Grid shift_d(int k) noexcept {
        return this->shift(k, 0);
    }
};