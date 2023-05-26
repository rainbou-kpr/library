# verification-helper: PROBLEM https://judge.yosupo.jp/problem/associative_array
from py.test import Dict


Q = int(input())
d = Dict()
for _ in range(Q):
    q = tuple(map(int, input().split()))
    if q[0] == 0:
        d[q[1]] = q[2]
    else:
        print(d[q[1]])
