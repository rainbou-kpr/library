#pragma once

/**
 * @file modint.hpp
 * @brief 四則演算において自動で mod を取るクラス
 */

#include <iostream>
#include <utility>
#include <limits>
#include <type_traits>
#include <cstdint>
#include <cassert>

namespace detail {
    static constexpr std::uint16_t prime32_bases[] {
        15591,  2018,  166, 7429,  8064, 16045, 10503,  4399,  1949,  1295, 2776,  3620,   560,  3128,  5212,  2657,
         2300,  2021, 4652, 1471,  9336,  4018,  2398, 20462, 10277,  8028, 2213,  6219,   620,  3763,  4852,  5012,
         3185,  1333, 6227, 5298,  1074,  2391,  5113,  7061,   803,  1269, 3875,   422,   751,   580,  4729, 10239,
          746,  2951,  556, 2206,  3778,   481,  1522,  3476,   481,  2487, 3266,  5633,   488,  3373,  6441,  3344,
           17, 15105, 1490, 4154,  2036,  1882,  1813,   467,  3307, 14042, 6371,   658,  1005,   903,   737,  1887,
         7447,  1888, 2848, 1784,  7559,  3400,   951, 13969,  4304,   177,   41, 19875,  3110, 13221,  8726,   571,
         7043,  6943, 1199,  352,  6435,   165,  1169,  3315,   978,   233, 3003,  2562,  2994, 10587, 10030,  2377,
         1902,  5354, 4447, 1555,   263, 27027,  2283,   305,   669,  1912,  601,  6186,   429,  1930, 14873,  1784,
         1661,   524, 3577,  236,  2360,  6146,  2850, 55637,  1753,  4178, 8466,   222,  2579,  2743,  2031,  2226,
         2276,   374, 2132,  813, 23788,  1610,  4422,  5159,  1725,  3597, 3366, 14336,   579,   165,  1375, 10018,
        12616,  9816, 1371,  536,  1867, 10864,   857,  2206,  5788,   434, 8085, 17618,   727,  3639,  1595,  4944,
         2129,  2029, 8195, 8344,  6232,  9183,  8126,  1870,  3296,  7455, 8947, 25017,   541, 19115,   368,   566,
         5674,   411,  522, 1027,  8215,  2050,  6544, 10049,   614,   774, 2333,  3007, 35201,  4706,  1152,  1785,
         1028,  1540, 3743,  493,  4474,  2521, 26845,  8354,   864, 18915, 5465,  2447,    42,  4511,  1660,   166,
         1249,  6259, 2553,  304,   272,  7286,    73,  6554,   899,  2816, 5197, 13330,  7054,  2818,  3199,   811,
          922,   350, 7514, 4452,  3449,  2663,  4708,   418,  1621,  1171, 3471,    88, 11345,   412,  1559,   194,
    };

    static constexpr bool is_SPRP(std::uint32_t n, std::uint32_t a) noexcept {
        std::uint32_t d = n - 1;
        std::uint32_t s = 0;
        while ((d & 1) == 0) {
            ++s;
            d >>= 1;
        }
        std::uint64_t cur = 1;
        std::uint64_t pw = d;
        while (pw) {
            if (pw & 1) cur = (cur * a) % n;
            a = (static_cast<std::uint64_t>(a) * a) % n;
            pw >>= 1;
        }
        if (cur == 1) return true;
        for (std::uint32_t r = 0; r < s; ++r) {
            if (cur == n - 1) return true;
            cur = (cur * cur) % n;
        }
        return false;
    }

    // 32ビット符号なし整数の素数判定
    // 参考: M. Forisek and J. Jancina, “Fast Primality Testing for Integers That Fit into a Machine Word,” presented at the Conference on Current Trends in Theory and Practice of Informatics, 2015.
    [[nodiscard]]
    static constexpr bool is_prime32(std::uint32_t x) noexcept {
        if (x == 2 || x == 3 || x == 5 || x == 7) return true;
        if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
        if (x < 121) return (x > 1);
        std::uint64_t h = x;
        h = ((h >> 16) ^ h) * 0x45d9f3b;
        h = ((h >> 16) ^ h) * 0x45d9f3b;
        h = ((h >> 16) ^ h) & 0xff;
        return is_SPRP(x, prime32_bases[h]);
    }
}

/// @brief static_modint と dynamic_modint の実装を CRTP によって行うためのクラステンプレート
/// @tparam Modint このクラステンプレートを継承するクラス
template <class Modint>
class modint_base {
public:
    /// @brief 保持する値の型
    using value_type = std::uint32_t;

    /// @brief 0 で初期化します。
    constexpr modint_base() noexcept
        : m_value{ 0 } {}

    /// @brief @c value の剰余で初期化します。
    /// @param value 初期化に使う値
    template <class SignedIntegral, std::enable_if_t<std::is_integral_v<SignedIntegral> && std::is_signed_v<SignedIntegral>>* = nullptr>
    constexpr modint_base(SignedIntegral value) noexcept
        : m_value{ static_cast<value_type>((static_cast<long long>(value) % Modint::mod() + Modint::mod()) % Modint::mod()) } {}

