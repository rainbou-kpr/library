---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: py/linkedlist.py
    title: py/linkedlist.py
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_3_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_3_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_3_C\n\
    from py.linkedlist import LinkedList\n\n\ndef main():\n    l = LinkedList()\n\
    \    for _ in range(int(input())):\n        q = input().split()\n        if q[0]\
    \ == 'insert':\n            l.appendleft(int(q[1]))\n        elif q[0] == 'delete':\n\
    \            i = l.find(int(q[1]))\n            if i is not None:\n          \
    \      l.erase(i)\n        elif q[0] == 'deleteFirst':\n            l.popleft()\n\
    \        else:\n            l.pop()\n    print(*l.values())\n\n\nif __name__ ==\
    \ \"__main__\":\n    main()\n"
  dependsOn:
  - py/linkedlist.py
  isVerificationFile: true
  path: test/aoj-alds1-3-c.test.py
  requiredBy: []
  timestamp: '2023-09-05 02:43:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj-alds1-3-c.test.py
layout: document
redirect_from:
- /verify/test/aoj-alds1-3-c.test.py
- /verify/test/aoj-alds1-3-c.test.py.html
title: test/aoj-alds1-3-c.test.py
---
