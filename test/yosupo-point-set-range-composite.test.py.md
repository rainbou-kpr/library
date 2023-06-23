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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite\n\
    import sys\ninput = sys.stdin.buffer.readline\n\nfrom py.segtree import SegTree\n\
    \n\ndef main() -> None:\n    MOD = 998244353\n    n, q = map(int, input().split())\n\
    \    v = [tuple(map(int, input().split())) for i in range(n)]\n    def op(l, r):\
    \ return (l[0]*r[0] % MOD, (r[0]*l[1]+r[1]) % MOD)\n    seg = SegTree(v, op, (1,\
    \ 0))\n    for _ in range(q):\n        query = tuple(map(int, input().split()))\n\
    \        if query[0] == 0:\n            p, c, d = query[1:]\n            seg.set(p,\
    \ (c, d))\n        else:\n            l, r, x = query[1:]\n            f = seg.prod(l,\
    \ r)\n            print((f[0]*x + f[1]) % MOD)\n    \n\n\nif __name__ == \"__main__\"\
    :\n    main()\n"
  dependsOn:
  - py/segtree.py
  isVerificationFile: true
  path: test/yosupo-point-set-range-composite.test.py
  requiredBy: []
  timestamp: '2023-05-31 01:56:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-point-set-range-composite.test.py
layout: document
redirect_from:
- /verify/test/yosupo-point-set-range-composite.test.py
- /verify/test/yosupo-point-set-range-composite.test.py.html
title: test/yosupo-point-set-range-composite.test.py
---
