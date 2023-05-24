---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: py/sqrt.py
    title: py/sqrt.py
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_quotients
    links:
    - https://judge.yosupo.jp/problem/enumerate_quotients
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://judge.yosupo.jp/problem/enumerate_quotients\n\
    import sys\ninput = sys.stdin.buffer.readline\n\nfrom py.sqrt import isqrt\n\n\
    \ndef main() -> None:\n    n = int(input())\n    v1 = []\n    v2 = []\n    m =\
    \ isqrt(n)\n    for i in range(1, m+1):\n        v1.append(n//i)\n        v2.append(i)\n\
    \    if(v1[-1] == v2[-1]):\n        v1.pop()\n    v1.reverse()\n    print(len(v1)+len(v2))\n\
    \    print(*(v2+v1))\n\n\nif __name__ == \"__main__\":\n    main()\n"
  dependsOn:
  - py/sqrt.py
  isVerificationFile: true
  path: test/yosupo-enumerate-quotients.test.py
  requiredBy: []
  timestamp: '2023-05-23 13:25:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-enumerate-quotients.test.py
layout: document
redirect_from:
- /verify/test/yosupo-enumerate-quotients.test.py
- /verify/test/yosupo-enumerate-quotients.test.py.html
title: test/yosupo-enumerate-quotients.test.py
---
