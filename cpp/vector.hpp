#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <istream>
#include <numeric>
#include <ostream>
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
    template <typename... Args>
    constexpr Vector(Args... args) noexcept : v{args...} {}
    
    /**
     * @brief i番目の成分を返す
     * 
     * @param i
     * @return T& 
     */
    constexpr T& operator[](int i) noexcept {
        return v[i];
    }
    /**
     * @brief i番目の成分を返す
     * 
     * @param i
     * @return T& 
     */
    constexpr const T& operator[](int i) const noexcept {
        return v[i];
    }

    /**
     * @brief 加算代入演算子
     * 
     * @param rhs 
     * @return Vector& 
     */
    constexpr Vector& operator+=(const Vector& rhs) noexcept {
        for(int i = 0; i < Dim; i++) v[i] += rhs[i];
        return *this;
    }
    /**
     * @brief 減算代入演算子
     * 
     * @param rhs 
     * @return Vector& 
     */
    constexpr Vector& operator-=(const Vector& rhs) noexcept {
        for(int i = 0; i < Dim; i++) v[i] -= rhs.v[i];
        return *this;
    }
    /**
     * @brief スカラー倍代入演算子
     * 
     * @param coef 
     * @return Vector& 
     */
    constexpr Vector& operator*=(const T& coef) noexcept {
        for(int i = 0; i < Dim; i++) v[i] *= coef;
        return *this;
    }
    /**
     * @brief スカラーの逆数倍代入演算子
     * 
     * @param coef 
     * @return Vector& 
     */
    Vector& operator/=(const T& coef) {
        for(int i = 0; i < Dim; i++) {
            if constexpr(std::is_integral_v<T>) {
                assert(v[i] % coef == 0 && "Vector::operator/= : coef must be a divisor of all elements");
            }
            v[i] /= coef;
        }
        return *this;
    }
    
    /**
     * @brief 単項プラス演算子
     * 
     * @return Vector 
     */
    [[nodiscard]]
    constexpr Vector operator+() const noexcept {
        return *this;
    }
    /**
     * @brief 単項マイナス演算子
     * 
     * @return Vector 
     */
    [[nodiscard]]
    constexpr Vector operator-() const noexcept {
        return *this * (-1);
    }
    
    /**
     * @brief 加算演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return Vector 
     */
    [[nodiscard]]
    friend constexpr Vector operator+(const Vector& lhs, const Vector& rhs) noexcept {
        return std::move(Vector(lhs) += rhs);
    }
    
    /**
     * @brief 減算演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return Vector 
     */
    [[nodiscard]]
    friend constexpr Vector operator-(const Vector& lhs, const Vector& rhs) noexcept {
        return std::move(Vector(lhs) -= rhs);
    }
    
    /**
     * @brief スカラー倍演算子
     * 
     * @param lhs 
     * @param coef 
     * @return Vector 
     */
    [[nodiscard]]
    friend constexpr Vector operator*(const Vector& lhs, const T& coef) noexcept {
        return std::move(Vector(lhs) *= coef);
    }
    
    /**
     * @brief スカラー倍演算子
     * 
     * @param coef 
     * @param rhs 
     * @return Vector 
     */
    [[nodiscard]]
    friend constexpr Vector operator*(const T& coef, const Vector& rhs) noexcept {
        return std::move(Vector(rhs) *= coef);
    }
    
    /**
     * @brief スカラーの逆数倍演算子
     * 
     * @param lhs 
     * @param coef 
     * @return Vector 
     */
    [[nodiscard]]
    friend Vector operator/(const Vector& lhs, const T& coef) {
        return std::move(Vector(lhs) /= coef);
    }
    
    /**
     * @brief 等価演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return bool
     */
    [[nodiscard]]
    friend constexpr bool operator==(const Vector& lhs, const Vector& rhs) noexcept {
        return lhs.v == rhs.v;
    }
    
    /**
     * @brief 非等価演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return bool 
     */
    [[nodiscard]]
    friend constexpr bool operator!=(const Vector& lhs, const Vector& rhs) noexcept {
        return lhs.v != rhs.v;
    }
    
    /**
     * @brief 小なり演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return bool 
     */ 
    [[nodiscard]]
    friend constexpr bool operator<(const Vector& lhs, const Vector& rhs) noexcept {
        return lhs.v < rhs.v;
    }
    /**
     * @brief 大なり演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return bool
     */
    [[nodiscard]]
    friend constexpr bool operator>(const Vector& lhs, const Vector& rhs) noexcept {
        return lhs.v > rhs.v;
    }
    /**
     * @brief 小なりイコール演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return bool 
     */
    [[nodiscard]]
    friend constexpr bool operator<=(const Vector& lhs, const Vector& rhs) noexcept {
        return lhs.v <= rhs.v;
    }
    /**
     * @brief 大なりイコール演算子
     * 
     * @param lhs 
     * @param rhs 
     * @return bool
     */
    [[nodiscard]]
    friend constexpr bool operator>=(const Vector& lhs, const Vector& rhs) noexcept {
        return lhs.v >= rhs.v;
    }
    
    /**
     * @brief 偏角ソートのファンクタ
     * 
     * 二次元限定、反時計回り
     */
    struct ArgSortComp {
        template <std::enable_if_t<Dim == 2>* = nullptr>
        bool operator()(const Vector& lhs, const Vector& rhs) {
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
    friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector& rhs) {
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
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector& rhs) {
        for(int i = 0; i < Dim; i++) {
            if(i != 0) os << ' ';
            os << rhs.v[i];
        }
        return os;
    }
    
    /**
     * @brief 内積
     * 
     * @param lhs 
     * @param rhs 
     * @return T 
     */
    friend constexpr T dot(const Vector& lhs, const Vector& rhs) noexcept {
        T ret = 0;
        for(int i = 0; i < Dim; i++) ret += lhs[i] * rhs[i];
        return ret;
    }
    
    /**
     * @brief 絶対値の2乗
     * 
     * @return T 
     */
    constexpr T squared_norm() const noexcept {
        return dot(*this, *this);
    }
    /**
     * @brief 絶対値
     * 
     * @return double 
     */
    constexpr double abs() const noexcept {
        return std::sqrt(squared_norm());
    }
};

