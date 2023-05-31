---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: py/unionfind.py
    title: py/unionfind.py
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://judge.yosupo.jp/problem/unionfind\n\
    from py.unionfind import UnionFind\n\n\ndef main():\n    N, Q = map(int, input().split())\n\
    \    g = UnionFind(N)\n    for i in range(Q):\n        t, u, v = map(int, input().split())\n\
    \        if t == 0:\n            g.merge(u, v)\n        else:\n            print(1\
    \ if g.same(u, v) else 0)\n\n\nif __name__ == \"__main__\":\n    main()\n"
  dependsOn:
  - py/unionfind.py
  isVerificationFile: true
  path: test/yosupo-unionfind.test.py
  requiredBy: []
  timestamp: '2023-05-26 10:38:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-unionfind.test.py
layout: document
redirect_from:
- /verify/test/yosupo-unionfind.test.py
- /verify/test/yosupo-unionfind.test.py.html
title: test/yosupo-unionfind.test.py
---
