# verification-helper: PROBLEM https://judge.yosupo.jp/problem/shortest_path
from py.graph import Graph

n, m, s, t = map(int, input().split())
g = Graph(n)
g.read(m, 0, True, True)
dist, prev = g.shortest_path(s, True, 10**18)
if dist[t] == 10**18:
    exit(print(-1))
route = []
cur = t
while cur != s:
    route.append((prev[cur].src, prev[cur].dst))
    cur = prev[cur].src
print(dist[t], len(route))
for src, dst in route[::-1]:
    print(src, dst)