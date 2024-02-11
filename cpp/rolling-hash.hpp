#pragma once

#include <string>
#include <vector>
#include <random>
#include <cassert>

#include "traits.hpp"

struct RHString;

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
        __uint128_t c = static_cast<__uint128_t>(a) * b;
        return add(static_cast<unsigned long long>(c >> 61), static_cast<unsigned long long>(c & MOD));
    }

    void expand(int n) {
        while(static_cast<int>(power.size()) <= n) power.push_back(mul(power.back(), base));
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
     * @brief 配列/文字列のイテレータ間のハッシュの計算(O(N))
     *
     * @tparam It イテレータ
     * @param first 配列の開始イテレータ
     * @param last 配列の終了イテレータ
     * @return std::vector<unsigned long long> 先頭から各要素数分のハッシュ
     */
    template <typename It>
    std::vector<unsigned long long> build(It first, It last) {
        std::vector<unsigned long long> res;
        if constexpr (std::is_convertible_v<typename std::iterator_traits<It>::iterator_category, std::random_access_iterator_tag>) {
            res.reserve(last - first + 1);
        }
        res.push_back(0);
        for(; first != last; ++first) {
            res.push_back(add(mul(res.back(), base), *first));
        }
        return res;
    }

    /**
     * @brief 配列/文字列全体のハッシュの計算(O(N))
     *
     * @param s 配列/文字列
     * @return std::vector<unsigned long long> 先頭から各文字数分のハッシュ
     */
    template <typename R>
    std::vector<unsigned long long> build(R&& s) {
        using std::begin, std::end;
        return build(begin(s), end(s));
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

    friend RHString;
};

/**
 * @brief ローリングハッシュによって管理される文字列型
 */
struct RHString {
    RollingHash& rh;
    size_t sz;
    unsigned long long hash1;  //!< 正順
    unsigned long long hash2;  //!< 逆順
    /**
     * @brief コンストラクタ
     * 予めRollingHashをインスタンス化しておく必要がある
     */
    RHString(RollingHash& rh) : rh(rh), sz(0), hash1(0), hash2(0) {}
    RHString(RollingHash& rh, size_t sz, unsigned long long hash1, unsigned long long hash2) : rh(rh), sz(sz), hash1(hash1), hash2(hash2) {}
    RHString(const RHString& o) : rh(o.rh), sz(o.sz), hash1(o.hash1), hash2(o.hash2) {}
    template <class R, class = std::enable_if_t<is_range_v<R>>>
    RHString(RollingHash& rh, R&& s) : rh(rh) {
        using std::begin, std::end, std::rbegin, std::rend;
        sz = std::distance(begin(s), end(s));
        hash1 = rh.build(begin(s), end(s)).back();
        hash2 = rh.build(rbegin(s), rend(s)).back();
    }
    template <class T, class = std::enable_if_t<!is_range_v<T>>>
    RHString(RollingHash& rh, T x) : rh(rh) {
        sz = 1;
        hash1 = x;
        hash2 = x;
    }

    /**
     * @brief 回文か否か
     */
    bool is_palindrome() const {
        return hash1 == hash2;
    }
    size_t size() const {
        return sz;
    }
    void clear() {
        sz = 0;
        hash1 = 0;
        hash2 = 0;
    }
    bool empty() const {
        return sz == 0;
    }
    RHString& operator+=(const RHString& o) {
        assert(&rh == &o.rh);
        rh.expand(sz);
        rh.expand(o.sz);
        hash1 = rh.add(rh.mul(hash1, rh.power[o.sz]), o.hash1);
        hash2 = rh.add(hash2, rh.mul(o.hash2, rh.power[sz]));
        sz += o.sz;
        return *this;
    }
    /**
     * @brief 再代入する
     */
    void assign(const RHString& o) {
        assert(&rh == &o.rh);
        sz = o.sz;
        hash1 = o.hash1;
        hash2 = o.hash2;
    }
    /**
     * @brief 文字列(std::string)などで再代入する
     */
    template <class R, class = std::enable_if_t<is_range_v<R>>>
    void assign(R&& s) {
        using std::begin, std::end;
        sz = std::distance(begin(s), end(s));
        hash1 = rh.build(begin(s), end(s)).back();
        hash2 = rh.build(rbegin(s), rend(s)).back();
    }
    /**
     * @brief 文字(char)などで再代入する
     */
    template <class T, class = std::enable_if_t<not is_range_v<T>>>
    void assign(T x) {
        sz = 1;
        hash1 = x;
        hash2 = x;
    }
    /**
     * @brief const char*で再代入する
     */
    void assign(const char* s) {
        assign(std::string(s));
    }
    /**
     * @brief 再代入する
     */
    RHString& operator=(const RHString& o) {
        assign(o);
        return *this;
    }
    /**
     * @brief 文字列(std::string)などで再代入する
     */
    template <class R, class = std::enable_if_t<is_range_v<R>>>
    RHString& operator=(R&& s) {
        assign(s);
        return *this;
    }
    /**
     * @brief 文字(char)などで再代入する
     */
    template <class T, class = std::enable_if_t<not is_range_v<T>>>
    RHString& operator=(T x) {
        assign(x);
        return *this;
    }
    /**
     * @brief const char*で再代入する
     */
    RHString& operator=(const char* s) {
        assign(s);
        return *this;
    }
    friend RHString operator+(const RHString& t1, const RHString& t2) {
        RHString ret = t1;
        ret += t2;
        return ret;
    }
    friend bool operator==(const RHString& t1, const RHString& t2) {
        assert(&t1.rh == &t2.rh);
        return t1.sz == t2.sz && t1.hash1 == t2.hash1 && t1.hash2 == t2.hash2;
    }
    friend bool operator!=(const RHString& t1, const RHString& t2) { return !(t1 == t2); }
};
