import math
import collections


def lcm(x, y):
    return x*y//math.gcd(x, y)


class Dict:
    def __init__(self) -> None:
        self.d = collections.defaultdict(int)

    def __getitem__(self, x: int) -> int:
        return self.d[str(x)]

    def __setitem__(self, x: int, y: int) -> None:
        self.d[str(x)] = y
