#pragma once

/**
 * @file monoid-unionfind.hpp
 * @brief 可換モノイドを乗せるUnionFind
 */

#include "unionfind.hpp"

/**
 * @brief 可換モノイドを乗せるUnionFind
 *
 * @tparam S
 * @tparam Op
 */
template <typename S, class Op>
class MonoidUnionFind : private UnionFind {
   private:
    std::vector<S> val;
    using UnionFind::_n;
    using UnionFind::parent_or_size;

   public:
    inline constexpr static auto op = Op();

    explicit MonoidUnionFind(std::vector<S> v) : UnionFind(v.size()), val(v) {}
    MonoidUnionFind(int n, S e) : UnionFind(n), val(n, e) {}
    using UnionFind::groups;
    using UnionFind::leader;
    using UnionFind::same;
    using UnionFind::size;
    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        val[x] = op(val[x], val[y]);
        return x;
    }
    const S& prod(int a) {
        return val[leader(a)];
    }
};
