class DoubleEndedPriorityQueue:
    def __init__(self,pop,push) -> None:
        self.pop=pop
        self.push=push
        self.l = []
        self.ld = {}
        self.r = []
        self.rd = {}

    def eject(self, x: int) -> None:
        if x in self.ld:
            self.ld[x] += 1
        else:
            self.ld[x] = 1
        if x in self.rd:
            self.rd[x] += 1
        else:
            self.rd[x] = 1
        while bool(self.l) and self.l[0] in self.ld:
            self.ld[self.l[0]] -= 1
            if self.ld[self.l[0]] == 0:
                self.ld.pop(self.l[0])
            self.pop(self.l)
        while bool(self.r) and -self.r[0] in self.rd:
            self.rd[-self.r[0]] -= 1
            if self.rd[-self.r[0]] == 0:
                self.rd.pop(-self.r[0])
            self.pop(self.r)

    def __bool__(self) -> bool:
        return bool(self.l)

    def pop_min(self) -> int:
        if not self:
            raise IndexError("pop from empty")
        m = self.l[0]
        self.eject(m)
        return m

    def pop_max(self) -> int:
        if not self:
            raise IndexError("pop from empty")
        m = -self.r[0]
        self.eject(m)
        return m

    def insert(self, x: int) -> None:
        self.push(self.l, x)
        self.push(self.r, -x)