/**
 * @brief 二次元ベクトルどうしの外積(平行四辺形の符号付き面積)
 * 
 * @param lhs 
 * @param rhs 
 * @tparam T 座標の型
 * @return T 
 */
template <typename T>
constexpr T cross(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs) noexcept {
    return lhs[0] * rhs[1] - lhs[1] * rhs[0];
}
/**
 * @brief 三次元ベクトルどうしの外積
 * 
 * @param lhs 
 * @param rhs 
 * @tparam T 座標の型
 * @return Vector<T, 3> 
 */
template <typename T>
constexpr Vector<T, 3> cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept {
    Vector<T, 3> ret;
    ret[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    ret[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    ret[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return std::move(ret);
}

/**
 * @brief 線分の交差判定
 * 
 * @param p1 1本目の線分の端点1
 * @param p2 1本目の線分の端点2
 * @param q1 2本目の線分の端点1
 * @param q2 2本目の線分の端点2
 * @tparam T 座標の型
 * @return std::pair<bool, Vector<T, 2>> firstは共有点の有無、secondは共有点の1例
*/
template <typename T>
constexpr std::pair<bool, Vector<T, 2>> segment_intersect(const Vector<T, 2>& p1, const Vector<T, 2>& p2, const Vector<T, 2>& q1, const Vector<T, 2>& q2) {
    assert(p1 != p2 && q1 != q2 && "segment_intersect: degenerate segment");
    T q1_cross = cross(p2 - p1, q1 - p1);
    int q1_section = (q1_cross > 0) - (q1_cross < 0); // 直線p1p2に対してq1がどの位置にあるか
    T q2_cross = cross(p2 - p1, q2 - p1);
    int q2_section = (q2_cross > 0) - (q2_cross < 0); // 直線p1p2に対してq2がどの位置にあるか
    T p1_cross = cross(q2 - q1, p1 - q1);
    int p1_section = (p1_cross > 0) - (p1_cross < 0); // 直線q1q2に対してp1がどの位置にあるか
    T p2_cross = cross(q2 - q1, p2 - q1);
    int p2_section = (p2_cross > 0) - (p2_cross < 0); // 直線q1q2に対してp2がどの位置にあるか
    if(q1_section == 0 && q2_section == 0) {
        // 4点が同一直線上にある場合
        if(dot(q1-p1, q2-p1) <= 0) return std::make_pair(true, p1);
        if(dot(q1-p2, q2-p2) <= 0) return std::make_pair(true, p2);
        if(dot(p1-q1, p2-q1) <= 0) return std::make_pair(true, q1);
        return std::make_pair(false, Vector<T, 2>());
    }
    if(q1_section * q2_section > 0 || p1_section * p2_section > 0) return std::make_pair(false, Vector<T, 2>());
    T area = cross(p2 - p1, q2 - q1); // 4点を頂点とする四角形の符号付き面積
    T partial_area = p1_cross; // 三角形q1q2p1の符号付き面積
    Vector<T, 2> vp12 = p2 - p1; // ベクトルp1p2
    if constexpr(std::is_integral_v<T>) {
        T g = std::gcd(area, partial_area);
        area /= g; partial_area /= g;
    }
    return std::make_pair(true, p1 + vp12 * partial_area / area);
}