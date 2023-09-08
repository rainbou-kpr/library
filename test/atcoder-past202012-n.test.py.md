---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: py/segtree.py
    title: py/segtree.py
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    PROBLEM: https://atcoder.jp/contests/past202012-open/tasks/past202012_n
    links:
    - https://atcoder.jp/contests/past202012-open/tasks/past202012_n
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://atcoder.jp/contests/past202012-open/tasks/past202012_n\n\
    from py.segtree import SegTree\n\nN, Q = map(int, input().split())\nlr = [tuple(map(int,\
    \ input().split())) for i in range(N-1)]\nseg = SegTree(lr, lambda a, b: (max(a[0],\
    \ b[0]), min(a[1], b[1])), (0, 10**9))\nfor i in range(Q):\n    a, b = map(int,\
    \ input().split())\n    b -= 1\n    r = seg.max_right(b, lambda x: x[0] <= a <=\
    \ x[1])\n    l = seg.min_left(b, lambda x: x[0] <= a <= x[1])\n    print(r-l+1)\n"
  dependsOn:
  - py/segtree.py
  isVerificationFile: true
  path: test/atcoder-past202012-n.test.py
  requiredBy: []
  timestamp: '2023-09-07 14:26:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/atcoder-past202012-n.test.py
layout: document
redirect_from:
- /verify/test/atcoder-past202012-n.test.py
- /verify/test/atcoder-past202012-n.test.py.html
title: test/atcoder-past202012-n.test.py
---
