# verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A
import sys
input = sys.stdin.buffer.readline

from py.segtree import RMinQ


def main() -> None:
    n, q = map(int, input().split())
    seg = RMinQ(n, 2**31-1)
    for _ in range(q):
        com, x, y = map(int, input().split())
        if com == 0:
            seg.set(x, y)
        else:
            print(seg.prod(x, y+1))


if __name__ == "__main__":
    main()
