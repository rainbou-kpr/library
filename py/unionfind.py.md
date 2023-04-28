---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "from typing import List\n\n\nclass UnionFind:\n    \"\"\"\n    \u7121\u5411\
    \u30B0\u30E9\u30D5\u306B\u5BFE\u3057\u3066\u300C\u8FBA\u306E\u8FFD\u52A0\u300D\
    \u3001\u300C2\u9802\u70B9\u304C\u9023\u7D50\u304B\u306E\u5224\u5B9A\u300D\u3092\
    \u3059\u308B\n    \"\"\"\n\n    def __init__(self, n: int) -> None:\n        \"\
    \"\"\n        \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n        :param int n:\
    \ \u9802\u70B9\u6570\n        \"\"\"\n        self._n = n\n        self.parent_or_size\
    \ = [-1]*n\n\n    def merge(self, a: int, b: int) -> int:\n        \"\"\"\n  \
    \      \u8FBA(a,b)\u3092\u8DB3\u3059\n        :return: \u9023\u7D50\u3057\u305F\
    \u3082\u306E\u306E\u4EE3\u8868\u5143\n        \"\"\"\n        assert 0 <= a <\
    \ self._n\n        assert 0 <= b < self._n\n        x = self.leader(a)\n     \
    \   y = self.leader(b)\n        if x == y:\n            return x\n        if -self.parent_or_size[x]\
    \ < -self.parent_or_size[y]:\n            x, y = y, x\n        self.parent_or_size[x]\
    \ += self.parent_or_size[y]\n        self.parent_or_size[y] = x\n        return\
    \ x\n\n    def same(self, a: int, b: int) -> bool:\n        \"\"\"\n        \u9802\
    \u70B9a,b\u304C\u9023\u7D50\u304B\u3069\u3046\u304B\n        \"\"\"\n        assert\
    \ 0 <= a < self._n\n        assert 0 <= b < self._n\n        return self.leader(a)\
    \ == self.leader(b)\n\n    def leader(self, a: int) -> int:\n        \"\"\"\n\
    \        \u9802\u70B9a\u306E\u5C5E\u3059\u308B\u9023\u7D50\u6210\u5206\u306E\u4EE3\
    \u8868\u5143\n        \"\"\"\n        assert 0 <= a < self._n\n        if self.parent_or_size[a]\
    \ < 0:\n            return a\n        x = a\n        while self.parent_or_size[x]\
    \ >= 0:\n            x = self.parent_or_size[x]\n        while self.parent_or_size[a]\
    \ >= 0:\n            self.parent_or_size[a], a = x, self.parent_or_size[a]\n \
    \       return x\n\n    def size(self, a: int) -> int:\n        \"\"\"\n     \
    \   \u9802\u70B9a\u306E\u5C5E\u3059\u308B\u9023\u7D50\u6210\u5206\u306E\u30B5\u30A4\
    \u30BA\n        \"\"\"\n        assert 0 <= a < self._n\n        return -self.parent_or_size[self.leader(a)]\n\
    \n    def groups(self) -> List[List[int]]:\n        \"\"\"\n        \u30B0\u30E9\
    \u30D5\u3092\u9023\u7D50\u6210\u5206\u306B\u5206\u3051\u3001\u305D\u306E\u60C5\
    \u5831\u3092\u8FD4\u3059\n        :return: \u300C\u4E00\u3064\u306E\u9023\u7D50\
    \u6210\u5206\u306E\u9802\u70B9\u756A\u53F7\u306E\u30EA\u30B9\u30C8\u300D\u306E\
    \u30EA\u30B9\u30C8\n        \"\"\"\n        leader_buf = [0]*self._n\n       \
    \ group_size = [0]*self._n\n        for i in range(self._n):\n            leader_buf[i]\
    \ = self.leader(i)\n            group_size[leader_buf[i]] += 1\n        result\
    \ = [[] for i in range(self._n)]\n        for i in range(self._n):\n         \
    \   result[leader_buf[i]].append(i)\n        return [l for l in result if l]\n"
  dependsOn: []
  isVerificationFile: false
  path: py/unionfind.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: py/unionfind.py
layout: document
redirect_from:
- /library/py/unionfind.py
- /library/py/unionfind.py.html
title: py/unionfind.py
---
