import sys


def Main():
    input = sys.stdin.buffer.readline
    print(sum(list(map(int, input().split()))))
