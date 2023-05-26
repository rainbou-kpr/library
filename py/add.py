class add:
    from typing import List

    def __init__(self, l: List[int]) -> None:
        t = 0
        for i in l:
            t += i
        self.v = t

    def __str__(self) -> str:
        return str(self.v)
