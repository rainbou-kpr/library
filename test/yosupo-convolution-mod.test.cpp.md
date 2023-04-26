---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cpp/convolution.hpp
    title: cpp/convolution.hpp
  - icon: ':heavy_check_mark:'
    path: cpp/modint.hpp
    title: "\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\u3067 mod\
      \ \u3092\u53D6\u308B\u30AF\u30E9\u30B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 312, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ cpp/modint.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"../cpp/convolution.hpp\"\n\nusing mint = modint998244353;\n\nint main() {\n\
    \    long long n, m, x;\n    std::cin >> n >> m;\n    std::vector<mint> a(n),\
    \ b(m);\n    for(int i = 0; i < n; ++ i) {\n        std::cin >> x;\n        a[i]\
    \ = mint(x);\n    }\n    for(int i = 0; i < m; ++ i) {\n        std::cin >> x;\n\
    \        b[i] = mint(x);\n    }\n    auto c = convolution(a, b);\n    for(auto\
    \ e : c) std::cout << e.value() << \" \";\n    std::cout << std::endl;\n\n   \
    \ return 0;\n\n}\n\n\n"
  dependsOn:
  - cpp/convolution.hpp
  - cpp/modint.hpp
  isVerificationFile: true
  path: test/yosupo-convolution-mod.test.cpp
  requiredBy: []
  timestamp: '2023-04-26 16:38:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-convolution-mod.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo-convolution-mod.test.cpp
- /verify/test/yosupo-convolution-mod.test.cpp.html
title: test/yosupo-convolution-mod.test.cpp
---