    /// @brief @c value の剰余で初期化します。
    /// @param value 初期化に使う値
    template <class UnsignedIntegral, std::enable_if_t<std::is_integral_v<UnsignedIntegral> && std::is_unsigned_v<UnsignedIntegral>>* = nullptr>
    constexpr modint_base(UnsignedIntegral value) noexcept
        : m_value{ static_cast<value_type>(value % Modint::mod()) } {}

    /// @brief 保持している値を取得します。
    /// @return 保持している値
    [[nodiscard]]
    constexpr value_type value() const noexcept {
        return m_value;
    }

    /// @brief 保持している値をインクリメントして、剰余を取ります。
    /// @return @c *this
    constexpr Modint& operator++() noexcept {
        ++m_value;
        if (m_value == Modint::mod()) {
            m_value = 0;
        }
        return static_cast<Modint&>(*this);
    }

    /// @brief 保持している値をインクリメントして、剰余を取ります。
    /// @return @c *this
    constexpr Modint operator++(int) noexcept {
        auto x = static_cast<const Modint&>(*this);
        ++*this;
        return x;
    }

    /// @brief 保持している値をデクリメントして、剰余を取ります。
    /// @return @c *this
    constexpr Modint& operator--() noexcept {
        if (m_value == 0) {
            m_value = Modint::mod();
        }
        --m_value;
        return static_cast<Modint&>(*this);
    }

    /// @brief 保持している値をデクリメントして、剰余を取ります。
    /// @return @c *this
    constexpr Modint operator--(int) noexcept {
        auto x = static_cast<const Modint&>(*this);
        --*this;
        return x;
    }

    /// @brief 保持している値に @c x の持つ値を足して、剰余を取ります。
    /// @param x 足す数
    /// @return @c *this
    constexpr Modint& operator+=(const Modint& x) noexcept {
        m_value += x.m_value;
        if (m_value >= Modint::mod()) {
            m_value -= Modint::mod();
        }
        return static_cast<Modint&>(*this);
    }

    /// @brief 保持している値から @c x の持つ値を引いて、剰余を取ります。
    /// @param x 引く数
    /// @return @c *this
    constexpr Modint& operator-=(const Modint& x) noexcept {
        m_value -= x.m_value;
        if (m_value >= Modint::mod()) {
            m_value += Modint::mod();
        }
        return static_cast<Modint&>(*this);
    }

    /// @brief 保持している値に @c x の持つ値を掛けて、剰余を取ります。
    /// @param x 掛ける数
    /// @return @c *this
    constexpr Modint& operator*=(const Modint& x) noexcept {
        m_value = static_cast<value_type>(static_cast<std::uint64_t>(m_value) * x.m_value % Modint::mod());
        return static_cast<Modint&>(*this);
    }

    /// @brief 保持している値を @c x の持つ値で割って、剰余を取ります。
    /// @remark 時間計算量： @f$O(\log x)@f$
    /// @param x 割る数
    /// @return @c *this
    constexpr Modint& operator/=(const Modint& x) noexcept {
        return *this *= x.inv();
    }

    /// @brief 自身のコピーを返します。
    /// @return @c *this
    [[nodiscard]]
    constexpr Modint operator+() const noexcept {
        return static_cast<const Modint&>(*this);
    }

    /// @brief 自身の反数を返します。
    /// @return 自身の反数
    [[nodiscard]]
    constexpr Modint operator-() const noexcept {
        return 0 - static_cast<const Modint&>(*this);
    }

    /// @brief 自身の @c n 乗を返します。
    /// @remark 時間計算量： @f$O(\log n)@f$
    /// @param n 指数
    /// @return 自身の @c n 乗
    [[nodiscard]]
    constexpr Modint pow(unsigned long long n) const noexcept {
        Modint x = 1;
        Modint y = static_cast<const Modint&>(*this);
        while (n) {
            if (n & 1) {
                x *= y;
            }
            y *= y;
            n >>= 1;
        }
        return x;
    }

    /// @brief 自身の逆数を返します。
    /// @remark 時間計算量： @f$O(\log value)@f$
    /// @return 自身の逆数
    [[nodiscard]]
    constexpr Modint inv() const noexcept {
        long long a = Modint::mod();
        long long b = m_value;
        long long x = 0;
        long long y = 1;
        while (b) {
            auto t = a / b;
            auto u = a - t * b;
            a = b;
            b = u;
            u = x - t * y;
            x = y;
            y = u;
        }
        assert(a == 1 && "The inverse element does not exist.");
        x %= Modint::mod();
        if (x < 0) {
            x += Modint::mod();
        }
        return x;
    }

    /// @brief @c x に @c y を足したオブジェクトを返します。
    /// @param x 足される数
    /// @param y 足す数
    /// @return @c x に @c y を足したオブジェクト
    [[nodiscard]]
    friend constexpr Modint operator+(const Modint& x, const Modint& y) noexcept {
        return std::move(Modint{ x } += y);
    }

