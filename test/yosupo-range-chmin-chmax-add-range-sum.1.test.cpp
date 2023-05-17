#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include <iostream>
#include <ostream>

#include "../cpp/segtree-beats.hpp"

long long inf = 2e18;

int main(void) {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    struct S {
        // 1番目、1番目の要素数、2番目、合計
        long long max1, max1_num, max2, min1, min1_num, min2, sum;
        S(long long x = 0) : max1(x), max1_num(1), max2(-inf), min1(x), min1_num(1), min2(inf), sum(x) {}
    };
    struct Op {
        S operator() (const S& l, const S& r) {
            S res;
            res.max1 = std::max(l.max1, r.max1);
            if(l.max1 == r.max1) {
                res.max1_num = l.max1_num + r.max1_num;
                res.max2 = std::max(l.max2, r.max2);
            } else if(l.max1 > r.max1) {
                res.max1_num = l.max1_num;
                res.max2 = std::max(l.max2, r.max1);
            } else {
                res.max1_num = r.max1_num;
                res.max2 = std::max(l.max1, r.max2);
            }
            res.min1 = std::min(l.min1, r.min1);
            if(l.min1 == r.min1) {
                res.min1_num = l.min1_num + r.min1_num;
                res.min2 = std::min(l.min2, r.min2);
            } else if(l.min1 < r.min1) {
                res.min1_num = l.min1_num;
                res.min2 = std::min(l.min2, r.min1);
            } else {
                res.min1_num = r.min1_num;
                res.min2 = std::min(l.min1, r.min2);
            }
            res.sum = l.sum + r.sum;
            return res;
        }
    };
    struct E {
        S operator() () {
            S res;
            res.max1 = -inf;
            res.max1_num = 0;
            res.max2 = -inf;
            res.min1 = inf;
            res.min1_num = 0;
            res.min2 = inf;
            res.sum = 0;
            return res;
        }
    };
    struct F {
        // clamp(x + add, lb, ub)
        long long lb, ub, add;
    };
    struct Mapping {
        std::pair<bool, S> operator() (const F& f, const S& x, int sz) {
            S res = x;
            res.max1 += f.add;
            res.max2 += f.add;
            res.min1 += f.add;
            res.min2 += f.add;
            res.sum += f.add * sz;
            if(res.max1 == res.min1) {
                long long x = std::clamp(res.max1, f.lb, f.ub);
                res.max1 = x;
                res.max2 = -inf;
                res.min1 = x;
                res.min2 = inf;
                res.sum = x * sz;
                return {false, res};
            }
            if(res.max1 == res.min2) {
                long long xr = std::clamp(res.max1, f.lb, f.ub);
                long long xl = std::clamp(res.min1, f.lb, f.ub);
                if(xr == xl) {
                    res.max1 = xr;
                    res.max1_num = sz;
                    res.max2 = -inf;
                    res.min1 = xr;
                    res.min1_num = sz;
                    res.min2 = inf;
                    res.sum = xr * sz;
                    return {false, res};
                }
                res.max1 = xr;
                res.max2 = xl;
                res.min1 = xl;
                res.min2 = xr;
                res.sum = xr * res.max1_num + xl * res.min1_num;
                return {false, res};
            }
            if(f.ub <= res.max2) return {true, res};
            if(f.lb >= res.min2) return {true, res};
            if(f.ub < res.max1) {
                res.sum -= (res.max1 - f.ub) * res.max1_num;
                res.max1 = f.ub;
            }
            if(f.lb > res.min1) {
                res.sum += (f.lb - res.min1) * res.min1_num;
                res.min1 = f.lb;
            }
            return {false, res};
        }
    };
    struct Composition {
        F operator() (const F& f, const F& g) {
            F res;
            res.lb = std::clamp(g.lb + f.add, f.lb, f.ub);
            res.ub = std::clamp(g.ub + f.add, f.lb, f.ub);
            res.add = f.add + g.add;
            return res;
        }
    };
    struct Id {
        F operator() () {
            F res;
            res.lb = -inf;
            res.ub = inf;
            res.add = 0;
            return res;
        }
    };
    int n, q; std::cin >> n >> q;
    std::vector<S> v(n);
    for(int i = 0; i < n; i++) {
        long long a; std::cin >> a;
        v[i] = S(a);
    }
    StaticSegTreeBeats<S, Op, E, F, Mapping, Composition, Id> seg(v);
    while(q--) {
        int op; std::cin >> op;
        if(op == 0) {
            int l, r; long long b; std::cin >> l >> r >> b;
            seg.apply(l, r, F{-inf, b, 0});
        } else if(op == 1) {
            int l, r; long long b; std::cin >> l >> r >> b;
            seg.apply(l, r, F{b, inf, 0});
        } else if(op == 2) {
            int l, r; long long b; std::cin >> l >> r >> b;
            seg.apply(l, r, F{-inf, inf, b});
        } else {
            int l, r; std::cin >> l >> r;
            std::cout << seg.prod(l, r).sum << std::endl;
        }
    }
}