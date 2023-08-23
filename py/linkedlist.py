class LinkedList:
    class LinkedListIterator:
        def __init__(self, v) -> None:
            self.value = v
            self.prev = None
            self.next = None

        def __iadd__(self, k: int):
            if k == 1:
                return self.next
            else:
                return self.next.__iadd__(k-1)

        def __isub__(self, k: int):
            if k == 1:
                return self.prev
            else:
                return self.prev.__isub__(k-1)

    def __init__(self, l=None) -> None:
        self.begin = self.LinkedListIterator(None)
        self.end = self.begin
        if l is not None:
            for v in l:
                self.append(v)

    def __bool__(self) -> bool:
        return self.begin is not self.end

    def __iter__(self):
        self._a = self.begin
        return self

    def __next__(self):
        if self._a is self.end:
            raise StopIteration()
        else:
            rt = self._a
            self._a += 1
            return rt

    def values(self):
        return [itr.value for itr in self]

    def append(self, v) -> None:
        itr = self.LinkedListIterator(v)
        if self.begin is self.end:
            self.begin = itr
        else:
            itr.prev = self.end.prev
            self.end.prev.next = itr
        itr.next = self.end
        self.end.prev = itr

    def appendleft(self, v) -> None:
        itr = self.LinkedListIterator(v)
        itr.next = self.begin
        self.begin.prev = itr
        self.begin = itr

    def pop(self):
        assert(self)
        itr = self.end.prev
        if self.begin is itr:
            self.end.prev = None
            self.begin = self.end
        else:
            itr.prev.next = self.end
            self.end.prev = itr.prev
        return itr.value

    def popleft(self):
        assert(self)
        itr = self.begin
        if itr.next is self.end:
            self.end.prev = None
            self.begin = self.end
        else:
            itr.next.prev = None
            self.begin = itr.next
        return itr.value

    def insert(self, i, v) -> None:
        if i is self.begin:
            self.appendleft(v)
        if i is self.end:
            self.append(v)
        else:
            j = i.prev
            itr = self.LinkedListIterator(v)
            itr.prev = j
            itr.next = i
            j.next = itr
            i.prev = itr

    def erase(self, i):
        assert(i is not self.end)
        if i is self.begin:
            self.popleft()
        else:
            j = i.next
            i = i.prev
            i.next = j
            j.prev = i

    def index(self, v):
        for itr in self:
            if itr.value == v:
                return itr
        return None
