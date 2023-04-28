#pragma once

/**
 * @file unionfind.hpp
 * @brief UnionFind
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief 無向グラフに対して「辺の追加」、「2頂点が連結かの判定」をする
 */
struct UnionFind {
   private:
    int _n;
    // 負ならサイズ、非負なら親
    std::vector<int> parent_or_size;

   public:
    UnionFind() : _n(0) {}
    explicit UnionFind(int n) : _n(n), parent_or_size(n, -1) {}

    /**
     * @brief 辺(a,b)を足す
     * @return 連結したものの代表元
     */
    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }
    /**
     * @brief 頂点a,bが連結かどうか
     */
    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }
    /**
     * @brief 頂点aの属する連結成分の代表元
     */
    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        int x = a;
        while (parent_or_size[x] >= 0) {
            x = parent_or_size[x];
        }
        while (parent_or_size[a] >= 0) {
            int t = parent_or_size[a];
            parent_or_size[a] = x;
            a = t;
        }
        return x;
    }
    /**
     * @brief 頂点aの属する連結成分のサイズ
     */
    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }
    /**
     * @brief グラフを連結成分に分け、その情報を返す
     * @return 「一つの連結成分の頂点番号のリスト」のリスト
     */
    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }
};