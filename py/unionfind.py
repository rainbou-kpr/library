from typing import List


class UnionFind:
    """
    無向グラフに対して「辺の追加」、「2頂点が連結かの判定」をする
    """

    def __init__(self, n: int) -> None:
        """
        コンストラクタ
        :param int n: 頂点数
        """
        self._n = n
        self.parent_or_size = [-1]*n

    def merge(self, a: int, b: int) -> int:
        """
        辺(a,b)を足す
        :return: 連結したものの代表元
        """
        assert 0 <= a < self._n
        assert 0 <= b < self._n
        x = self.leader(a)
        y = self.leader(b)
        if x == y:
            return x
        if -self.parent_or_size[x] < -self.parent_or_size[y]:
            x, y = y, x
        self.parent_or_size[x] += self.parent_or_size[y]
        self.parent_or_size[y] = x
        return x

    def same(self, a: int, b: int) -> bool:
        """
        頂点a,bが連結かどうか
        """
        assert 0 <= a < self._n
        assert 0 <= b < self._n
        return self.leader(a) == self.leader(b)

    def leader(self, a: int) -> int:
        """
        頂点aの属する連結成分の代表元
        """
        assert 0 <= a < self._n
        if self.parent_or_size[a] < 0:
            return a
        x = a
        while self.parent_or_size[x] >= 0:
            x = self.parent_or_size[x]
        while self.parent_or_size[a] >= 0:
            self.parent_or_size[a], a = x, self.parent_or_size[a]
        return x

    def size(self, a: int) -> int:
        """
        頂点aの属する連結成分のサイズ
        """
        assert 0 <= a < self._n
        return -self.parent_or_size[self.leader(a)]

    def groups(self) -> List[List[int]]:
        """
        グラフを連結成分に分け、その情報を返す
        :return: 「一つの連結成分の頂点番号のリスト」のリスト
        """
        leader_buf = [0]*self._n
        group_size = [0]*self._n
        for i in range(self._n):
            leader_buf[i] = self.leader(i)
            group_size[leader_buf[i]] += 1
        result = [[] for i in range(self._n)]
        for i in range(self._n):
            result[leader_buf[i]].append(i)
        return [l for l in result if l]
