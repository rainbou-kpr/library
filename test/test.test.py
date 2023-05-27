# verification-helper: PROBLEM https://judge.yosupo.jp/problem/aplusb
from py.test import lcm

print(sum(list(map(int, input().split())))*lcm(4, 6)//12)