    /// @brief @c x から @c y を引いたオブジェクトを返します。
    /// @param x 引かれる数
    /// @param y 引く数
    /// @return @c x から @c y を引いたオブジェクト
    [[nodiscard]]
    friend constexpr Modint operator-(const Modint& x, const Modint& y) noexcept {
        return std::move(Modint{ x } -= y);
    }

    /// @brief @c x に @c y を掛けたオブジェクトを返します。
    /// @param x 掛けられる数
    /// @param y 掛ける数
    /// @return @c x に @c y を掛けたオブジェクト
    [[nodiscard]]
    friend constexpr Modint operator*(const Modint& x, const Modint& y) noexcept {
        return std::move(Modint{ x } *= y);
    }

    /// @brief @c x を @c y で割ったオブジェクトを返します。
    /// @param x 割られる数
    /// @param y 割る数
    /// @return @c x を @c y で割ったオブジェクト
    [[nodiscard]]
    friend constexpr Modint operator/(const Modint& x, const Modint& y) noexcept {
        return std::move(Modint{ x } /= y);
    }

    /// @brief @c x と @c y の保持する値が等しいかどうかを調べます。
    /// @return @c x と @c y の保持する値が等しければ @c true 、そうでなければ @c false
    [[nodiscard]]
    friend constexpr bool operator==(const Modint& x, const Modint& y) noexcept {
        return x.m_value == y.m_value;
    }

    /// @brief @c x と @c y の保持する値が等しくないかどうかを調べます。
    /// @return @c x と @c y の保持する値が等しければ @c false 、そうでなければ @c true
    [[nodiscard]]
    friend constexpr bool operator!=(const Modint& x, const Modint& y) noexcept {
        return not (x == y);
    }

    /// @brief 入力ストリームから符号付き整数を読み取り、 @c x に格納します。
    /// @tparam CharT 入力ストリームの文字型
    /// @tparam Traits 入力ストリームの文字トレイト
    /// @param is 入力ストリーム
    /// @param x 入力を受け取るオブジェクト
    /// @return @c is
    template <class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Modint& x) {
        long long tmp;
        is >> tmp;
        x = tmp;
        return is;
    }

    /// @brief 出力ストリームに @c x の保持する値を出力します。
    /// @tparam CharT 出力ストリームの文字型
    /// @tparam Traits 出力ストリームの文字トレイト
    /// @param os 出力ストリーム
    /// @param x 出力するオブジェクト
    /// @return @c os
    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Modint& x) {
        os << x.value();
        return os;
    }

protected:
    value_type m_value;
};

/// @brief コンパイル時に法が決まるとき、四則演算において自動で mod を取るクラス
/// @tparam Mod 法
template <std::uint32_t Mod>
class static_modint : public modint_base<static_modint<Mod>> {
    static_assert(Mod > 0 && Mod <= std::numeric_limits<std::uint32_t>::max() / 2);

private:
    using base_type = modint_base<static_modint<Mod>>;

public:
    using typename base_type::value_type;

    /// @brief 法を取得します。
    /// @return 法
    [[nodiscard]]
    static constexpr value_type mod() noexcept {
        return Mod;
    }

    /// @brief 0 で初期化します。
    constexpr static_modint() noexcept
        : base_type{} {}

    /// @brief @c value の剰余で初期化します。
    /// @param value 初期化に使う値
    template <class SignedIntegral, std::enable_if_t<std::is_integral_v<SignedIntegral>>* = nullptr>
    constexpr static_modint(SignedIntegral value) noexcept
        : base_type{value} {}

    /// @brief 自身の逆数を返します。
    /// @remark 時間計算量： @f$O(\log value)@f$
    /// @return 自身の逆数
    [[nodiscard]]
    constexpr static_modint inv() const noexcept {
        if constexpr (detail::is_prime32(Mod)) {
            assert(this->m_value != 0 && "The inverse element of zero does not exist.");
            return this->pow(Mod - 2);
        }
        else {
            return base_type::inv();
        }
    }
};

/// @brief 実行時に法が決まるとき、四則演算において自動で mod を取るクラス
/// @tparam ID このIDごとに法を設定することができます
template <int ID>
class dynamic_modint : public modint_base<dynamic_modint<ID>> {
private:
    using base_type = modint_base<dynamic_modint<ID>>;

public:
    using typename base_type::value_type;

    /// @brief 法を取得します。
    /// @return 法
    [[nodiscard]]
    static value_type mod() noexcept {
        return modulus;
    }

    /// @brief 法を設定します。
    /// @param m 新しい法
    static void set_mod(value_type m) noexcept {
        assert(m > 0 && m <= std::numeric_limits<value_type>::max() / 2);
        modulus = m;
    }

    /// @brief 0 で初期化します。
    constexpr dynamic_modint() noexcept
        : base_type{} {}

    /// @brief @c value の剰余で初期化します。
    /// @param value 初期化に使う値
    template <class SignedIntegral, std::enable_if_t<std::is_integral_v<SignedIntegral>>* = nullptr>
    constexpr dynamic_modint(SignedIntegral value) noexcept
        : base_type{value} {}

private:
    inline static value_type modulus = 998244353;
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;
