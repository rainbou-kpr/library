from typing import Generic, TypeVar, Callable, List, Union

S = TypeVar('S')


class SegTree(Generic[S]):
    """
    セグメント木
    """

    def __init__(self, n_or_v: Union[int, List[S]], op: Callable[[S, S], S], e: S) -> None:
        """
        コンストラクタ
        :type S: 要素のtype
        :param int | List[S] n_or_v: 要素数 or 初期の要素のリスト
        :param Callable[[S, S], S] op: 積の関数
        :param S e: 積の単位元を返す関数
        """
        if type(n_or_v) is int:
            self.n = n_or_v
            self.op = op
            self.e = e
            self.sz = 1
            self.height = 0
            while self.sz < self.n:
                self.sz <<= 1
                self.height += 1
            self.data = [e for i in range(self.sz*2)]
        elif type(n_or_v) is list:
            self.n = len(n_or_v)
            self.op = op
            self.e = e
            self.sz = 1
            self.height = 0
            while self.sz < self.n:
                self.sz <<= 1
                self.height += 1
            self.data = [e for i in range(self.sz*2)]
            for i in range(self.n):
                self.data[self.sz+i] = n_or_v[i]
            for i in range(self.sz-1, 0, -1):
                self.update(i)
        else:
            return TypeError

    def __update(self, k: int) -> None:
        self.data[k] = self.op(self.data[2*k], self.data[2*k+1])

    def get(self, k: int) -> S:
        """
        指定された要素の値を返す
        :param int k: インデックス
        :return S: 値
        """
        return self.data[self.sz+k]

    def __getitem__(self, k: int) -> S:
        """
        指定された要素の値を返す
        :param int k: インデックス
        :return S: 値
        """
        return self.get(k)

    def set(self, k: int, x: S) -> None:
        """
        指定された要素の値をxに更新する
        :param int k: インデックス
        :param S x: 新しい値
        """
        k += self.sz
        self.data[k] = x
        for i in range(1, self.height+1):
            self.update(k >> i)

    def __setitem__(self, k: int, x: S):
        """
        指定された要素の値をxに更新する
        :param int k: インデックス
        :param S x: 新しい値
        """
        self.set(k, x)

    def apply(self, k: int, x: S) -> None:
        """
        指定された要素の値にxを作用させる
        :param int k: インデックス
        :param S x: 作用素
        """
        self.set(k, self.op(self.get(k), x))

    def prod(self, l: int, r: int) -> S:
        """
        [l, r)の区間の総積を返す
        :param int l: 半開区間の開始
        :param int r: 半壊区間の終端
        :return S: 総積
        """
        left_prod = self.e
        right_prod = self.e
        l += self.sz
        r += self.sz
        while l < r:
            if l & 1 == 1:
                left_prod = self.op(left_prod, self.data[l])
                l += 1
            if r & 1 == 1:
                r -= 1
                right_prod = self.op(self.data[r], right_prod)
            l >>= 1
            r >>= 1
        return self.op(left_prod, right_prod)

    def all_prod(self) -> S:
        """
        すべての要素の総積を返す
        :return S: 総積
        """
        return self.data[1]

    def max_right(self, l: int, f: Callable[[S], bool]) -> int:
        """
        (r = l or f(prod([l, r))) = True) and (r = n or f(prod([l, r+1))) = False)となるrを返す。
        fが単調なら、f(prod([l, r))) = Trueとなる最大のrとなる。
        :param l: 半開区間の開始
        :param f: 判定関数
        :return int: r
        """
        assert f(self.e)
        if l == self.n:
            return self.n
        l += self.sz
        while l % 2 == 0:
            l >>= 1
        sm = self.e
        while f(self.op(sm, self.data[l])):
            if l.bit_length() != (l+1).bit_length():
                return self.n
            sm = self.op(sm, self.data[l])
            l += 1
            while l % 2 == 0:
                l >>= 1
        while l < self.sz:
            if not f(self.op(self.data[l*2])):
                l *= 2
            else:
                sm = self.op(sm, self.data[l*2])
                l = l*2+1
        return l-self.sz

    def min_left(self, r: int, f: Callable[[S], bool]) -> int:
        """
        (l = 0 or f(prod([l, r))) = True) and (l = r or f(prod([l-1, r))) = False)となるlを返す。
        fが単調なら、f(prod([l, r))) = Trueとなる最小のlとなる。
        :param r: 半開区間の終端
        :param f: 判定関数
        :return int: l
        """
        assert f(self.e)
        if r == 0:
            return 0
        r += self.sz-1
        while r % 2 == 1:
            r >>= 1
        sm = self.e
        while f(self.op(sm, self.data[r])):
            if r.bit_length() != (r-1).bit_length():
                return 0
            sm = self.op(sm, self.data[r])
            r -= 1
            while r % 2 == 1:
                r >>= 1
        while r < self.sz:
            if not f(self.op(self.data[r*2+1], sm)):
                r = r*2+1
            else:
                sm = self.op(self.data[r*2+1], sm)
                r *= 2
        return r+1-self.sz

    def __str__(self) -> str:
        re: List[str] = []
        for i in range(self.n):
            re.append(str(self.data[i+self.sz]))
        return ' '.join(re)


class RMaxQ(SegTree, Generic[S]):
    def __init__(self, n_or_v: Union[int, List[S]], init: S = -float('inf')) -> None:
        """
        コンストラクタ
        :type S: 要素のtype
        :param int | List[S] n_or_v: 要素数 or 初期の要素のリスト
        :param S init: 単位元 デフォルトは-float('inf') これと比較演算できるならばSは他のtype(intなど)でもかまわない
        """
        super().__init__(n_or_v, lambda x, y: x if x > y else y, init)


class RMinQ(SegTree, Generic[S]):
    def __init__(self, n_or_v: Union[int, List[S]], init: S = float('inf')) -> None:
        """
        コンストラクタ
        :type S: 要素のtype
        :param int | List[S] n_or_v: 要素数 or 初期の要素のリスト
        :param S init: 単位元 デフォルトはfloat('inf') これと比較演算できるならばSは他のtype(intなど)でもかまわない
        """
        super().__init__(n_or_v, lambda x, y: x if x < y else y, init)


class RSumQ(SegTree, Generic[S]):
    def __init__(self, n_or_v: Union[int, List[S]], init: S = 0) -> None:
        """
        コンストラクタ
        :type S: 要素のtype
        :param int | List[S] n_or_v: 要素数 or 初期の要素のリスト
        :param S init: 単位元 デフォルトは0
        """
        super().__init__(n_or_v, lambda x, y: x+y, init)
