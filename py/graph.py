from typing import Generic, TypeVar

Cost = TypeVar('Cost')

class Graph(Generic[Cost]):
    """
    グラフの汎用クラス
    """
    class Edge:
        """
        グラフの辺を表すクラス
        """
        def __init__(self, from: int, to: int, cost: Cost, id: int):
            self.from = from
            self.to = to
            self.cost = cost
            self.id = id
        def __int__(self):
            return self.to

    def __init__(self, n: int):
        """
        コンストラクタ
        :param n: 頂点数
        """
        self.n = n
        self.m = 0
        self.g = [[] for _ in range(n)]
    def add_edge(self, u: int, v: int, cost: Cost=1):
        """
        無向辺を追加する
        :param u: 始点
        :param v: 終点
        :param: cost コスト 省略したら1
        """
        g[u].append(Edge(u, v, cost, self.m))
        g[v].append(Edge(v, u, cost, self.m))
        self.m += 1
    def add_directed_edge(self, u: int, v: int, cost: Cost=1):
        """
        有向辺を追加する
        :param u: 始点
        :param v: 終点
        :param cost: コスト 省略したら1
        """
        g[u].append(Edge(u, v, cost, self.m))
        self.m += 1
    def read(self, m: int, padding: int=-1, weighted: bool=False, directed: bool=False):
        """
        辺の情報を標準入力から受け取って追加する
        :param m: 辺の数
        :param padding: 頂点番号を入力からいくつずらすか 省略したら-1
        :param weighted: 辺の重みが入力されるか 省略したらfalseとなり、重み1で辺が追加される
        :param directed: 有向グラフかどうか 省略したらfalse
        """
        for _ in range(m):
            if weighted:
                u, v, cost = map(int, input().split())
            else:
                u, v = map(int, input().split())
                cost = 1
            u += padding
            v += padding
            if directed:
                self.add_directed_edge(u+padding, v+padding, cost)
            else:
                self.add_edge(u+padding, v+padding, cost)
    def __getitem__(self, v: int) -> list[Edge]:
        """
        ある頂点から出る辺を列挙する
        :param v: 頂点番号
        :return: vから出る辺のリスト
        """
        return self.g[v]

