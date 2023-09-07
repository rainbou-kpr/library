---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo-enumerate-quotients.test.py
    title: test/yosupo-enumerate-quotients.test.py
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "def isqrt(n: int) -> int:\n    \"\"\"\n    floor(sqrt(n))\n    :param int\
    \ n: \u5E73\u65B9\u6839\u3092\u6C42\u3081\u305F\u3044\u975E\u8CA0\u6574\u6570\n\
    \    :rtype: int\n    \"\"\"\n    # python3.8\u4EE5\u4E0A\u3067\u306Fmath.isqrt\u3092\
    \u63A8\u5968\n    le = 0\n    ri = 1\n    while n >= ri*ri:\n        ri <<= 1\n\
    \    le = ri // 2\n    while ri-le > 1:\n        mid = (le+ri)//2\n        if\
    \ mid*mid <= n:\n            le = mid\n        else:\n            ri = mid\n \
    \   return le\n"
  dependsOn: []
  isVerificationFile: false
  path: py/sqrt.py
  requiredBy: []
  timestamp: '2023-05-19 22:21:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-enumerate-quotients.test.py
documentation_of: py/sqrt.py
layout: document
redirect_from:
- /library/py/sqrt.py
- /library/py/sqrt.py.html
title: py/sqrt.py
---
