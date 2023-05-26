class sub:
    def __init__(self, x, y) -> None:
        self.v = x+y


class add(sub):
    def __str__(self):
        return str(self.v)
