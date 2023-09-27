# verification-helper: PROBLEM https://atcoder.jp/contests/past202012-open/tasks/past202012_n
from py.segtree import SegTree

N, Q = map(int, input().split())
lr = [tuple(map(int, input().split())) for i in range(N-1)]
seg = SegTree(lr, lambda a, b: (max(a[0], b[0]), min(a[1], b[1])), (0, 10**9))
for i in range(Q):
    a, b = map(int, input().split())
    b -= 1
    r = seg.max_right(b, lambda x: x[0] <= a <= x[1])
    l = seg.min_left(b, lambda x: x[0] <= a <= x[1])
    print(r-l+1)
