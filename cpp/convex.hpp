#pragma once
#include <cassert>
#include <vector>
#include <functional>
#include <stack>
#include <type_traits>
#include <optional>

/**
 * @brief monotoneな行列において、各行の最小値を取る最小列番号を$O((H+W)\log H)$時間で得る
 * @param h 行数(行番号は[0..h-1])
 * @param w 列数(列番号は[0..w-1])
 * @param f 行列の要素を与える関数(行番号と列番号を引数にとって値を返す)
 * @param comp 要素の比較関数(最小値を知りたい場合はデフォルトのstd::less<T>)
 * @return std::vector<int> 各行の最小値列番号
 */
template <typename F, typename Comp = std::less<std::invoke_result_t<F, int, int>>>
std::vector<int> monotone_minima(int h, int w, const F& f, const Comp& comp = Comp()) {
    using T = std::invoke_result_t<F, int, int>;
    assert(h >= 0);
    assert(w >= 0);
    std::vector<int> res(h);
    std::stack<std::tuple<int, int, int, int>> stk; // {i, j, l, r} : [i..j]行目の答えを求める。結果は[l..r]の範囲に収まることが保証されている。
    stk.emplace(0, h-1, 0, w-1);
    while(!stk.empty()) {
        auto [i, j, l, r] = stk.top(); stk.pop();
        int m = (i+j) / 2;
        T min_value = f(m, l);
        int min_idx = l;
        for(int k = l+1; k <= r; k++) {
            T value = f(m, k);
            if(comp(value, min_value)) {
                min_value = value;
                min_idx = k;
            }
        }
        res[m] = min_idx;
        if(i <= m-1) stk.emplace(i, m-1, l, min_idx);
        if(m+1 <= j) stk.emplace(m+1, j, min_idx, r);
    }
    return res;
}

/**
 * @brief オンライン・オフライン変換による、DAGで辺のコストがmonotoneな場合の最短経路問題
 * @param n ノード数-1 (ノード番号は[0..n])
 * @param f 辺のコスト(i<jのときf(i, j)が辺のコストを返す)
 * @param comp 比較関数
 * @return 頂点0から頂点[0..n]へのコストを表す長さn+1のvector
 */
template <typename F, typename Comp = std::less<std::invoke_result_t<F, int, int>>>
std::vector<std::invoke_result_t<F, int, int>> online_offline_dp(int n, const F& f, const Comp& comp = Comp{}) {
    using T = std::invoke_result_t<F, int, int>;
    std::vector<std::optional<T>> dp(n+1, std::nullopt);
    dp[0] = 0;
    // dp[l..r)の要素を、dp[l..r)からの遷移のみの範囲で求める
    auto solve_subproblem = [&](auto self, int l, int r) -> void {
        int mid = (l+r) / 2;
        if(mid-l >= 2) self(self, l, mid);
        auto submat = [&](int i, int j) {
            return dp[l+j].value() + f(l+j, mid+i);
        };
        std::vector<int> min_idx = monotone_minima(r-mid, mid-l, submat, comp);
        for(int i = 0; i < r-mid; i++) {
            T val = submat(i, min_idx[i]);
            if(!dp[mid+i] || comp(val, dp[mid+i].value())) {
                dp[mid+i] = val;
            }
        }
        if(r-mid >= 2) self(self, mid, r);
    };
    solve_subproblem(solve_subproblem, 0, n+1);
    std::vector<T> res(n+1);
    for(int i = 0; i <= n; i++) res[i] = dp[i].value();
    return res;
}
