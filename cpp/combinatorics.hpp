#pragma once

#include <vector>
#include "modint.hpp"

/**
 * @brief 組み合わせ
 */
template <typename Modint>
class Combination {
    static std::vector<Modint> fact, inv_fact;

public:
    /**
     * @brief n までの階乗とその逆元を前計算する
     * @param n
     * @note O(n) 必要になったら呼び出されるが、予め大きなnに対して呼び出しておくことで逆元の直接計算を減らせる
     */
    inline static void extend(int n) {
        int m = fact.size();
        if (n < m) return;
        fact.resize(n + 1);
        inv_fact.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            fact[i] = fact[i - 1] * i;
        }
        inv_fact[n] = fact[n].inv();
        for (int i = n; i > m; --i) {
            inv_fact[i - 1] = inv_fact[i] * i;
        }
    }
    
    /**
     * @brief n の階乗を返す
     * @param n
     * @return n!
     * @note extend(n), O(1)
     */
    inline static Modint factorial(int n) {
        extend(n);
        return fact[n];
    }
    /**
     * @brief n の階乗の逆元を返す
     * @param n
     * @return n!^-1
     * @note extend(n), O(1)
     */
    inline static Modint inverse_factorial(int n) {
        extend(n);
        return inv_fact[n];
    }
    /**
     * @brief n の逆元を返す
     * @param n
     * @return n^-1
     * @note extend(n), O(1)
     */
    inline static Modint inverse(int n) {
        extend(n);
        return inv_fact[n] * fact[n - 1];
    }

    /**
     * @brief nPr を返す
     * @param n
     * @param r
     * @return nPr
     * @note extend(n), O(1)
     */
    inline static Modint P(int n, int r) {
        if (r < 0 || n < r) return 0;
        extend(n);
        return fact[n] * inv_fact[n - r];
    }
    /**
     * @brief nCr を返す
     * @param n
     * @param r
     * @return nCr
     * @note extend(n), O(1)
     */
    inline static Modint C(int n, int r) {
        if (r < 0 || n < r) return 0;
        extend(n);
        return fact[n] * inv_fact[r] * inv_fact[n - r];
    }
    /**
     * @brief nHr を返す
     * @param n
     * @param r
     * @return nHr
     * @note extend(n+r-1), O(1)
     */
    inline static Modint H(int n, int r) {
        if (n < 0 || r < 0) return 0;
        if (n == 0 && r == 0) return 1;
        return C(n + r - 1, r);
    }

    /**
     * @brief nPr を定義どおり計算する
     * @param n
     * @param r
     * @return nPr
     * @note O(r)
     */
    inline static Modint P_loop(long long n, int r) {
        if (r < 0 || n < r) return 0;
        Modint res = 1;
        for (int i = 0; i < r; ++i) {
            res *= n - i;
        }
        return res;
    }
    /**
     * @brief nCr を定義どおり計算する
     * @param n
     * @param r
     * @return nCr
     * @note O(min(r, n-r))
     */
    inline static Modint C_loop(long long n, long long r) {
        if (r < 0 || n < r) return 0;
        if(r > n - r) r = n - r;
        extend(r);
        return P_loop(n, r) * inv_fact[r];
    }
    /**
     * @brief nHr を定義どおり計算する
     * @param n
     * @param r
     * @return nHr
     * @note O(r)
     */
    inline static Modint H_loop(long long n, long long r) {
        if (n < 0 || r < 0) return 0;
        if (n == 0 && r == 0) return 1;
        return C_loop(n + r - 1, r);
    }

    /**
     * @brief nCr を Lucas の定理を用いて計算する
     * @param n
     * @param r
     * @return nCr
     * @note expand(Mod), O(log(r))
     */
    inline static Modint C_lucas(long long n, long long r) {
        if (r < 0 || n < r) return 0;
        if (r == 0 || n == r) return 1;
        Modint res = 1;
        while(r > 0) {
            int ni = n % Modint::mod(), ri = r % Modint::mod();
            if (ni < ri) return 0;
            res *= C(ni, ri);
            n /= Modint::mod();
            r /= Modint::mod();
        }
        return res;
    }
};

template <typename Modint>
std::vector<Modint> Combination<Modint>::fact{1, 1};
template <typename Modint>
std::vector<Modint> Combination<Modint>::inv_fact{1, 1};
