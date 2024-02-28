#pragma once

#include <iterator>
#include <type_traits>
#include <utility>

namespace detail {
using std::begin, std::end;

template <class T, class = void>
struct is_range_impl : std::false_type {};
template <class T>
struct is_range_impl<T, std::void_t<decltype(begin(std::declval<T&>()), end(std::declval<T&>()))>> : std::true_type {};
}  // namespace detail

template <class T>
struct is_range : detail::is_range_impl<T>::type {};
template <class T>
inline constexpr bool is_range_v = is_range<T>::value;
