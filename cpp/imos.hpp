#pragma once

/**
 * @file imos.hpp
 * @brief imos法で区間作用、1点取得
 */

#include <cassert>
#include <functional>
#include <vector>
#include "more_functional.hpp"

/**
 * @brief imos法で区間作用、1点取得する。
 * @tparam S 値
 * @tparam F 作用素 アーベル群(可換群)
 * @tparam Mapping 作用素を適用するファンクタ 引数は(作用素, 値)
 * @tparam Composition 作用素の積のファンクタ
 * @tparam ID 作用素の単位元を返すファンクタ
 * @tparam Inv 作用素の逆元を返すファンクタ
 */
template <typename S, typename F, typename Mapping, typename Composition, typename ID, typename Inv>
class Imos {
   private:
    std::vector<S> data;
    std::vector<S> lazy;
    int _n, t;

   public:
    inline constexpr static auto mapping = Mapping();
    inline constexpr static auto composition = Composition();
    inline constexpr static auto id = ID();
    inline constexpr static auto inv = Inv();
    explicit Imos(int n) : _n(n), t(n), data(n), lazy(n, id()) {}
    Imos(int n, const S& value) : _n(n), t(n), data(n, value), lazy(n, id()) {}
    explicit Imos(const std::vector<S>& value) : _n(value.size()), t(value.size()), data(value), lazy(value.size(), id()) {}
    /**
     * @brief 1点作用
     * @param k インデックス
     * @param f 作用素
     */
    void apply(int k, const F& f) {
        assert(0 <= k && k < _n);
        data[k] = mapping(f, data[k]);
    }
    /**
     * @brief [l, r)の区間の値にfを作用させる
     * @param l 半開区間の開始
     * @param r 半開区間の終端 0<=l<=r<=n
     * @param f 作用素
     */
    void apply(int l, int r, const F& f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l < _n) lazy[l] = composition(lazy[l], f);
        if (r < _n) lazy[r] = composition(lazy[r], inv(f));
        if (t > l) t = l;
    }
    /**
     * @brief 指定された要素の値を返す
     * @param k インデックス
     * @return const S& 値
     */
    const S& get(int k) {
        assert(0 <= k && k < _n);
        while (t <= k) {
            data[t] = mapping(lazy[t], data[t]);
            if (t + 1 < _n) {
                lazy[t + 1] = composition(lazy[t], lazy[t + 1]);
            }
            lazy[t] = id();
            t++;
        }
        return data[k];
    }
};

/**
 * @brief 区間加算
 * @tparam S 可換群の型
 */
template <typename S>
using StaticRAddQ = Imos<S, S, std::plus<S>, std::plus<S>, more_functional::None<S>, std::negate<F>>;
/**
 * @brief 区間積
 * @tparam S 可換群の型
 */
template <typename S>
using StaticRMulQ = Imos<S, S, std::multiplies<S>, std::multiplies<S>, more_functional::One<S>, more_functional::Div<S>>;
