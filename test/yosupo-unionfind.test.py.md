---
data:
  _extendedDependsOn: []
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
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://judge.yosupo.jp/problem/unionfind\n\
    from py.unionfind import UnionFind\n\nN, Q = map(int, input().split())\ng = UnionFind(N)\n\
    for i in range(Q):\n    t, u, v = map(int, input().split())\n    if t == 0:\n\
    \        g.merge(u, v)\n    else:\n        print(1 if g.same(u, v) else 0)\n"
  dependsOn: []
  isVerificationFile: true
  path: test/yosupo-unionfind.test.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-unionfind.test.py
layout: document
redirect_from:
- /verify/test/yosupo-unionfind.test.py
- /verify/test/yosupo-unionfind.test.py.html
title: test/yosupo-unionfind.test.py
---
