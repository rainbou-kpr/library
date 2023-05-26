import typing


class add:
    def __init__(self, l: typing.List[int]):
        t = 0
        for i in l:
            t += i
        self.v = t

    def __str__(self) -> str:
        return str(self.v)
