---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo-shortest-path.test.py
    title: test/yosupo-shortest-path.test.py
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "from typing import List, Tuple, Generic, TypeVar\nfrom collections import\
    \ deque\nimport heapq\n\nCost = TypeVar('Cost')\n\nclass Graph(Generic[Cost]):\n\
    \    \"\"\"\n    \u30B0\u30E9\u30D5\u306E\u6C4E\u7528\u30AF\u30E9\u30B9\n    \"\
    \"\"\n    class Edge:\n        \"\"\"\n        \u30B0\u30E9\u30D5\u306E\u8FBA\u3092\
    \u8868\u3059\u30AF\u30E9\u30B9\n        \"\"\"\n        def __init__(self, src:\
    \ int, dst: int, cost: Cost, id: int):\n            self.src = src\n         \
    \   self.dst = dst\n            self.cost = cost\n            self.id = id\n \
    \       def __int__(self):\n            return self.dst\n\n    def __init__(self,\
    \ n: int):\n        \"\"\"\n        \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\
    \n        :param int n: \u9802\u70B9\u6570\n        :rtype: None\n        \"\"\
    \"\n        self.n = n\n        self.m = 0\n        self.g = [[] for _ in range(n)]\n\
    \    def add_edge(self, u: int, v: int, w: Cost=1):\n        \"\"\"\n        \u7121\
    \u5411\u8FBA\u3092\u8FFD\u52A0\u3059\u308B\n        :param int u: \u59CB\u70B9\
    \n        :param int v: \u7D42\u70B9\n        :param int w: \u30B3\u30B9\u30C8\
    \ \u7701\u7565\u3057\u305F\u30891\n        :rtype: None\n        \"\"\"\n    \
    \    self.g[u].append(self.Edge(u, v, w, self.m))\n        self.g[v].append(self.Edge(v,\
    \ u, w, self.m))\n        self.m += 1\n    def add_directed_edge(self, u: int,\
    \ v: int, w: Cost=1):\n        \"\"\"\n        \u6709\u5411\u8FBA\u3092\u8FFD\u52A0\
    \u3059\u308B\n        :param int u: \u59CB\u70B9\n        :param int v: \u7D42\
    \u70B9\n        :param Cost w: \u30B3\u30B9\u30C8 \u7701\u7565\u3057\u305F\u3089\
    1\n        :rtype: None\n        \"\"\"\n        self.g[u].append(self.Edge(u,\
    \ v, w, self.m))\n        self.m += 1\n    def read(self, m: int, padding: int=-1,\
    \ weighted: bool=False, directed: bool=False):\n        \"\"\"\n        \u8FBA\
    \u306E\u60C5\u5831\u3092\u6A19\u6E96\u5165\u529B\u304B\u3089\u53D7\u3051\u53D6\
    \u3063\u3066\u8FFD\u52A0\u3059\u308B\n        :param int m: \u8FBA\u306E\u6570\
    \n        :param int padding: \u9802\u70B9\u756A\u53F7\u3092\u5165\u529B\u304B\
    \u3089\u3044\u304F\u3064\u305A\u3089\u3059\u304B \u7701\u7565\u3057\u305F\u3089\
    -1\n        :param bool weighted: \u8FBA\u306E\u91CD\u307F\u304C\u5165\u529B\u3055\
    \u308C\u308B\u304B \u7701\u7565\u3057\u305F\u3089false\u3068\u306A\u308A\u3001\
    \u91CD\u307F1\u3067\u8FBA\u304C\u8FFD\u52A0\u3055\u308C\u308B\n        :param\
    \ bool directed: \u6709\u5411\u30B0\u30E9\u30D5\u304B\u3069\u3046\u304B \u7701\
    \u7565\u3057\u305F\u3089false\n        :rtype: None\n        \"\"\"\n        for\
    \ _ in range(m):\n            if weighted:\n                u, v, c = map(int,\
    \ input().split())\n            else:\n                u, v = map(int, input().split())\n\
    \                c = 1\n            u += padding\n            v += padding\n \
    \           if directed:\n                self.add_directed_edge(u, v, c)\n  \
    \          else:\n                self.add_edge(u, v, c)\n    def __getitem__(self,\
    \ v: int) -> List[Edge]:\n        \"\"\"\n        \u3042\u308B\u9802\u70B9\u304B\
    \u3089\u51FA\u308B\u8FBA\u3092\u5217\u6319\u3059\u308B\n        :param int v:\
    \ \u9802\u70B9\u756A\u53F7\n        :return: v\u304B\u3089\u51FA\u308B\u8FBA\u306E\
    \u30EA\u30B9\u30C8\n        :rtype: List[Edge]\n        \"\"\"\n        return\
    \ self.g[v]\n    def shortest_path(self, s: int, weighted: bool = True, inf: Cost=-1)\
    \ -> Tuple[List[Cost], List[Edge]]:\n        \"\"\"\n        \u3042\u308B\u9802\
    \u70B9\u304B\u3089\u5404\u9802\u70B9\u3078\u306E\u6700\u77ED\u8DEF\n        :param\
    \ int s: \u59CB\u70B9\n        :param int weighted: 1\u4EE5\u5916\u306E\u30B3\u30B9\
    \u30C8\u306E\u8FBA\u304C\u5B58\u5728\u3059\u308B\u304B \u7701\u7565\u3059\u308B\
    \u3068true\n        :param Cost inf: \u30B3\u30B9\u30C8\u306Emin\u306E\u5358\u4F4D\
    \u5143 \u672A\u5230\u9054\u306E\u9802\u70B9\u3078\u306E\u8DDD\u96E2\u306Finf\u306B\
    \u306A\u308B \u7701\u7565\u3059\u308B\u30682**31-1\n        :return: (\u5404\u9802\
    \u70B9\u3078\u306E\u6700\u77ED\u8DEF\u9577, \u5404\u9802\u70B9\u3078\u306E\u6700\
    \u77ED\u8DEF\u4E0A\u306E\u76F4\u524D\u306E\u8FBA)\n        :rtype: Tuple[List[Cost],\
    \ List[Edge]]\n        \"\"\"\n        if weighted:\n            return self.__shortest_path_dijkstra(s,\
    \ inf)\n        else:\n            return self.__shortest_path_bfs(s, inf)\n \
    \   def __shortest_path_bfs(self, s: int, inf: Cost) -> Tuple[List[int], List[Edge]]:\n\
    \        dist = [inf] * self.n\n        prev = [None] * self.n\n        que =\
    \ deque()\n        dist[s] = 0\n        que.append(s)\n        while len(que)\
    \ > 0:\n            u = que.popleft()\n            for e in self.g[u]:\n     \
    \           if dist[e.dst] == inf:\n                    dist[e.dst] = dist[e.src]\
    \ + 1\n                    prev[e.dst] = e\n                    que.append(e.dst)\n\
    \        return dist, prev\n    def __shortest_path_dijkstra(self, s: int, inf:\
    \ Cost) -> Tuple[List[Cost], List[Edge]]:\n        dist = [inf] * self.n\n   \
    \     prev = [None] * self.n\n        que = []\n        dist[s] = 0\n        heapq.heappush(que,\
    \ (0, s))\n        while len(que) > 0:\n            d, u = heapq.heappop(que)\n\
    \            if dist[u] < d:\n                continue\n            for e in self.g[u]:\n\
    \                if dist[e.dst] == inf or dist[e.dst] > dist[e.src] + e.cost:\n\
    \                    dist[e.dst] = dist[e.src] + e.cost\n                    prev[e.dst]\
    \ = e\n                    heapq.heappush(que, (dist[e.dst], e.dst))\n       \
    \ return dist, prev\n"
  dependsOn: []
  isVerificationFile: false
  path: py/graph.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo-shortest-path.test.py
documentation_of: py/graph.py
layout: document
redirect_from:
- /library/py/graph.py
- /library/py/graph.py.html
title: py/graph.py
---
