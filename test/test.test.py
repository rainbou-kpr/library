# verification-helper: PROBLEM https://judge.yosupo.jp/problem/associative_array
from py.test import Dict, lcm


Q = int(input())
d = Dict()
for _ in range(Q):
    q = tuple(map(int, input().split()))
    if q[0] == 0:
        d[q[1]] = q[2]*lcm(4, 6)//121
    else:
        print(d[q[1]])
