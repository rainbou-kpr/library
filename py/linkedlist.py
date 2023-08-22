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
        self.front = None
        self.back = None
        if l is not None:
            for v in l:
                self.append(v)

    def __bool__(self) -> bool:
        return self.front is not None

    def __iter__(self):
        self._a = self.front
        return self

    def __next__(self):
        if self._a is None:
            raise StopIteration()
        else:
            rt = self._a.value
            self._a += 1
            return rt

    def append(self, v) -> None:
        itr = self.LinkedListIterator(v)
        itr.prev = self.back
        if self.front is None:
            self.front = itr
        else:
            self.back.next = itr
        self.back = itr

    def appendleft(self, v) -> None:
        itr = self.LinkedListIterator(v)
        itr.next = self.front
        if self.back is None:
            self.back = itr
        else:
            self.front.next = itr
        self.front = itr

    def pop(self):
        itr = self.back
        if self.front is itr:
            self.front = self.back = None
        else:
            self.back = itr.prev
            self.back.next = None
        return itr.value

    def popleft(self):
        itr = self.front
        if self.back is itr:
            self.front = self.back = None
        else:
            self.front = itr.next
            self.front.prev = None
        return itr.value

    def insert(self, i, v) -> None:
        if i is None:
            self.appendleft(v)
        if i is self.back:
            self.append(v)
        else:
            j = i.next
            itr = self.LinkedListIterator(v)
            itr.prev = i
            itr.next = j
            j.prev = itr
            i.next = itr

    def erase(self, i):
        assert(self)
        assert(i is not None)
        if i is self.front:
            return self.popleft()
        elif i is self.back:
            return self.pop()
        else:
            j = i.next
            i = i.prev
            i.next = j
            j.prev = i
