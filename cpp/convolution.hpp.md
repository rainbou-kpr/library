---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/modint.hpp
    title: "\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod\
      \ \u3092\u53D6\u308B\u30AF\u30E9\u30B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo-convolution-mod-1000000007.test.cpp
    title: test/yosupo-convolution-mod-1000000007.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo-convolution-mod.test.cpp
    title: test/yosupo-convolution-mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 312, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ cpp/modint.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#pragma once\n\n#include <vector>\n#include \"modint.hpp\"\n\nnamespace NTT\
    \ {\n    long long modinv(long long a, long long m) {\n        long long b = m,\
    \ u = 1, v = 0;\n        while (b) {\n            long long t = a / b;\n     \
    \       a -= t * b; std::swap(a, b);\n            u -= t * v; std::swap(u, v);\n\
    \        }\n        u %= m; \n        if (u < 0) u += m;\n        return u;\n\
    \    }\n\n    long long modpow(long long a, long long n, long long MOD) {\n  \
    \      long long res = 1;\n        a %= MOD;\n        while (n > 0) {\n      \
    \      if (n & 1) res = res * a % MOD;\n            a = a * a % MOD;\n       \
    \     n >>= 1;\n        }\n        return res;\n    }\n\n    int calc_primitive_root(int\
    \ MOD) {\n        if (MOD == 2) return 1;\n        if (MOD == 167772161) return\
    \ 3;\n        if (MOD == 469762049) return 3;\n        if (MOD == 754974721) return\
    \ 11;\n        if (MOD == 998244353) return 3;\n        int divs[20] = {};\n \
    \       divs[0] = 2;\n        int cnt = 1;\n        long long x = (MOD - 1) >>\
    \ 1;\n        while (x % 2 == 0) x >>= 1;\n        for (long long i = 3; i * i\
    \ <= x; i += 2) {\n            if (x % i == 0) {\n                divs[cnt ++]\
    \ = i;\n                while (x % i == 0) x /= i;\n            }\n        }\n\
    \        if (x > 1) divs[cnt++] = x;\n        for (int g = 2;; ++ g) {\n     \
    \       bool ok = true;\n            for (int i = 0; i < cnt; i++) {\n       \
    \         if (modpow(g, (MOD - 1) / divs[i], MOD) == 1) {\n                  \
    \  ok = false;\n                    break;\n                }\n            }\n\
    \            if (ok) return g;\n        }\n    }\n\n    int get_fft_size(int N,\
    \ int M) {\n        int size_a = 1, size_b = 1;\n        while (size_a < N) size_a\
    \ <<= 1;\n        while (size_b < M) size_b <<= 1;\n        return std::max(size_a,\
    \ size_b) << 1;\n    }\n\n    template<class mint> void trans(std::vector<mint>&\
    \ v, bool inv = false) {\n        if (v.empty()) return;\n        int N = (int)\
    \ v.size();\n        int MOD = v[0].mod();\n        int PR = calc_primitive_root(MOD);\n\
    \        static bool first = true;\n        static std::vector<long long> vbw(30),\
    \ vibw(30);\n        if (first) {\n            first = false;\n            for\
    \ (int k = 0; k < 30; ++ k) {\n                vbw[k] = modpow(PR, (MOD - 1) >>\
    \ (k + 1), MOD);\n                vibw[k] = modinv(vbw[k], MOD);\n           \
    \ }\n        }\n        for (int i = 0, j = 1; j < N - 1; ++ j) {\n          \
    \  for (int k = N >> 1; k > (i ^= k); k >>= 1);\n            if (i > j) std::swap(v[i],\
    \ v[j]);\n        }\n        for (int k = 0, t = 2; t <= N; ++ k, t <<= 1) {\n\
    \            long long bw = vbw[k];\n            if (inv) bw = vibw[k];\n    \
    \        for (int i = 0; i < N; i += t) {\n                mint w = 1;\n     \
    \           for (int j = 0; j < (t >> 1); ++ j) {\n                    int j1\
    \ = i + j, j2 = i + j + (t >> 1);\n                    mint c1 = v[j1], c2 = v[j2]\
    \ * w;\n                    v[j1] = c1 + c2;\n                    v[j2] = c1 -\
    \ c2;\n                    w *= bw;\n                }\n            }\n      \
    \  }\n        if (inv) {\n            long long invN = modinv(N, MOD);\n     \
    \       for (int i = 0; i < N; ++ i) v[i] = v[i] * invN;\n        }\n    }\n\n\
    \    static constexpr int MOD0 = 754974721;\n    static constexpr int MOD1 = 167772161;\n\
    \    static constexpr int MOD2 = 469762049;\n    using mint0 = static_modint<MOD0>;\n\
    \    using mint1 = static_modint<MOD1>;\n    using mint2 = static_modint<MOD2>;\n\
    \    static const mint1 imod0 = 95869806; // modinv(MOD0, MOD1);\n    static const\
    \ mint2 imod1 = 104391568; // modinv(MOD1, MOD2);\n    static const mint2 imod01\
    \ = 187290749; // imod1 / MOD0;\n\n    // small case (T = mint, long long)\n \
    \   template<class T> std::vector<T> naive_mul \n    (const std::vector<T>& A,\
    \ const std::vector<T>& B) {\n        if (A.empty() || B.empty()) return {};\n\
    \        int N = (int) A.size(), M = (int) B.size();\n        std::vector<T> res(N\
    \ + M - 1);\n        for (int i = 0; i < N; ++ i)\n            for (int j = 0;\
    \ j < M; ++ j)\n                res[i + j] += A[i] * B[j];\n        return res;\n\
    \    }\n};\n\n// mint\ntemplate<class mint> std::vector<mint> convolution\n(const\
    \ std::vector<mint>& A, const std::vector<mint>& B) {\n    if (A.empty() || B.empty())\
    \ return {};\n    int N = (int) A.size(), M = (int) B.size();\n    if (std::min(N,\
    \ M) < 30) return NTT::naive_mul(A, B);\n    int MOD = A[0].mod();\n    int size_fft\
    \ = NTT::get_fft_size(N, M);\n    if (MOD == 998244353) {\n        std::vector<mint>\
    \ a(size_fft), b(size_fft), c(size_fft);\n        for (int i = 0; i < N; ++i)\
    \ a[i] = A[i];\n        for (int i = 0; i < M; ++i) b[i] = B[i];\n        NTT::trans(a),\
    \ NTT::trans(b);\n        std::vector<mint> res(size_fft);\n        for (int i\
    \ = 0; i < size_fft; ++i) res[i] = a[i] * b[i];\n        NTT::trans(res, true);\n\
    \        res.resize(N + M - 1);\n        return res;\n    }\n    std::vector<NTT::mint0>\
    \ a0(size_fft, 0), b0(size_fft, 0), c0(size_fft, 0);\n    std::vector<NTT::mint1>\
    \ a1(size_fft, 0), b1(size_fft, 0), c1(size_fft, 0);\n    std::vector<NTT::mint2>\
    \ a2(size_fft, 0), b2(size_fft, 0), c2(size_fft, 0);\n    for (int i = 0; i <\
    \ N; ++ i) {\n        a0[i] = A[i].value();\n        a1[i] = A[i].value();\n \
    \       a2[i] = A[i].value();\n    }\n    for (int i = 0; i < M; ++ i) {\n   \
    \     b0[i] = B[i].value();\n        b1[i] = B[i].value();\n        b2[i] = B[i].value();\n\
    \    }\n    NTT::trans(a0), NTT::trans(a1), NTT::trans(a2), \n    NTT::trans(b0),\
    \ NTT::trans(b1), NTT::trans(b2);\n    for (int i = 0; i < size_fft; ++i) {\n\
    \        c0[i] = a0[i] * b0[i];\n        c1[i] = a1[i] * b1[i];\n        c2[i]\
    \ = a2[i] * b2[i];\n    }\n    NTT::trans(c0, true), NTT::trans(c1, true), NTT::trans(c2,\
    \ true);\n    static const mint mod0 = NTT::MOD0, mod01 = mod0 * NTT::MOD1;\n\
    \    std::vector<mint> res(N + M - 1);\n    for (int i = 0; i < N + M - 1; ++\
    \ i) {\n        int y0 = c0[i].value();\n        int y1 = (NTT::imod0 * (c1[i]\
    \ - y0)).value();\n        int y2 = (NTT::imod01 * (c2[i] - y0) - NTT::imod1 *\
    \ y1).value();\n        res[i] = mod01 * y2 + mod0 * y1 + y0;\n    }\n    return\
    \ res;\n}\n\n// long long\nstd::vector<long long> convolution_ll\n(const std::vector<long\
    \ long>& A, const std::vector<long long>& B) {\n    if (A.empty() || B.empty())\
    \ return {};\n    int N = (int) A.size(), M = (int) B.size();\n    if (std::min(N,\
    \ M) < 30) return NTT::naive_mul(A, B);\n    int size_fft = NTT::get_fft_size(N,\
    \ M);\n    std::vector<NTT::mint0> a0(size_fft, 0), b0(size_fft, 0), c0(size_fft,\
    \ 0);\n    std::vector<NTT::mint1> a1(size_fft, 0), b1(size_fft, 0), c1(size_fft,\
    \ 0);\n    std::vector<NTT::mint2> a2(size_fft, 0), b2(size_fft, 0), c2(size_fft,\
    \ 0);\n    for (int i = 0; i < N; ++ i) {\n        a0[i] = A[i];\n        a1[i]\
    \ = A[i];\n        a2[i] = A[i];\n    }\n    for (int i = 0; i < M; ++ i) {\n\
    \        b0[i] = B[i];\n        b1[i] = B[i];\n        b2[i] = B[i];\n    }\n\
    \    NTT::trans(a0), NTT::trans(a1), NTT::trans(a2), \n    NTT::trans(b0), NTT::trans(b1),\
    \ NTT::trans(b2);\n    for (int i = 0; i < size_fft; ++ i) {\n        c0[i] =\
    \ a0[i] * b0[i];\n        c1[i] = a1[i] * b1[i];\n        c2[i] = a2[i] * b2[i];\n\
    \    }\n    NTT::trans(c0, true), NTT::trans(c1, true), NTT::trans(c2, true);\n\
    \    static const long long mod0 = NTT::MOD0, mod01 = mod0 * NTT::MOD1;\n    std::vector<long\
    \ long> res(N + M - 1);\n    for (int i = 0; i < N + M - 1; ++ i) {\n        int\
    \ y0 = c0[i].value();\n        int y1 = (NTT::imod0 * (c1[i] - y0)).value();\n\
    \        int y2 = (NTT::imod01 * (c2[i] - y0) - NTT::imod1 * y1).value();\n  \
    \      res[i] = mod01 * y2 + mod0 * y1 + y0;\n    }\n    return res;\n}\n"
  dependsOn:
  - cpp/modint.hpp
  isVerificationFile: false
  path: cpp/convolution.hpp
  requiredBy: []
  timestamp: '2023-04-26 16:38:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-convolution-mod.test.cpp
  - test/yosupo-convolution-mod-1000000007.test.cpp
documentation_of: cpp/convolution.hpp
layout: document
redirect_from:
- /library/cpp/convolution.hpp
- /library/cpp/convolution.hpp.html
title: cpp/convolution.hpp
---
