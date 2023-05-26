class sub:
    def __init__(self, l) -> None:
        t = 0
        for i in l:
            t += sum(i)
        self.v = t


class add(sub):
    def __str__(self):
        return str(self.v)
