---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "from typing import TypeVar, Generic, Callable, Union, Dict\n\n\nT = TypeVar(\"\
    T\")\n\n\nclass _Template(Generic[T]):\n    def __init__(self, func: Callable[...,\
    \ T]) -> None:\n        self.__func = func\n        self.__cache: Dict[tuple,\
    \ T] = {}\n        self.__doc__ = func.__doc__\n\n    def __getitem__(self, args:\
    \ any) -> T:\n        if not isinstance(args, tuple):\n            args = args,\n\
    \        if args not in self.__cache:\n            result = self.__func(*args)\n\
    \            self.__cache[args] = result\n            return result\n        return\
    \ self.__cache[args]\n\n\ndef _template(func: Callable[..., T]) -> _Template[T]:\n\
    \    return _Template(func)\n\n\nclass ModintBase:\n    def __init__(self, value:\
    \ Union[\"ModintBase\", int] = 0) -> None:\n        \"\"\"value \u306E\u5270\u4F59\
    \u3067\u521D\u671F\u5316\u3057\u307E\u3059\u3002\n        :param value: \u521D\
    \u671F\u5316\u306B\u4F7F\u3046\u5024\n        \"\"\"\n        self._mod: int\n\
    \        self._type = type(self)\n        if isinstance(value, self._type):\n\
    \            value = value._value\n        self._value = value % self._mod\n\n\
    \    def copy(self):\n        \"\"\"\u81EA\u8EAB\u306E\u30B3\u30D4\u30FC\u3092\
    \u8FD4\u3057\u307E\u3059\u3002\n        :returns: \u81EA\u8EAB\u306E\u30B3\u30D4\
    \u30FC\n        \"\"\"\n        return self._type(self._value)\n\n    def value(self)\
    \ -> int:\n        \"\"\"\u4FDD\u6301\u3057\u3066\u3044\u308B\u5024\u3092\u53D6\
    \u5F97\u3057\u307E\u3059\u3002\n        :returns: \u4FDD\u6301\u3057\u3066\u3044\
    \u308B\u5024\n        \"\"\"\n        return self._value\n\n    def __iadd__(self,\
    \ x: Union[\"ModintBase\", int]):\n        if isinstance(x, self._type):\n   \
    \         self._value += x._value\n            if self._value >= self._mod:\n\
    \                self._value -= self._mod\n        else:\n            self._value\
    \ += x\n            self._value %= self._mod\n        return self\n\n    def __isub__(self,\
    \ x: Union[\"ModintBase\", int]):\n        if isinstance(x, self._type):\n   \
    \         self._value -= x._value\n            if self._value < 0:\n         \
    \       self._value += self._mod\n        else:\n            self._value -= x\n\
    \            self._value %= self._mod\n        return self\n\n    def __imul__(self,\
    \ x: Union[\"ModintBase\", int]):\n        if isinstance(x, self._type):\n   \
    \         x = x._value\n        self._value *= x\n        self._value %= self._mod\n\
    \        return self\n\n    def __itruediv__(self, x: Union[\"ModintBase\", int]):\n\
    \        if not isinstance(x, self._type):\n            x = self._type(x)\n  \
    \      self._value *= x.inv()._value\n        self._value %= self._mod\n     \
    \   return self\n\n    def __ipow__(self, n: int):\n        self._value = pow(self._value,\
    \ n, self._mod)\n        return self\n\n    def __pos__(self):\n        return\
    \ self._type(self._value)\n\n    def __neg__(self):\n        return self._type(-self._value)\n\
    \n    def pow(self, n: int):\n        \"\"\"\u81EA\u8EAB\u306E n \u4E57\u3092\u8FD4\
    \u3057\u307E\u3059\u3002\n        :param n: \u6307\u6570\n        :returns: \u81EA\
    \u8EAB\u306E n \u4E57\n        \"\"\"\n        return self._type(pow(self._value,\
    \ n, self._mod))\n\n    def inv(self):\n        \"\"\"\u81EA\u8EAB\u306E\u9006\
    \u6570\u3092\u8FD4\u3057\u307E\u3059\u3002\n        \u6642\u9593\u8A08\u7B97\u91CF\
    \uFF1A O(log value)\n        :returns: \u81EA\u8EAB\u306E\u9006\u6570\n      \
    \  \"\"\"\n        a, b = self._mod, self._value\n        x, y = 0, 1\n      \
    \  while b:\n            t = a // b\n            a, b = b, a - t * b\n       \
    \     x, y = y, x - t * y\n        assert a == 1, \"The inverse element does not\
    \ exist.\"\n        return self._type(x)\n\n    def __add__(self, y: Union[\"\
    ModintBase\", int]):\n        if isinstance(y, self._type):\n            y = y._value\n\
    \        return self._type(self._value + y)\n\n    def __radd__(self, x: int):\n\
    \        return self._type(x + self._value)\n\n    def __sub__(self, y: Union[\"\
    ModintBase\", int]):\n        if isinstance(y, self._type):\n            y = y._value\n\
    \        return self._type(self._value - y)\n\n    def __rsub__(self, x: int):\n\
    \        return self._type(x - self._value)\n\n    def __mul__(self, y: Union[\"\
    ModintBase\", int]):\n        if isinstance(y, self._type):\n            y = y._value\n\
    \        return self._type(self._value * y)\n\n    def __rmul__(self, x: int):\n\
    \        return self._type(x * self._value)\n\n    def __truediv__(self, y: Union[\"\
    ModintBase\", int]):\n        if not isinstance(y, self._type):\n            y\
    \ = self._type(y)\n        return self._type(self._value * y.inv()._value)\n\n\
    \    def __rtruediv__(self, x: int):\n        return self._type(x * self.inv()._value)\n\
    \n    def __pow__(self, n: int):\n        return self._type(pow(self._value, n,\
    \ self._mod))\n\n    def __eq__(self, y: Union[\"ModintBase\", int]) -> bool:\n\
    \        if isinstance(y, self._type):\n            y = y._value\n        return\
    \ self._value == y\n\n    def __ne__(self, y: Union[\"ModintBase\", int]) -> bool:\n\
    \        if isinstance(y, self._type):\n            y = y._value\n        return\
    \ self._value != y\n\n    def __str__(self) -> str:\n        \"\"\"\u4FDD\u6301\
    \u3059\u308B\u5024\u3092\u6587\u5B57\u5217\u306B\u5909\u63DB\u3057\u307E\u3059\
    \u3002\n        \"\"\"\n        return str(self._value)\n\n\n@_template\ndef StaticModint(Mod:\
    \ int):\n    \"\"\"\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\u3066\u81EA\u52D5\
    \u3067 mod \u3092\u53D6\u308B\u30AF\u30E9\u30B9\n    :param Mod: \u6CD5\n    \"\
    \"\"\n    assert Mod > 0\n\n    class StaticModint(ModintBase):\n        _mod\
    \ = Mod\n\n        @staticmethod\n        def mod() -> int:\n            \"\"\"\
    \u6CD5\u3092\u53D6\u5F97\u3057\u307E\u3059\u3002\n            :returns: \u6CD5\
    \n            \"\"\"\n            return Mod\n    return StaticModint\n\n\n@_template\n\
    def DynamicModint(_: int):\n    \"\"\"\u56DB\u5247\u6F14\u7B97\u306B\u304A\u3044\
    \u3066\u81EA\u52D5\u3067 mod \u3092\u53D6\u308B\u30AF\u30E9\u30B9\n    :param\
    \ _: \u3053\u306EID\u3054\u3068\u306B\u6CD5\u3092\u8A2D\u5B9A\u3059\u308B\u3053\
    \u3068\u304C\u3067\u304D\u307E\u3059\n    \"\"\"\n    class DynamicModint(ModintBase):\n\
    \        _mod = 998244353\n\n        @classmethod\n        def mod(cls) -> int:\n\
    \            \"\"\"\u6CD5\u3092\u53D6\u5F97\u3057\u307E\u3059\u3002\n        \
    \    :returns: \u6CD5\n            \"\"\"\n            return cls._mod\n\n   \
    \     @classmethod\n        def set_mod(cls, m: int) -> None:\n            \"\"\
    \"\u6CD5\u3092\u8A2D\u5B9A\u3057\u307E\u3059\u3002\n            :param m: \u65B0\
    \u3057\u3044\u6CD5\n            \"\"\"\n            assert m > 0\n           \
    \ cls._mod = m\n    return DynamicModint\n\n\nModint998244353 = StaticModint[998244353]\n\
    Modint1000000007 = StaticModint[1000000007]\nModint = DynamicModint[-1]\n"
  dependsOn: []
  isVerificationFile: false
  path: py/modint.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: py/modint.py
layout: document
redirect_from:
- /library/py/modint.py
- /library/py/modint.py.html
title: py/modint.py
---
