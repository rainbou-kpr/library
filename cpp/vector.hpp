#pragma once

#include <array>
#include <initializer_list>
#include <type_traits>

/**
 * @brief 幾何学としてのベクトル
 *
 * @tparam T 型 省略したらdouble
 * @tparam Dim 次元 省略したら2
 */
template <typename T = double, int Dim = 2, std::enable_if_t<std::is_scalar_v<T> && (Dim > 0)>* = nullptr>
struct Vector {
    std::array<T, Dim> v; //!< ベクトルの成分表示

    /**
     * @brief デフォルトコンストラクタ
     * ゼロベクトル
     */
    constexpr Vector() noexcept : v() {}
    /**
     * @brief 可変長引数によるコンストラクタ
     * 
     * @tparam Args 
     */
    template <typename... Args, std::enable_if_t<(sizeof...(Args) == Dim)>* = nullptr>
    constexpr Vector(Args... args) noexcept : v{args...} {}
    
    /**
     * @brief i番目の成分を返す
     * 
     * @param i
     * @return constexpr T& 
     */
    constexpr T& operator[](int i) noexcept {
        return v[i];
    }
    /**
     * @brief i番目の成分を返す
     * 
     * @param i
     * @return constexpr T& 
     */
    constexpr const T& operator[](int i) const noexcept {
        return v[i];
    }

    /**
     * @brief 加算代入演算子
     * 
     * @param rhs 
     * @return constexpr Vector<T, Dim>& 
     */
    constexpr Vector<T, Dim>& operator+=(const Vector<T, Dim>& rhs) noexcept {
        for(int i = 0; i < Dim; i++) v[i] += rhs[i];
        return *this;
    }
    /**
     * @brief 減算代入演算子
     * 
     * @param rhs 
     * @return constexpr Vector<T, Dim>& 
     */
    constexpr Vector<T, Dim>& operator-=(const Vector<T, Dim>& rhs) noexcept {
        for(int i = 0; i < Dim; i++) v[i] -= rhs.v[i];
        return *this;
    }
    /**
     * @brief スカラー倍代入演算子
     * 
     * @param coef 
     * @return constexpr Vector<T, Dim>& 
     */
    constexpr Vector<T, Dim>& operator*=(const T& coef) noexcept {
        for(int i = 0; i < Dim; i++) v[i] *= coef;
        return *this;
    }
    /**
     * @brief スカラーの逆数倍代入演算子
     * 
     * @param coef 
     * @return constexpr Vector<T, Dim>& 
     */
    constexpr Vector<T, Dim>& operator/=(const T& coef) noexcept {
        for(int i = 0; i < Dim; i++) v[i] /= coef;
        return *this;
    }
    
    /**
     * @brief 単項プラス演算子
     * 
     * @return constexpr Vector<T, Dim> 
     */
    [[nodiscard]]
    constexpr Vector<T, Dim> operator+() const noexcept {
        return *this;
    }
    /**
     * @brief 単項マイナス演算子
     * 
     * @return constexpr Vector<T, Dim> 
     */
    [[nodiscard]]
    constexpr Vector<T, Dim> operator-() const noexcept {
        return *this * (-1);
    }
    
    /**
     * @brief 加算演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<T, Dim> 
     */
    [[nodiscard]]
    friend constexpr Vector<T, Dim> operator+(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return std::move(lhs += rhs);
    }
    
    /**
     * @brief 減算演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<T, Dim> 
     */
    [[nodiscard]]
    friend constexpr Vector<T, Dim> operator-(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return std::move(lhs -= rhs);
    }
    
    /**
     * @brief スカラー倍演算子
     * 
     * @param lhs 
     * @param coef 
     * @return constexpr Vector<T, Dim> 
     */
    [[nodiscard]]
    friend constexpr Vector<T, Dim> operator*(const Vector<T, Dim>& lhs, const T& coef) noexcept {
        return std::move(lhs *= coef);
    }
    
    /**
     * @brief スカラーの逆数倍演算子
     * 
     * @param lhs 
     * @param coef 
     * @return constexpr Vector<T, Dim> 
     */
    [[nodiscard]]
    friend constexpr Vector<T, Dim> operator/(const Vector<T, Dim>& lhs, const T& coef) noexcept {
        return std::move(lhs /= coef);
    }
    
    /**
     * @brief 等価演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr bool
     */
    [[nodiscard]]
    friend constexpr bool operator==(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return lhs.v == rhs.v;
    }
    
    /**
     * @brief 非等価演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr bool 
     */
    [[nodiscard]]
    friend constexpr bool operator!=(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return lhs.v != rhs.v;
    }
    
    /**
     * @brief 小なり演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr bool 
     */ 
    [[nodiscard]]
    friend constexpr bool operator<(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return lhs.v < rhs.v;
    }
    /**
     * @brief 大なり演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr bool
     */
    [[nodiscard]]
    friend constexpr bool operator>(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return lhs.v > rhs.v;
    }
    /**
     * @brief 小なりイコール演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr bool 
     */
    [[nodiscard]]
    friend constexpr bool operator<=(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return lhs.v <= rhs.v;
    }
    /**
     * @brief 大なりイコール演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return constexpr bool
     */
    [[nodiscard]]
    friend constexpr bool operator>=(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) noexcept {
        return lhs.v >= rhs.v;
    }
    
    /**
     * @brief 偏角ソートのファンクタ
     * 
     * 二次元限定、反時計回り
     */
    struct ArgSortComp {
        template <std::enable_if_t<Dim == 2>* = nullptr>
        bool operator()(const Vector<T, Dim>& lhs, const Vector<T, Dim>& rhs) {
            int l_half = lhs[1] < 0 || (lhs[1] == 0 && lhs[0] < 0);
            int r_half = rhs[1] < 0 || (rhs[1] == 0 && rhs[0] < 0);
            if(l_half != r_half) return l_half < r_half;
            return rhs[0] * lhs[1] < lhs[0] * rhs[1];
        }
    };
    
    /**
     * @brief 入力ストリームからの読み込み
     * 
     * @tparam CharT 入力ストリームの文字型
     * @tparam Traits 入力ストリームの文字型特性
     * @param is 
     * @param rhs 
     * @return std::basic_istream<CharT, Traits>& 
     */
    template <class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector<T, Dim>& rhs) {
        for(int i = 0; i < Dim; i++) is >> rhs.v[i];
        return is;
    }
    /**
     * @brief 出力ストリームへの書き込み
     * 
     * @tparam CharT 出力ストリームの文字型
     * @tparam Traits 出力ストリームの文字型特性
     * @param is 
     * @param rhs 
     * @return std::basic_ostream<CharT, Traits>& 
     */
    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector<T, Dim>& rhs) {
        for(int i = 0; i < Dim; i++) {
            if(i != 0) os << ' ';
            os << rhs.v[i];
        }
        return os;
    }
};