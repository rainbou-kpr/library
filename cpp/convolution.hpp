#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace NTT {
    int calc_primitive_root(int mod) {
        if (mod == 2) return 1;
        if (mod == 167772161) return 3;
        if (mod == 469762049) return 3;
        if (mod == 754974721) return 11;
        if (mod == 998244353) return 3;
        int divs[20] = {};
        divs[0] = 2;
        int cnt = 1;
        long long x = (mod - 1) / 2;
        while (x % 2 == 0) x /= 2;
        for (long long i = 3; i * i <= x; i += 2) {
            if (x % i == 0) {
                divs[cnt++] = i;
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) divs[cnt++] = x;
        for (int g = 2;; g++) {
            bool ok = true;
            for (int i = 0; i < cnt; i++) {
                if (modpow(g, (mod - 1) / divs[i], mod) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
    }

    int get_fft_size(int N, int M) {
        int size_a = 1, size_b = 1;
        while (size_a < N) size_a <<= 1;
        while (size_b < M) size_b <<= 1;
        return max(size_a, size_b) << 1;
    }

    // number-theoretic transform
    template<class mint> void trans(vector<mint>& v, bool inv = false) {
        if (v.empty()) return;
        int N = (int)v.size();
        int MOD = v[0].getmod();
        int PR = calc_primitive_root(MOD);
        static bool first = true;
        static vector<long long> vbw(30), vibw(30);
        if (first) {
            first = false;
            for (int k = 0; k < 30; ++k) {
                vbw[k] = modpow(PR, (MOD - 1) >> (k + 1), MOD);
                vibw[k] = modinv(vbw[k], MOD);
            }
        }
        for (int i = 0, j = 1; j < N - 1; j++) {
            for (int k = N >> 1; k > (i ^= k); k >>= 1);
            if (i > j) swap(v[i], v[j]);
        }
        for (int k = 0, t = 2; t <= N; ++k, t <<= 1) {
            long long bw = vbw[k];
            if (inv) bw = vibw[k];
            for (int i = 0; i < N; i += t) {
                mint w = 1;
                for (int j = 0; j < t/2; ++j) {
                    int j1 = i + j, j2 = i + j + t/2;
                    mint c1 = v[j1], c2 = v[j2] * w;
                    v[j1] = c1 + c2;
                    v[j2] = c1 - c2;
                    w *= bw;
                }
            }
        }
        if (inv) {
            long long invN = modinv(N, MOD);
            for (int i = 0; i < N; ++i) v[i] = v[i] * invN;
        }
    }

    // for garner
    static constexpr int MOD0 = 754974721;
    static constexpr int MOD1 = 167772161;
    static constexpr int MOD2 = 469762049;
    using mint0 = Modint<MOD0>;
    using mint1 = Modint<MOD1>;
    using mint2 = Modint<MOD2>;
    static const mint1 imod0 = 95869806; // modinv(MOD0, MOD1);
    static const mint2 imod1 = 104391568; // modinv(MOD1, MOD2);
    static const mint2 imod01 = 187290749; // imod1 / MOD0;

    // small case (T = mint, long long)
    template<class T> vector<T> naive_mul 
    (const vector<T>& A, const vector<T>& B) {
        if (A.empty() || B.empty()) return {};
        int N = (int)A.size(), M = (int)B.size();
        vector<T> res(N + M - 1);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                res[i + j] += A[i] * B[j];
        return res;
    }
};

// mint
template<class mint> vector<mint> convolution
(const vector<mint>& A, const vector<mint>& B) {
    if (A.empty() || B.empty()) return {};
    int N = (int)A.size(), M = (int)B.size();
    if (min(N, M) < 30) return NTT::naive_mul(A, B);
    int MOD = A[0].getmod();
    int size_fft = NTT::get_fft_size(N, M);
    if (MOD == 998244353) {
        vector<mint> a(size_fft), b(size_fft), c(size_fft);
        for (int i = 0; i < N; ++i) a[i] = A[i];
        for (int i = 0; i < M; ++i) b[i] = B[i];
        NTT::trans(a), NTT::trans(b);
        vector<mint> res(size_fft);
        for (int i = 0; i < size_fft; ++i) res[i] = a[i] * b[i];
        NTT::trans(res, true);
        res.resize(N + M - 1);
        return res;
    }
    vector<NTT::mint0> a0(size_fft, 0), b0(size_fft, 0), c0(size_fft, 0);
    vector<NTT::mint1> a1(size_fft, 0), b1(size_fft, 0), c1(size_fft, 0);
    vector<NTT::mint2> a2(size_fft, 0), b2(size_fft, 0), c2(size_fft, 0);
    for (int i = 0; i < N; ++i)
        a0[i] = A[i].val, a1[i] = A[i].val, a2[i] = A[i].val;
    for (int i = 0; i < M; ++i)
        b0[i] = B[i].val, b1[i] = B[i].val, b2[i] = B[i].val;
    NTT::trans(a0), NTT::trans(a1), NTT::trans(a2), 
    NTT::trans(b0), NTT::trans(b1), NTT::trans(b2);
    for (int i = 0; i < size_fft; ++i) {
        c0[i] = a0[i] * b0[i];
        c1[i] = a1[i] * b1[i];
        c2[i] = a2[i] * b2[i];
    }
    NTT::trans(c0, true), NTT::trans(c1, true), NTT::trans(c2, true);
    static const mint mod0 = NTT::MOD0, mod01 = mod0 * NTT::MOD1;
    vector<mint> res(N + M - 1);
    for (int i = 0; i < N + M - 1; ++i) {
        int y0 = c0[i].val;
        int y1 = (NTT::imod0 * (c1[i] - y0)).val;
        int y2 = (NTT::imod01 * (c2[i] - y0) - NTT::imod1 * y1).val;
        res[i] = mod01 * y2 + mod0 * y1 + y0;
    }
    return res;
}

// long long
vector<long long> convolution_ll
(const vector<long long>& A, const vector<long long>& B) {
    if (A.empty() || B.empty()) return {};
    int N = (int)A.size(), M = (int)B.size();
    if (min(N, M) < 30) return NTT::naive_mul(A, B);
    int size_fft = NTT::get_fft_size(N, M);
    vector<NTT::mint0> a0(size_fft, 0), b0(size_fft, 0), c0(size_fft, 0);
    vector<NTT::mint1> a1(size_fft, 0), b1(size_fft, 0), c1(size_fft, 0);
    vector<NTT::mint2> a2(size_fft, 0), b2(size_fft, 0), c2(size_fft, 0);
    for (int i = 0; i < N; ++i)
        a0[i] = A[i], a1[i] = A[i], a2[i] = A[i];
    for (int i = 0; i < M; ++i)
        b0[i] = B[i], b1[i] = B[i], b2[i] = B[i];
    NTT::trans(a0), NTT::trans(a1), NTT::trans(a2), 
    NTT::trans(b0), NTT::trans(b1), NTT::trans(b2);
    for (int i = 0; i < size_fft; ++i) {
        c0[i] = a0[i] * b0[i];
        c1[i] = a1[i] * b1[i];
        c2[i] = a2[i] * b2[i];
    }
    NTT::trans(c0, true), NTT::trans(c1, true), NTT::trans(c2, true);
    static const long long mod0 = NTT::MOD0, mod01 = mod0 * NTT::MOD1;
    vector<long long> res(N + M - 1);
    for (int i = 0; i < N + M - 1; ++i) {
        int y0 = c0[i].val;
        int y1 = (NTT::imod0 * (c1[i] - y0)).val;
        int y2 = (NTT::imod01 * (c2[i] - y0) - NTT::imod1 * y1).val;
        res[i] = mod01 * y2 + mod0 * y1 + y0;
    }
    return res;
}

// depends on {modint.cpp, modpow_modinv.cpp}