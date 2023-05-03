from typing import TypeVar, Generic, Callable, Union, Dict


T = TypeVar("T")


class _Template(Generic[T]):
    def __init__(self, func: Callable[..., T]) -> None:
        self.__func = func
        self.__cache: Dict[tuple, T] = {}
        self.__doc__ = func.__doc__

    def __getitem__(self, args: any) -> T:
        if not isinstance(args, tuple):
            args = args,
        if args not in self.__cache:
            result = self.__func(*args)
            self.__cache[args] = result
            return result
        return self.__cache[args]


def _template(func: Callable[..., T]) -> _Template[T]:
    return _Template(func)


class ModintBase:
    def __init__(self, value: int = 0) -> None:
        """value の剰余で初期化します。
        :param value: 初期化に使う値
        """
        self._mod: int
        self._value = value % self._mod
        self._type = type(self)

    def copy(self):
        """自身のコピーを返します。
        :returns: 自身のコピー
        """
        return self._type(self._value)

    def value(self) -> int:
        """保持している値を取得します。
        :returns: 保持している値
        """
        return self._value

    def __iadd__(self, x: Union["ModintBase", int]):
        if isinstance(x, self._type):
            self._value += x._value
            if self._value >= self._mod:
                self._value -= self._mod
        else:
            self._value += x
            self._value %= self._mod
        return self

    def __isub__(self, x: Union["ModintBase", int]):
        if isinstance(x, self._type):
            self._value -= x._value
            if self._value < 0:
                self._value += self._mod
        else:
            self._value -= x
            self._value %= self._mod
        return self

    def __imul__(self, x: Union["ModintBase", int]):
        if isinstance(x, self._type):
            x = x._value
        self._value *= x
        self._value %= self._mod
        return self

    def __itruediv__(self, x: Union["ModintBase", int]):
        if not isinstance(x, self._type):
            x = self._type(x)
        self._value *= x.inv()._value
        self._value %= self._mod
        return self

    def __ipow__(self, n: int):
        self._value = pow(self._value, n, self._mod)
        return self

    def __pos__(self):
        return self._type(self._value)

    def __neg__(self):
        return self._type(-self._value)

    def pow(self, n: int):
        """自身の n 乗を返します。
        :param n: 指数
        :returns: 自身の n 乗
        """
        return self._type(pow(self._value, n, self._mod))

    def inv(self):
        """自身の逆数を返します。
        時間計算量： O(log value)
        :returns: 自身の逆数
        """
        a, b = self._mod, self._value
        x, y = 0, 1
        while b:
            t = a // b
            a, b = b, a - t * b
            x, y = y, x - t * y
        assert a == 1, "The inverse element does not exist."
        return self._type(x)

    def __add__(self, y: Union["ModintBase", int]):
        if isinstance(y, self._type):
            y = y._value
        return self._type(self._value + y)

    def __radd__(self, x: int):
        return self._type(x + self._value)

    def __sub__(self, y: Union["ModintBase", int]):
        if isinstance(y, self._type):
            y = y._value
        return self._type(self._value - y)

    def __rsub__(self, x: int):
        return self._type(x - self._value)

    def __mul__(self, y: Union["ModintBase", int]):
        if isinstance(y, self._type):
            y = y._value
        return self._type(self._value * y)

    def __rmul__(self, x: int):
        return self._type(x * self._value)

    def __truediv__(self, y: Union["ModintBase", int]):
        if not isinstance(y, self._type):
            y = self._type(y)
        return self._type(self._value * y.inv()._value)

    def __rtruediv__(self, x: int):
        return self._type(x * self.inv()._value)

    def __pow__(self, n: int):
        return self._type(pow(self._value, n, self._mod))

    def __eq__(self, y: Union["ModintBase", int]) -> bool:
        if isinstance(y, self._type):
            y = y._value
        return self._value == y

    def __ne__(self, y: Union["ModintBase", int]) -> bool:
        if isinstance(y, self._type):
            y = y._value
        return self._value != y

    def __str__(self) -> str:
        """保持する値を文字列に変換します。
        """
        return str(self._value)


@_template
def StaticModint(Mod: int):
    """四則演算において自動で mod を取るクラス
    :param Mod: 法
    """
    assert Mod > 0

    class StaticModint(ModintBase):
        _mod = Mod

        @staticmethod
        def mod() -> int:
            """法を取得します。
            :returns: 法
            """
            return Mod
    return StaticModint


@_template
def DynamicModint(_: int):
    """四則演算において自動で mod を取るクラス
    :param _: このIDごとに法を設定することができます
    """
    class DynamicModint(ModintBase):
        _mod = 998244353

        @classmethod
        def mod(cls) -> int:
            """法を取得します。
            :returns: 法
            """
            return cls._mod

        @classmethod
        def set_mod(cls, m: int) -> None:
            """法を設定します。
            :param m: 新しい法
            """
            assert m > 0
            cls._mod = m
    return DynamicModint


Modint998244353 = StaticModint[998244353]
Modint1000000007 = StaticModint[1000000007]
Modint = DynamicModint[-1]
