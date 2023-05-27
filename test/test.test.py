# verification-helper: PROBLEM https://judge.yosupo.jp/problem/double_ended_priority_queue
import heapq

from py.test import DoubleEndedPriorityQueue


pq = DoubleEndedPriorityQueue(heapq.heappop, heapq.heappush)
N, Q = map(int, input().split())
S = list(map(int, input().split()))
for i in S:
    pq.insert(i)
for _ in range(Q):
    q = tuple(map(int, input().split()))
    if q[0] == 0:
        pq.insert(q[1])
    elif q[0] == 1:
        print(pq.pop_min())
    else:
        print(pq.pop_max())
