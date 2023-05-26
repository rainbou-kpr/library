# verification-helper: PROBLEM https://judge.yosupo.jp/problem/enumerate_quotients
from py.sqrt import isqrt


n = int(input())
v1 = []
v2 = []
m = isqrt(n)
for i in range(1, m+1):
    v1.append(n//i)
    v2.append(i)
if(v1[-1] == v2[-1]):
    v1.pop()
v1.reverse()
print(len(v1)+len(v2))
print(*(v2+v1))
