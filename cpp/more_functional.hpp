#pragma once

/**
 * @file more_functional.hpp
 * @brief 関数オブジェクトを定義する
 */

#include <limits>
#include <numeric>
#include <type_traits>

namespace more_functional {
template <typename S>
struct Max {
    const S operator()(const S& a, const S& b) const { return std::max(a, b); }
};
template <typename S>
struct Min {
    const S operator()(const S& a, const S& b) const { return std::min(a, b); }
};
template <typename S, std::enable_if_t<std::is_integral_v<S>>* = nullptr>
struct Gcd {
    constexpr S operator()(const S& a, const S& b) const { return std::gcd(a, b); }
};
template <typename S>
struct Zero {
    S operator()() const { return S(0); }
};
template <typename S>
struct One {
    S operator()() const { return S(1); }
};
template <typename S>
struct None {
    S operator()() const { return S{}; }
};
template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>
struct MaxLimit {
    constexpr S operator()() const { return std::numeric_limits<S>::max(); }
};
template <typename S, std::enable_if_t<std::is_scalar_v<S>>* = nullptr>
struct MinLimit {
    constexpr S operator()() const { return std::numeric_limits<S>::lowest(); }
};
template <typename S>
struct Div {
    S operator()(const S& a) const { return S(1) / a; }
};
}  // namespace more_functional
