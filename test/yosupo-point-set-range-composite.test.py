# verification-helper: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite
import sys
input = sys.stdin.buffer.readline

from py.segtree import SegTree


def main() -> None:
    MOD = 998244353
    n, q = map(int, input().split())
    v = [tuple(map(int, input().split())) for i in range(n)]
    def op(l, r): return (l[0]*r[0] % MOD, (r[0]*l[1]+r[1]) % MOD)
    def e(): return (1, 0)
    seg = SegTree(v, op, e)
    for _ in range(q):
        query = tuple(map(int, input().split()))
        if query[0] == 0:
            p, c, d = query[1:]
            seg.set(p, (c, d))
        else:
            l, r, x = query[1:]
            f = seg.prod(l, r)
            print((f[0]*x + f[1]) % MOD)
    


if __name__ == "__main__":
    main()
