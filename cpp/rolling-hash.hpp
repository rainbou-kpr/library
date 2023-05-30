#pragma once

#include <string>
#include <vector>
#include <random>

/**
 * @brief ローリングハッシュ
 *
 * ビット演算に寄る高速化のためハッシュはMOD = 2^61-1で計算される
 *
 * 10^8個くらいなら99%の確率で衝突する組が存在しない
 */
class RollingHash {
    constexpr static unsigned long long MASK30 = (1ULL << 30) - 1;
    constexpr static unsigned long long MASK31 = (1ULL << 31) - 1;
    constexpr static unsigned long long MOD = (1ULL << 61) - 1;

    // a < MOD, b < MOD必須
    constexpr static unsigned long long add(unsigned long long a, unsigned long long b) {
        if((a += b) >= MOD) a -= MOD;
        return a;
    }

    // a < MOD, b < MOD必須
    constexpr static unsigned long long mul(unsigned long long a, unsigned long long b) {
        __uint128_t c = (__uint128_t)a * b;
        return add((unsigned long long)(c >> 61), (unsigned long long)c & MOD);
    }

    void expand(int n) {
        while(power.size() <= n) power.push_back(mul(power.back(), base));
    }

public:
    unsigned int base; //!< ハッシュの基数
    std::vector<unsigned long long> power; //!< baseの累乗

    /**
     * @brief コンストラクタ
     *
     * @param base ハッシュの基数 省略するとランダム
     */
    RollingHash(unsigned int base = 0) : base(base) {
        if(base == 0) {
            std::mt19937 mt(std::random_device{}());
            this->base = std::uniform_int_distribution<unsigned int>(129, ~0U)(mt);
        }
        power = {1};
    }

    /**
     * @brief 配列のハッシュの計算(O(N))
     *
     * @tparam It イテレータ
     * @param first 配列の開始イテレータ
     * @param last 配列の終了イテレータ
     * @return std::vector<unsigned long long> 先頭から各要素数分のハッシュ
     */
    template <typename It>
    std::vector<unsigned long long> build(It first, It last) {
        int n = std::distance(first, last);
        std::vector<unsigned long long> res(n+1);
        for(int i = 0; i < n; i++) {
            res[i+1] = add(mul(res[i], base), *(first+i));
        }
        return res;
    }

    /**
     * @brief 文字列のハッシュの計算(O(N))
     *
     * @param s 文字列
     * @return std::vector<unsigned long long> 先頭から各文字数分のハッシュ
     */
    std::vector<unsigned long long> build(const std::string& s) {
        return build(s.begin(), s.end());
    }

    /**
     * @brief [l,r)のハッシュの計算(O(1))
     *
     * @param hash 先頭からのハッシュ
     * @param l 区間の左端
     * @param r 区間の右端
     * @return unsigned long long [l,r)のハッシュ
     */
    unsigned long long query(const std::vector<unsigned long long>& hash, int l, int r) {
        expand(r - l);
        return add(hash[r], MOD - mul(hash[l], power[r-l]));
    }
};
