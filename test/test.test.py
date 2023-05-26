# verification-helper: PROBLEM https://judge.yosupo.jp/problem/unionfind
import sys
input = sys.stdin.buffer.readline

from py.unionfind import UnionFind


def main() -> None:
    N, Q = map(int, input().split())
    uft = UnionFind(N)
    for _ in range(Q):
        t, u, v = map(int, input().split())
        if t == 0:
            uft.merge(u, v)
        else:
            print(int(uft.same(u, v)))


if __name__ == "__main__":
    main()