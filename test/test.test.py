# verification-helper: PROBLEM https://judge.yosupo.jp/problem/unionfind
from py.test import UnionFindTree


N, Q = map(int, input().split())
g = UnionFindTree(N)
for i in range(Q):
    t, u, v = map(int, input().split())
    if t == 0:
        g.merge(u, v)
    else:
        print(1 if g.same(u, v) else 0)
