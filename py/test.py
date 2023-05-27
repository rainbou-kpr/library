from subtest import add


def Main():
    print(add(*map(int, input().split())))
