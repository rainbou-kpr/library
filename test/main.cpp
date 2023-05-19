#line 1 "yukicoder-search-oji.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/1340"

#line 2 "/mnt/c/Users/shinc/atcoder/library/cpp/matrix.hpp"

#include <vector>
#include <string>
#include <algorithm>

/**
 * @brief 行列
 * @tparam T 型 行列(グリッド)の要素となるintやchar
 */
template<class T> struct Matrix {
    int n, m;
    std::vector<std::vector<T>> v;

    /**
     * @brief コンストラクタ
     * @param v 行列(グリッド)の元となる vector<string> や vector<vector<T>>
     * @return Matrix
     */
    template <typename Iterable>
    constexpr Matrix(const std::vector<Iterable>& v_) noexcept : n(v_.size()), m(v_.size() == 0 ? 0 : v_[0].size()) {
        v.resize(n);
        for(int i = 0; i < n; i++) {
            v[i].assign(v_[i].begin(), v_[i].end());
        }
    }

    /**
     * @brief コンストラクタ
     * @param _n 行列(グリッド)の行数
     * @param _m 行列(グリッド)の列数
     * @param _val 行列(グリッド)の要素の初期値
     * @return Matrix
     */
    constexpr Matrix(int _n, int _m, T _val = T()) : n(_n), m(_m), v(n, std::vector<T>(m, _val)) {}
    
    constexpr auto begin() noexcept {return v.begin();}
    constexpr auto end() noexcept {return v.end();}

    /**
     * @brief 行列(グリッド)の行数
     * @return size_t
     */
    [[nodiscard]]
    constexpr size_t size() const {return v.size();}

    std::vector<T>& operator [] (int i) {return v[i];}
    const std::vector<T>& operator [] (int i) const {return v[i];}
    constexpr Matrix<T>& operator = (const std::vector<std::vector<T>> &A) noexcept {
        v = A; return *this;
    }

    /**
     * @brief 転置
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix transpose() noexcept {
        if(n == 0) return Matrix(v);
        std::vector<std::vector<T>> ret(m);
        for(int i = 0; i < m; i ++) {
            ret[i].resize(n);
            for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];
        }
        return Matrix(ret);
    }

    /**
     * @brief 左右反転
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix rev_lr() noexcept {
        std::vector<std::vector<T>> ret = v;
        for(int i = 0; i < n; i ++) std::reverse(ret[i].begin(), ret[i].end());
        return Matrix(ret);
    }

    /**
     * @brief 上下反転
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix rev_ud() noexcept {
        std::vector<std::vector<T>> ret = v;
        reverse(ret.begin(), ret.end());
        return Matrix(ret);
    }

    /**
     * @brief 時計周りに90度回転
     * @param k 回転する回数
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix rotate(int k) noexcept {
        k %= 4;
        if(k == 0) return *this;
        if(k < 0) k += 4;
        if(k == 2) return this->rev_lr().rev_ud();
        std::vector<std::vector<T>> ret(m);
        if(k == 1) {
            for(int i = 0; i < m; i ++) {
                ret[i].resize(n);
                for(int j = 0; j < n; j ++) ret[i][j] = v[n - j - 1][i];
            }
        } else {
            for(int i = 0; i < m; i ++) {
                ret[i].resize(n);
                for(int j = 0; j < n; j ++) ret[i][j] = v[j][m - i - 1];
            }
        }
        return Matrix(ret);
    }

    /**
     * @brief (i, j)を((i + dy) mod n, (j + dx) mod m)に移動
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift(int dy, int dx) noexcept {
        std::vector<std::vector<T>> ret = v;
        for(int i = 0, ni = dy; i < n; i ++, ni ++) {
            if(ni >= n) ni = 0;
            for(int j = 0, nj = dx; j < m; j ++, nj ++) {
                if(nj >= m) nj = 0;
                ret[ni][nj] = v[i][j];
            }
        }
        return Matrix(ret);
    }

    /**
     * @brief 左にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_l(int k) noexcept {
        return this->shift(0, -k);
    }

    /**
     * @brief 右にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_r(int k) noexcept {
        return this->shift(0, k);
    }

    /**
     * @brief 上にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_u(int k) noexcept {
        return this->shift(-k, 0);
    }

    /**
     * @brief 下にk回シフト
     * @return Matrix
     */
    [[nodiscard]]
    constexpr Matrix shift_d(int k) noexcept {
        return this->shift(k, 0);
    }

    /**
     * @brief グリッドをvector<string>で返す
     * @return std::vector<std::string>
     */
    [[nodiscard]]
    constexpr std::vector<std::string> vstr() noexcept {
        std::vector<std::string> ret(n);
        for(int i = 0; i < n; i ++) {
            ret[i].assign(v[i].begin(), v[i].end());
        }
        return ret;
    }

    /**
     * @brief グリッドのj列目を返す
     * @param j 返す列番号(0-indexed)
     * @return std::vector<T>
     */
    [[nodiscard]]
    constexpr std::vector<T> col(int j) noexcept {
        std::vector<T> ret(n);
        for(int i = 0; i < n; i ++) {
            ret[i] = v[i][j];
        }
        return ret;
    }

    /**
     * @brief グリッドのi行目をstringで返す
     * @param i 返す行番号(0-indexed)
     * @return std::string
     */
    [[nodiscard]]
    constexpr std::string str(int i) noexcept {
        std::string ret;
        ret.assign(v[i].begin(), v[i].end());
        return ret;
    }

    constexpr Matrix &operator+=(const Matrix &B) {
        if(n == 0) return (*this);
        assert(n == B.size() && m == B[0].length());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
        return (*this);
    }

    constexpr Matrix &operator-=(const Matrix &B) {
        if(n == 0) return (*this);
        assert(n == B.size() && m == B[0].length());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
        return (*this);
    }

    constexpr Matrix &operator*=(const Matrix &B) {
        int p = B[0].size();
        Matrix<T> C(n, p);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int k = 0; k < p; k++) C[i][j] += (*this)[i][k] * B[k][j];
        v = C.v;
        m = p;
        return (*this);
    }

    [[nodiscard]]
    constexpr Matrix pow(long long k) {
        Matrix<T> B(n, n);
        for(int i = 0; i < n; i ++) B[i][i] = 1;
        while(k > 0) {
            if(k & 1) B *= *this;
            *this *= *this;
            k >>= 1;
        }
        v = B.v;
        return (*this);
    }

    [[nodiscard]]
    constexpr Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
    [[nodiscard]]
    constexpr Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
    [[nodiscard]]
    constexpr Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }

    [[nodiscard]]
    constexpr friend std::vector<T> operator*(const Matrix &A, const std::vector<T> &B) {
        std::vector<T> ret(A.n, 0);
        for(int i = 0; i < A.n; i ++) {
            for(int j = 0; j < A.m; j ++) {
                ret[i] += A[i][j] * B[j];
            }
        }
        return ret;
    }

    [[nodiscard]]
    constexpr friend std::vector<T> operator*(const std::vector<T> &A, const Matrix &B) {
        std::vector<T> ret(B.m, 0);
        for(int i = 0; i < B.n; i ++) {
            for(int j = 0; j < B.m; j ++) {
                ret[j] += A[i] * B[i][j];
            }
        }
        return ret;
    }
};
#line 2 "/mnt/c/Users/shinc/atcoder/library/cpp/modint.hpp"

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

    using base_type::modint_base;

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

    using base_type::modint_base;

private:
    inline static value_type modulus = 998244353;
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;
#line 6 "yukicoder-search-oji.test.cpp"

using mint3 = static_modint<57>;

int main() {
    long long n, m, t;
    std::cin >> n >> m >> t;
    
    Matrix<modint1000000007> mat1(n, n, 0);
    Matrix<modint998244353> mat2(n, n, 0);
    Matrix<mint3> mat3(n, n, 0);
    for(int i = 0; i < m; i ++) {
        int a, b;
        std::cin >> a >> b;
        mat1[b][a] = 1;
        mat2[b][a] = 1;
        mat3[b][a] = 1;
    }
    std::vector<modint1000000007> v1(n, 0);
    std::vector<modint998244353> v2(n, 0);
    std::vector<mint3> v3(n, 0);
    v1[0] = 1;
    v2[0] = 1;
    v3[0] = 1;

    v1 = mat1.pow(t) * v1;
    v2 = mat2.pow(t) * v2;
    v3 = mat3.pow(t) * v3;

    int ans = 0;
    for(int i = 0; i < n; i ++) {
        if(v1[i].value() || v2[i].value() || v3[i].value()) ans ++;
    }
    std::cout << ans << std::endl;

    return 0;
}

