from typing import Generic, TypeVar
from collections import deque
import heapq

Cost = TypeVar('Cost')

class Graph(Generic[Cost]):
    """
    グラフの汎用クラス
    """
    class Edge:
        """
        グラフの辺を表すクラス
        """
        def __init__(self, src: int, dst: int, cost: Cost, id: int):
            self.src = src
            self.dst = dst
            self.cost = cost
            self.id = id
        def __int__(self):
            return self.dst

    def __init__(self, n: int):
        """
        コンストラクタ
        :param int n: 頂点数
        :rtype: None
        """
        self.n = n
        self.m = 0
        self.g = [[] for _ in range(n)]
    def add_edge(self, u: int, v: int, w: Cost=1):
        """
        無向辺を追加する
        :param int u: 始点
        :param int v: 終点
        :param int w: コスト 省略したら1
        :rtype: None
        """
        self.g[u].append(self.Edge(u, v, w, self.m))
        self.g[v].append(self.Edge(v, u, w, self.m))
        self.m += 1
    def add_directed_edge(self, u: int, v: int, w: Cost=1):
        """
        有向辺を追加する
        :param int u: 始点
        :param int v: 終点
        :param Cost w: コスト 省略したら1
        :rtype: None
        """
        self.g[u].append(self.Edge(u, v, w, self.m))
        self.m += 1
    def read(self, m: int, padding: int=-1, weighted: bool=False, directed: bool=False):
        """
        辺の情報を標準入力から受け取って追加する
        :param int m: 辺の数
        :param int padding: 頂点番号を入力からいくつずらすか 省略したら-1
        :param bool weighted: 辺の重みが入力されるか 省略したらfalseとなり、重み1で辺が追加される
        :param bool directed: 有向グラフかどうか 省略したらfalse
        :rtype: None
        """
        for _ in range(m):
            if weighted:
                u, v, c = map(int, input().split())
            else:
                u, v = map(int, input().split())
                c = 1
            u += padding
            v += padding
            if directed:
                self.add_directed_edge(u, v, c)
            else:
                self.add_edge(u, v, c)
    def __getitem__(self, v: int):
        """
        ある頂点から出る辺を列挙する
        :param int v: 頂点番号
        :return: vから出る辺のリスト
        :rtype: list[Edge]
        """
        return self.g[v]
    def shortest_path(self, s: int, weighted: bool = True, inf: Cost=-1):
        """
        ある頂点から各頂点への最短路
        :param int s: 始点
        :param int weighted: 1以外のコストの辺が存在するか 省略するとtrue
        :param Cost inf: コストのminの単位元 未到達の頂点への距離はinfになる 省略すると2**31-1
        :return: (各頂点への最短路長, 各頂点への最短路上の直前の辺)
        :rtype: tuple[list[Cost], list[Edge]]
        """
        if weighted:
            return self.__shortest_path_dijkstra(s, inf)
        else:
            return self.__shortest_path_bfs(s, inf)
    def __shortest_path_bfs(self, s: int, inf: Cost):
        dist = [2**31-1] * self.n
        prev = [None] * self.n
        que = deque()
        dist[s] = 0
        que.append(s)
        while len(que) > 0:
            u = que.popleft()
            for e in self.g[u]:
                if dist[e.dst] == inf:
                    dist[e.dst] = dist[e.src] + 1
                    prev[e.dst] = e
                    que.append(e.dst)
        return dist, prev
    def __shortest_path_dijkstra(self, s: int, inf: Cost):
        dist = [inf] * self.n
        prev = [None] * self.n
        que = []
        dist[s] = 0
        heapq.heappush(que, (0, s))
        while len(que) > 0:
            d, u = heapq.heappop(que)
            if dist[u] < d:
                continue
            for e in self.g[u]:
                if dist[e.dst] == inf or dist[e.dst] > dist[e.src] + e.cost:
                    dist[e.dst] = dist[e.src] + e.cost
                    prev[e.dst] = e
                    heapq.heappush(que, (dist[e.dst], e.dst))
        return dist, prev
