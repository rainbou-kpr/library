#pragma once

#include <vector>

/**
 * @brief Z-algorithm
 * s[0:]とs[i:]のLCPの長さを各iについて求める 全体でO(N)
 *
 * @tparam It 配列のイテレータ
 * @param begin 配列の開始イテレータ
 * @param end 配列の終了イテレータ
 * @return std::vector<typename std::iterator_traits<It>::value_type> z
 */
template <typename It>
std::vector<int> z_algorithm(It begin, It end) {
    int n = end - begin;
    std::vector<int> z(n);
    z[0] = n;
    for(int i = 1, j = 0; i < n;) {
        // [0, j)と[i, i + j)が一致している
        while(i + j < n && begin[j] == begin[i + j]) j++;
        z[i] = j;
        int k = 1; // [k,)と[i+k,)はLCPが等しいと確定している
        for(; k < j && k + z[k] < j; k++) {
            z[i + k] = z[k];
        }
        i += k;
        if(j) j -= k;
    }
    return z;
}

/**
 * @brief Z-algorithm
 * s[0:]とs[i:]のLCPの長さを各iについて求める 全体でO(N)
 *
 * @tparam R 配列の型
 * @param s 配列
 * @return std::vector<typename R::value_type> z
 */
template <typename R>
std::vector<int> z_algorithm(const R& s) {
    return z_algorithm(std::begin(s), std::end(s));
}
