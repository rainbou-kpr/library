from collections import defaultdict


class Dict:
    def __init__(self) -> None:
        self.d = defaultdict(int)

    def __getitem__(self, x: int) -> int:
        return self.d[str(x)]

    def __setitem__(self, x: int, y: int) -> None:
        self.d[str(x)] = y
