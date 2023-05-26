class Dict:
    def __init__(self) -> None:
        self.d = {}

    def __getitem__(self, x: int) -> int:
        if str(x) in self.d:
            return self.d[str(x)]
        else:
            return 0

    def __setitem__(self, x: int, y: int) -> None:
        self.d[str(x)] = y

import math