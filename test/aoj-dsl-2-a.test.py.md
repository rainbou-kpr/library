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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A\n\
    import sys\ninput = sys.stdin.buffer.readline\n\nfrom py.segtree import RMinQ\n\
    \n\ndef main() -> None:\n    n, q = map(int, input().split())\n    seg = RMinQ(n,\
    \ 2**31-1)\n    for _ in range(q):\n        com, x, y = map(int, input().split())\n\
    \        if com == 0:\n            seg.set(x, y)\n        else:\n            print(seg.prod(x,\
    \ y+1))\n\n\nif __name__ == \"__main__\":\n    main()\n"
  dependsOn:
  - py/segtree.py
  isVerificationFile: true
  path: test/aoj-dsl-2-a.test.py
  requiredBy: []
  timestamp: '2023-05-31 01:56:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj-dsl-2-a.test.py
layout: document
redirect_from:
- /verify/test/aoj-dsl-2-a.test.py
- /verify/test/aoj-dsl-2-a.test.py.html
title: test/aoj-dsl-2-a.test.py
---
