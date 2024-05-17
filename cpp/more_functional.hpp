#pragma once

/**
 * @file more_functional.hpp
 * @brief 関数オブジェクトを定義する
 */

namespace more_functional {
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
template <typename S>
struct Div {
    S operator()(const S& a) const { return S(1) / a; }
};
}  // namespace more_functional
