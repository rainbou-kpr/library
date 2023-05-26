class add:
    def __init__(self, l) -> None:
        t = 0
        for i in l:
            t += i
        self.v = t

    def __str__(self) -> str:
        return str(self.v)
