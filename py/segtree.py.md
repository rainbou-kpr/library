---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-a.test.py
    title: test/aoj-dsl-2-a.test.py
  - icon: ':heavy_check_mark:'
    path: test/aoj-dsl-2-b.test.py
    title: test/aoj-dsl-2-b.test.py
  - icon: ':heavy_check_mark:'
    path: test/atcoder-past202012-n.test.py
    title: test/atcoder-past202012-n.test.py
  - icon: ':heavy_check_mark:'
    path: test/yosupo-point-set-range-composite.test.py
    title: test/yosupo-point-set-range-composite.test.py
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "from typing import Generic, TypeVar, Callable, List, Union\n\nS = TypeVar('S')\n\
    \n\nclass SegTree(Generic[S]):\n    \"\"\"\n    \u30BB\u30B0\u30E1\u30F3\u30C8\
    \u6728\n    \"\"\"\n\n    def __init__(self, n_or_v: Union[int, List[S]], op:\
    \ Callable[[S, S], S], e: S) -> None:\n        \"\"\"\n        \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n        :type S: \u8981\u7D20\u306Etype\n        :param\
    \ int | List[S] n_or_v: \u8981\u7D20\u6570 or \u521D\u671F\u306E\u8981\u7D20\u306E\
    \u30EA\u30B9\u30C8\n        :param Callable[[S, S], S] op: \u7A4D\u306E\u95A2\u6570\
    \n        :param S e: \u7A4D\u306E\u5358\u4F4D\u5143\n        \"\"\"\n       \
    \ if type(n_or_v) is int:\n            self.n = n_or_v\n            self.op =\
    \ op\n            self.e = e\n            self.sz = 1\n            self.height\
    \ = 0\n            while self.sz < self.n:\n                self.sz <<= 1\n  \
    \              self.height += 1\n            self.data = [e for i in range(self.sz*2)]\n\
    \        elif type(n_or_v) is list:\n            self.n = len(n_or_v)\n      \
    \      self.op = op\n            self.e = e\n            self.sz = 1\n       \
    \     self.height = 0\n            while self.sz < self.n:\n                self.sz\
    \ <<= 1\n                self.height += 1\n            self.data = [e for i in\
    \ range(self.sz*2)]\n            for i in range(self.n):\n                self.data[self.sz+i]\
    \ = n_or_v[i]\n            for i in range(self.sz-1, 0, -1):\n               \
    \ self.__update(i)\n        else:\n            return TypeError\n\n    def __update(self,\
    \ k: int) -> None:\n        self.data[k] = self.op(self.data[2*k], self.data[2*k+1])\n\
    \n    def get(self, k: int) -> S:\n        \"\"\"\n        \u6307\u5B9A\u3055\u308C\
    \u305F\u8981\u7D20\u306E\u5024\u3092\u8FD4\u3059\n        :param int k: \u30A4\
    \u30F3\u30C7\u30C3\u30AF\u30B9\n        :return S: \u5024\n        \"\"\"\n  \
    \      return self.data[self.sz+k]\n\n    def __getitem__(self, k: int) -> S:\n\
    \        \"\"\"\n        \u6307\u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\
    \u3092\u8FD4\u3059\n        :param int k: \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\
    \n        :return S: \u5024\n        \"\"\"\n        return self.get(k)\n\n  \
    \  def set(self, k: int, x: S) -> None:\n        \"\"\"\n        \u6307\u5B9A\u3055\
    \u308C\u305F\u8981\u7D20\u306E\u5024\u3092x\u306B\u66F4\u65B0\u3059\u308B\n  \
    \      :param int k: \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n        :param S x:\
    \ \u65B0\u3057\u3044\u5024\n        \"\"\"\n        k += self.sz\n        self.data[k]\
    \ = x\n        for i in range(1, self.height+1):\n            self.__update(k\
    \ >> i)\n\n    def __setitem__(self, k: int, x: S):\n        \"\"\"\n        \u6307\
    \u5B9A\u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u3092x\u306B\u66F4\u65B0\u3059\
    \u308B\n        :param int k: \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n        :param\
    \ S x: \u65B0\u3057\u3044\u5024\n        \"\"\"\n        self.set(k, x)\n\n  \
    \  def apply(self, k: int, x: S) -> None:\n        \"\"\"\n        \u6307\u5B9A\
    \u3055\u308C\u305F\u8981\u7D20\u306E\u5024\u306Bx\u3092\u4F5C\u7528\u3055\u305B\
    \u308B\n        :param int k: \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n        :param\
    \ S x: \u4F5C\u7528\u7D20\n        \"\"\"\n        self.set(k, self.op(self.get(k),\
    \ x))\n\n    def prod(self, l: int, r: int) -> S:\n        \"\"\"\n        [l,\
    \ r)\u306E\u533A\u9593\u306E\u7DCF\u7A4D\u3092\u8FD4\u3059\n        :param int\
    \ l: \u534A\u958B\u533A\u9593\u306E\u958B\u59CB\n        :param int r: \u534A\u58CA\
    \u533A\u9593\u306E\u7D42\u7AEF\n        :return S: \u7DCF\u7A4D\n        \"\"\"\
    \n        left_prod = self.e\n        right_prod = self.e\n        l += self.sz\n\
    \        r += self.sz\n        while l < r:\n            if l & 1 == 1:\n    \
    \            left_prod = self.op(left_prod, self.data[l])\n                l +=\
    \ 1\n            if r & 1 == 1:\n                r -= 1\n                right_prod\
    \ = self.op(self.data[r], right_prod)\n            l >>= 1\n            r >>=\
    \ 1\n        return self.op(left_prod, right_prod)\n\n    def all_prod(self) ->\
    \ S:\n        \"\"\"\n        \u3059\u3079\u3066\u306E\u8981\u7D20\u306E\u7DCF\
    \u7A4D\u3092\u8FD4\u3059\n        :return S: \u7DCF\u7A4D\n        \"\"\"\n  \
    \      return self.data[1]\n\n    def max_right(self, l: int, f: Callable[[S],\
    \ bool]) -> int:\n        \"\"\"\n        (r = l or f(prod([l, r))) = True) and\
    \ (r = n or f(prod([l, r+1))) = False)\u3068\u306A\u308Br\u3092\u8FD4\u3059\u3002\
    \n        f\u304C\u5358\u8ABF\u306A\u3089\u3001f(prod([l, r))) = True\u3068\u306A\
    \u308B\u6700\u5927\u306Er\u3068\u306A\u308B\u3002\n        :param l: \u534A\u958B\
    \u533A\u9593\u306E\u958B\u59CB\n        :param f: \u5224\u5B9A\u95A2\u6570\n \
    \       :return int: r\n        \"\"\"\n        assert f(self.e)\n        if l\
    \ == self.n:\n            return self.n\n        l += self.sz\n        while l\
    \ % 2 == 0:\n            l >>= 1\n        sm = self.e\n        while f(self.op(sm,\
    \ self.data[l])):\n            sm = self.op(sm, self.data[l])\n            l +=\
    \ 1\n            while l % 2 == 0:\n                l >>= 1\n            if l\
    \ == 1:\n                return self.n\n        while l < self.sz:\n         \
    \   if not f(self.op(sm, self.data[l*2])):\n                l *= 2\n         \
    \   else:\n                sm = self.op(sm, self.data[l*2])\n                l\
    \ = l*2+1\n        return l-self.sz\n\n    def min_left(self, r: int, f: Callable[[S],\
    \ bool]) -> int:\n        \"\"\"\n        (l = 0 or f(prod([l, r))) = True) and\
    \ (l = r or f(prod([l-1, r))) = False)\u3068\u306A\u308Bl\u3092\u8FD4\u3059\u3002\
    \n        f\u304C\u5358\u8ABF\u306A\u3089\u3001f(prod([l, r))) = True\u3068\u306A\
    \u308B\u6700\u5C0F\u306El\u3068\u306A\u308B\u3002\n        :param r: \u534A\u958B\
    \u533A\u9593\u306E\u7D42\u7AEF\n        :param f: \u5224\u5B9A\u95A2\u6570\n \
    \       :return int: l\n        \"\"\"\n        assert f(self.e)\n        if r\
    \ == 0:\n            return 0\n        r += self.sz\n        while r % 2 == 0:\n\
    \            r >>= 1\n        sm = self.e\n        while f(self.op(self.data[r-1],\
    \ sm)):\n            sm = self.op(self.data[r-1], sm)\n            r -= 1\n  \
    \          while r % 2 == 0:\n                r >>= 1\n            if r == 1:\n\
    \                return 0\n        while r < self.sz:\n            if not f(self.op(self.data[r*2-1],\
    \ sm)):\n                r = r*2\n            else:\n                sm = self.op(self.data[r*2-1],\
    \ sm)\n                r = r*2-1\n        return r-self.sz\n\n    def __str__(self)\
    \ -> str:\n        re: List[str] = []\n        for i in range(self.n):\n     \
    \       re.append(str(self.data[i+self.sz]))\n        return ' '.join(re)\n\n\n\
    class RMaxQ(SegTree, Generic[S]):\n    def __init__(self, n_or_v: Union[int, List[S]],\
    \ init: S = -float('inf')) -> None:\n        \"\"\"\n        \u30B3\u30F3\u30B9\
    \u30C8\u30E9\u30AF\u30BF\n        :type S: \u8981\u7D20\u306Etype\n        :param\
    \ int | List[S] n_or_v: \u8981\u7D20\u6570 or \u521D\u671F\u306E\u8981\u7D20\u306E\
    \u30EA\u30B9\u30C8\n        :param S init: \u5358\u4F4D\u5143 \u30C7\u30D5\u30A9\
    \u30EB\u30C8\u306F-float('inf') \u3053\u308C\u3068\u6BD4\u8F03\u6F14\u7B97\u3067\
    \u304D\u308B\u306A\u3089\u3070S\u306F\u4ED6\u306Etype(int\u306A\u3069)\u3067\u3082\
    \u304B\u307E\u308F\u306A\u3044\n        \"\"\"\n        super().__init__(n_or_v,\
    \ lambda x, y: x if x > y else y, init)\n\n\nclass RMinQ(SegTree, Generic[S]):\n\
    \    def __init__(self, n_or_v: Union[int, List[S]], init: S = float('inf')) ->\
    \ None:\n        \"\"\"\n        \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n\
    \        :type S: \u8981\u7D20\u306Etype\n        :param int | List[S] n_or_v:\
    \ \u8981\u7D20\u6570 or \u521D\u671F\u306E\u8981\u7D20\u306E\u30EA\u30B9\u30C8\
    \n        :param S init: \u5358\u4F4D\u5143 \u30C7\u30D5\u30A9\u30EB\u30C8\u306F\
    float('inf') \u3053\u308C\u3068\u6BD4\u8F03\u6F14\u7B97\u3067\u304D\u308B\u306A\
    \u3089\u3070S\u306F\u4ED6\u306Etype(int\u306A\u3069)\u3067\u3082\u304B\u307E\u308F\
    \u306A\u3044\n        \"\"\"\n        super().__init__(n_or_v, lambda x, y: x\
    \ if x < y else y, init)\n\n\nclass RSumQ(SegTree, Generic[S]):\n    def __init__(self,\
    \ n_or_v: Union[int, List[S]], init: S = 0) -> None:\n        \"\"\"\n       \
    \ \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n        :type S: \u8981\u7D20\u306E\
    type\n        :param int | List[S] n_or_v: \u8981\u7D20\u6570 or \u521D\u671F\u306E\
    \u8981\u7D20\u306E\u30EA\u30B9\u30C8\n        :param S init: \u5358\u4F4D\u5143\
    \ \u30C7\u30D5\u30A9\u30EB\u30C8\u306F0\n        \"\"\"\n        super().__init__(n_or_v,\
    \ lambda x, y: x+y, init)\n"
  dependsOn: []
  isVerificationFile: false
  path: py/segtree.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/atcoder-past202012-n.test.py
  - test/aoj-dsl-2-a.test.py
  - test/yosupo-point-set-range-composite.test.py
  - test/aoj-dsl-2-b.test.py
documentation_of: py/segtree.py
layout: document
redirect_from:
- /library/py/segtree.py
- /library/py/segtree.py.html
title: py/segtree.py
---
