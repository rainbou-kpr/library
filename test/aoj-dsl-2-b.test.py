# verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B
import sys
input = sys.stdin.buffer.readline

from py.segtree import RSumQ


def main() -> None:
    n, q = map(int, input().split())
    seg = RSumQ(n)
    for _ in range(q):
        com, x, y = map(int, input().split())
        if com == 0:
            seg.apply(x-1, y)
        else:
            print(seg.prod(x-1, y))


if __name__ == "__main__":
    main()
