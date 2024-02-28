---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: cpp/rolling-hash.hpp
    title: "\u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/atcoder-abc331-f.test.cpp
    title: test/atcoder-abc331-f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-enumerate-palindromes.test.cpp
    title: test/yosupo-enumerate-palindromes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: '#line 2 "cpp/traits.hpp"


    #include <iterator>

    #include <type_traits>

    #include <utility>


    namespace detail {

    using std::begin, std::end;


    template <class T, class = void>

    struct is_range_impl : std::false_type {};

    template <class T>

    struct is_range_impl<T, std::void_t<decltype(begin(std::declval<T&>()), end(std::declval<T&>()))>>
    : std::true_type {};

    }  // namespace detail


    template <class T>

    struct is_range : detail::is_range_impl<T>::type {};

    template <class T>

    inline constexpr bool is_range_v = is_range<T>::value;

    '
  code: '#pragma once


    #include <iterator>

    #include <type_traits>

    #include <utility>


    namespace detail {

    using std::begin, std::end;


    template <class T, class = void>

    struct is_range_impl : std::false_type {};

    template <class T>

    struct is_range_impl<T, std::void_t<decltype(begin(std::declval<T&>()), end(std::declval<T&>()))>>
    : std::true_type {};

    }  // namespace detail


    template <class T>

    struct is_range : detail::is_range_impl<T>::type {};

    template <class T>

    inline constexpr bool is_range_v = is_range<T>::value;

    '
  dependsOn: []
  isVerificationFile: false
  path: cpp/traits.hpp
  requiredBy:
  - cpp/rolling-hash.hpp
  timestamp: '2024-02-11 12:44:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/atcoder-abc331-f.test.cpp
  - test/yosupo-enumerate-palindromes.test.cpp
documentation_of: cpp/traits.hpp
layout: document
redirect_from:
- /library/cpp/traits.hpp
- /library/cpp/traits.hpp.html
title: cpp/traits.hpp
---
