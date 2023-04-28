#pragma once

#include <functional>
#include <limits>
#include <ostream>
#include <vector>

template <typename S, typename ActualSegTree>
class SegTreeBase {
    int n, sz, height;
    std::vector<S> data;
    void update(int k) { data[k] = ActualSegTree::op(data[2 * k], data[2 * k + 1]); }
    
    class SegTreeReference {
        SegTreeBase& segtree;
        int k;
    public:
        SegTreeReference(SegTreeBase& segtree, int k) : segtree(segtree), k(k) {}
        SegTreeReference& operator=(const S& x) {
            segtree.set(k, x);
            return *this;
        }
        operator S() const { return segtree.get(k); }
    };
    
public:
    SegTreeBase(int n) : n(n) {
        sz = 1;
        height = 0;
        while (sz < n) {
            sz <<= 1;
            height++;
        }
        data.assign(sz * 2, ActualSegTree::e());
    }
    SegTreeBase(const std::vector<S>& v) : SegTreeBase(v.size()) {
        for (int i = 0; i < n; i++) data[sz + i] = v[i];
        for (int i = sz - 1; i > 0; i--) update(i);
    }
    
    S get(int k) const { return data[sz + k]; }
    S operator[] (int k) const { return get(k); }
    SegTreeReference operator[] (int k) { return SegTreeReference(*this, k); }

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const SegTreeBase& rhs) {
        for(int i = 0; i < rhs.n; i++) {
            if(i != 0) os << ' ';
            os << rhs[i];
        }
        return os;
    }
    
    void set(int k, const S& x) {
        k += sz;
        data[k] = x;
        for (int i = 1; i <= height; i++) update(k >> i);
    }
    void set(int k, S& x) {
        k += sz;
        data[k] = x;
        for (int i = 1; i <= height; i++) update(k >> i);
    }
    void apply(int k, const S& x) { set(k, ActualSegTree::op(get(k), x)); }
    void apply(int k, S& x) { set(k, ActualSegTree::op(get(k), x)); }
    
    S prod(int l, int r) const {
        S left_prod = ActualSegTree::e(), right_prod = ActualSegTree::e();
        l += sz;
        r += sz;
        while (l < r) {
            if (l & 1) left_prod = ActualSegTree::op(left_prod, data[l++]);
            if (r & 1) right_prod = ActualSegTree::op(data[--r], right_prod);
            l >>= 1;
            r >>= 1;
        }
        return ActualSegTree::op(left_prod, right_prod);
    }
    S all_prod() const { return data[1]; }

    template <typename F>
    int max_right(int l, F f) const {
        assert(f(ActualSegTree::e()));
        if (l == n) return n;
        l += sz;
        while (l % 2 == 0) l >>= 1;
        S sum = ActualSegTree::e();
        while(f(ActualSegTree::op(sum, data[l]))) {
            if (__builtin_clz(l) != __builtin_clz(l+1)) return n;
            sum = ActualSegTree::op(sum, data[l]);
            l++;
            while (l % 2 == 0) l >>= 1;
        }
        while (l < sz) {
            if (!f(ActualSegTree::op(sum, data[l * 2]))) l *= 2;
            else {
                sum = ActualSegTree::op(sum, data[l * 2]);
                l = l * 2 + 1;
            }
        }
        return l - sz;
    }
    template <typename F>
    int min_left(int r, F f) const {
        assert(f(ActualSegTree::e()));
        if (r == 0) return 0;
        r += sz - 1;
        while (r % 2 == 1) r >>= 1;
        S sum = ActualSegTree::e();
        while(f(ActualSegTree::op(sum, data[r]))) {
            if (__builtin_clz(r) != __builtin_clz(r-1)) return 0;
            sum = ActualSegTree::op(sum, data[r]);
            r--;
            while (r % 2 == 1) r >>= 1;
        }
        while (r < sz) {
            if (!f(ActualSegTree::op(data[r * 2 + 1], sum))) r = r * 2 + 1;
            else {
                sum = ActualSegTree::op(data[r * 2 + 1], sum);
                r *= 2;
            }
        }
        return r + 1 - sz;
    }
};

template <typename S, typename Op, S E>
class StaticSegTree : public SegTreeBase<S, StaticSegTree<S, Op, E>> {
    static Op operator_object;
public:
    static S op(const S& a, const S& b) { return operator_object(a, b); }
    static S op(S& a, S& b) { return operator_object(a, b); }
    static S e() { return E; }
    
    StaticSegTree(int n = 0) : SegTreeBase<S, StaticSegTree<S, Op, E>>(n) {}
    StaticSegTree(const std::vector<S>& v) : SegTreeBase<S, StaticSegTree<S, Op, E>>(v) {}
};

template <typename S, int ID=-1>
class SegTree : public SegTreeBase<S, SegTree<S, ID>> {
    static std::function<S(S, S)> operator_object;
    static std::function<S()> identity_object;
    
public:
    static void set_operator(const std::function<S(S, S)>& op, const std::function<S()>& id) {
        operator_object = op;
        identity_object = id;
    }
    static void set_operator(const std::function<S(S, S)>& op, const S& e) {
        operator_object = op;
        identity_object = [&e](){ return e; };
    }
    static S op(S a, S b) { return operator_object(a, b); }
    static S e() { return identity_object(); }
    
    SegTree(int n = 0) : SegTreeBase<S, SegTree<S, ID>>(n) {}
    SegTree(const std::vector<S>& v) : SegTreeBase<S, SegTree<S, ID>>(v) {}
};

namespace segtree {
    template <typename S>
    struct Max {
        const S& operator() (const S& a, const S& b) const { return std::max(a, b); }
    };
    template <typename S>
    struct Min {
        const S& operator() (const S& a, const S& b) const { return std::min(a, b); }
    };
}
template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>
using RMaxQ = StaticSegTree<S, segtree::Max<S>, std::numeric_limits<S>::min()>;
template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>
using RMinQ = StaticSegTree<S, segtree::Min<S>, std::numeric_limits<S>::max()>;
template <typename S>
using RSumQ = StaticSegTree<S, std::plus<S>, S(0)>;