---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "# verification-helper: PROBLEM https://judge.yosupo.jp/problem/shortest_path\n\
    from py.graph import Graph\n\n\ndef main():\n    n, m, s, t = map(int, input().split())\n\
    \    g = Graph(n)\n    g.read(m, 0, True, True)\n    dist, prev = g.shortest_path(s,\
    \ True)\n    if dist[t] == -1:\n        exit(print(-1))\n    route = []\n    cur\
    \ = t\n    while cur != s:\n        route.append((prev[cur].src, prev[cur].dst))\n\
    \        cur = prev[cur].src\n    print(dist[t], len(route))\n    for src, dst\
    \ in route[::-1]:\n        print(src, dst)\n\n\nif __name__ == \"__main__\":\n\
    \    main()\n"
  dependsOn: []
  isVerificationFile: true
  path: test/yosupo-shortest-path.test.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo-shortest-path.test.py
layout: document
redirect_from:
- /verify/test/yosupo-shortest-path.test.py
- /verify/test/yosupo-shortest-path.test.py.html
title: test/yosupo-shortest-path.test.py
---
