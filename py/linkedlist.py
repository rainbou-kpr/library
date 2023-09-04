from typing import Any, List, Optional, Iterable


class LinkedListElement:
    """
    連結リストの要素
    """

    def __init__(self, value: Any, prev: Optional['LinkedListElement'] = None, next: Optional['LinkedListElement'] = None) -> None:
        """
        コンストラクタ
        :param Any value: 値
        :param LinkedListElement | None prev: 前の要素
        :param LinkedListElement | None next: 次の要素
        """
        self.value = value
        self.prev = prev
        self.next = next

    def __iadd__(self, k: int) -> Optional['LinkedListElement']:
        a = self
        for i in range(k):
            a = a.next
            if a is None:
                return None
        return a

    def __add__(self, k: int) -> Optional['LinkedListElement']:
        a = self
        a += k
        return a

    def __isub__(self, k: int) -> Optional['LinkedListElement']:
        a = self
        for i in range(k):
            a = a.prev
            if a is None:
                return None
        return a

    def __sub__(self, k: int) -> Optional['LinkedListElement']:
        a = self
        a -= k
        return a


class LinkedListIterator:
    def __init__(self, begin: LinkedListElement, end: LinkedListElement) -> None:
        self.a = begin
        self.begin = begin
        self.end = end

    def __iter__(self):
        return LinkedListIterator(self.begin, self.end)

    def __next__(self):
        if self.a is self.end:
            raise StopIteration()
        else:
            rt = self.a
            self.a += 1
            return rt


class LinkedList:
    def __init__(self, l: Optional[Iterable] = None) -> None:
        """
        コンストラクタ
        :param iterable l: 初期値
        """
        self.begin = LinkedListElement(None)
        self.end = self.begin
        self.size = 0
        if l is not None:
            for v in l:
                self.append(v)

    def __bool__(self) -> bool:
        return self.begin is not self.end

    def __iter__(self) -> LinkedListIterator:
        return LinkedListIterator(self.begin, self.end)

    def __len__(self) -> int:
        return self.size

    def __getitem__(self, k: int) -> Any:
        """
        前からk番目(0-based)の値を返す。O(min(k,len-k))
        :param int k: index
        """
        assert(0 <= k < self.size)
        if k <= self.size//2:
            return (self.begin+k).value
        else:
            return (self.end-(self.size-k)).value

    def __setitem__(self, k: int, v: Any) -> None:
        """
        前からk番目(0-based)の値に代入する。O(min(k,len-k))
        :param int k: index
        :param Any v: 値
        """
        assert(0 <= k < self.size)
        if k <= self.size//2:
            (self.begin+k).value = v
        else:
            (self.end-(self.size-k)).value = v

    def values(self) -> List[Any]:
        """
        各要素の値を順に並べたリストを返す
        """
        return [itr.value for itr in self]

    def append(self, v: Any) -> None:
        """
        末尾に追加する
        :param Any v: 値
        """
        self.size += 1
        itr = LinkedListElement(v, self.end.prev, self.end)
        if self.begin is self.end:
            self.begin = itr
        else:
            self.end.prev.next = itr
        self.end.prev = itr

    def appendleft(self, v) -> None:
        """
        先頭に追加する
        :param Any v: 値
        """
        self.size += 1
        itr = LinkedListElement(v, None, self.begin)
        self.begin.prev = itr
        self.begin = itr

    def extend(self, l: "LinkedList") -> None:
        """
        lを末尾に追加する。\\
        LinkedListならO(1)、それ以外はO(len(l))。
        """
        self.size += l.size
        if self.begin is self.end:
            self.begin = l.begin
            self.end = l.end
        else:
            l.begin.prev = self.end.prev
            self.end.prev.next = l.begin
            self.end = l.end

    def extendleft(self, l: "LinkedList") -> None:
        """
        lを先頭に追加する。\\
        LinkedListならO(1)、それ以外はO(len(l))。
        """
        self.size += l.size
        if self.begin is self.end:
            self.begin = l.begin
            self.end = l.end
        else:
            self.begin.prev = l.end.prev
            l.end.prev.next = self.begin
            self.begin = l.begin

    def pop(self) -> Any:
        """
        末尾を削除して、その値を返す
        """
        assert(self)
        self.size -= 1
        itr = self.end.prev
        if self.begin is itr:
            self.end.prev = None
            self.begin = self.end
        else:
            itr.prev.next = self.end
            self.end.prev = itr.prev
        return itr.value

    def popleft(self) -> Any:
        """
        先頭を削除して、その値を返す
        """
        assert(self)
        self.size -= 1
        itr = self.begin
        if itr.next is self.end:
            self.end.prev = None
            self.begin = self.end
        else:
            itr.next.prev = None
            self.begin = itr.next
        return itr.value

    def insert(self, i: LinkedListElement, v: Any) -> None:
        """
        指定した位置の前に追加する
        """
        self.size += 1
        if i is self.begin:
            self.appendleft(v)
        if i is self.end:
            self.append(v)
        else:
            j = i.prev
            itr = LinkedListElement(v, j, i)
            j.next = itr
            i.prev = itr

    def erase(self, i: LinkedListElement) -> None:
        """
        指定したものを削除する
        """
        assert(i is not self.end)
        self.size -= 1
        if i is self.begin:
            self.popleft()
        else:
            j = i.next
            i = i.prev
            i.next = j
            j.prev = i

    def find(self, v: Any) -> Optional[LinkedListElement]:
        """
        指定した値の要素を返す
        """
        for itr in self:
            if itr.value == v:
                return itr
        return None

    def index(self, v: Any) -> Optional[int]:
        """
        指定した値が何番目かを返す(0-based)
        """
        k = 0
        for itr in self:
            if itr.value == v:
                return k
            else:
                k += 1
        return None
