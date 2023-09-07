---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj-alds1-3-c.test.py
    title: test/aoj-alds1-3-c.test.py
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.18/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 93, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "from typing import Any, List, Optional, Iterable\n\n\nclass LinkedListElement:\n\
    \    \"\"\"\n    \u9023\u7D50\u30EA\u30B9\u30C8\u306E\u8981\u7D20\n    \"\"\"\n\
    \n    def __init__(self, value: Any, prev: Optional['LinkedListElement'] = None,\
    \ next: Optional['LinkedListElement'] = None) -> None:\n        \"\"\"\n     \
    \   \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n        :param Any value: \u5024\
    \n        :param LinkedListElement | None prev: \u524D\u306E\u8981\u7D20\n   \
    \     :param LinkedListElement | None next: \u6B21\u306E\u8981\u7D20\n       \
    \ \"\"\"\n        self.value = value\n        self.prev = prev\n        self.next\
    \ = next\n\n    def __add__(self, k: int) -> Optional['LinkedListElement']:\n\
    \        a = self\n        for i in range(k):\n            a = a.next\n      \
    \      if a is None:\n                return None\n        return a\n\n    def\
    \ __sub__(self, k: int) -> Optional['LinkedListElement']:\n        a = self\n\
    \        for i in range(k):\n            a = a.prev\n            if a is None:\n\
    \                return None\n        return a\n\n\nclass LinkedListIterator:\n\
    \    def __init__(self, begin: LinkedListElement, end: LinkedListElement) -> None:\n\
    \        self.a = begin\n        self.begin = begin\n        self.end = end\n\n\
    \    def __iter__(self):\n        return LinkedListIterator(self.begin, self.end)\n\
    \n    def __next__(self):\n        if self.a is self.end:\n            raise StopIteration()\n\
    \        else:\n            rt = self.a\n            self.a = self.a + 1\n   \
    \         return rt\n\n\nclass LinkedList:\n    def __init__(self, l: Optional[Iterable]\
    \ = None) -> None:\n        \"\"\"\n        \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\
    \u30BF\n        :param iterable l: \u521D\u671F\u5024\n        \"\"\"\n      \
    \  self.begin = LinkedListElement(None)\n        self.end = self.begin\n     \
    \   self.size = 0\n        if l is not None:\n            for v in l:\n      \
    \          self.append(v)\n\n    def __bool__(self) -> bool:\n        return self.begin\
    \ is not self.end\n\n    def __iter__(self) -> LinkedListIterator:\n        return\
    \ LinkedListIterator(self.begin, self.end)\n\n    def __len__(self) -> int:\n\
    \        return self.size\n\n    def __getitem__(self, k: int) -> Any:\n     \
    \   \"\"\"\n        \u524D\u304B\u3089k\u756A\u76EE(0-based)\u306E\u5024\u3092\
    \u8FD4\u3059\u3002O(min(k,len-k))\n        :param int k: index\n        \"\"\"\
    \n        assert(0 <= k < self.size)\n        if k <= self.size//2:\n        \
    \    return (self.begin+k).value\n        else:\n            return (self.end-(self.size-k)).value\n\
    \n    def __setitem__(self, k: int, v: Any) -> None:\n        \"\"\"\n       \
    \ \u524D\u304B\u3089k\u756A\u76EE(0-based)\u306E\u5024\u306B\u4EE3\u5165\u3059\
    \u308B\u3002O(min(k,len-k))\n        :param int k: index\n        :param Any v:\
    \ \u5024\n        \"\"\"\n        assert(0 <= k < self.size)\n        if k <=\
    \ self.size//2:\n            (self.begin+k).value = v\n        else:\n       \
    \     (self.end-(self.size-k)).value = v\n\n    def values(self) -> List[Any]:\n\
    \        \"\"\"\n        \u5404\u8981\u7D20\u306E\u5024\u3092\u9806\u306B\u4E26\
    \u3079\u305F\u30EA\u30B9\u30C8\u3092\u8FD4\u3059\n        \"\"\"\n        return\
    \ [itr.value for itr in self]\n\n    def append(self, v: Any) -> None:\n     \
    \   \"\"\"\n        \u672B\u5C3E\u306B\u8FFD\u52A0\u3059\u308B\n        :param\
    \ Any v: \u5024\n        \"\"\"\n        self.size += 1\n        itr = LinkedListElement(v,\
    \ self.end.prev, self.end)\n        if self.begin is self.end:\n            self.begin\
    \ = itr\n        else:\n            self.end.prev.next = itr\n        self.end.prev\
    \ = itr\n\n    def appendleft(self, v) -> None:\n        \"\"\"\n        \u5148\
    \u982D\u306B\u8FFD\u52A0\u3059\u308B\n        :param Any v: \u5024\n        \"\
    \"\"\n        self.size += 1\n        itr = LinkedListElement(v, None, self.begin)\n\
    \        self.begin.prev = itr\n        self.begin = itr\n\n    def extend(self,\
    \ l: \"LinkedList\") -> None:\n        \"\"\"\n        l\u3092\u672B\u5C3E\u306B\
    \u8FFD\u52A0\u3059\u308B\u3002\\\\\n        LinkedList\u306A\u3089O(1)\u3001\u305D\
    \u308C\u4EE5\u5916\u306FO(len(l))\u3002\n        \"\"\"\n        self.size +=\
    \ l.size\n        if self.begin is self.end:\n            self.begin = l.begin\n\
    \            self.end = l.end\n        else:\n            l.begin.prev = self.end.prev\n\
    \            self.end.prev.next = l.begin\n            self.end = l.end\n\n  \
    \  def extendleft(self, l: \"LinkedList\") -> None:\n        \"\"\"\n        l\u3092\
    \u5148\u982D\u306B\u8FFD\u52A0\u3059\u308B\u3002\\\\\n        LinkedList\u306A\
    \u3089O(1)\u3001\u305D\u308C\u4EE5\u5916\u306FO(len(l))\u3002\n        \"\"\"\n\
    \        self.size += l.size\n        if self.begin is self.end:\n           \
    \ self.begin = l.begin\n            self.end = l.end\n        else:\n        \
    \    self.begin.prev = l.end.prev\n            l.end.prev.next = self.begin\n\
    \            self.begin = l.begin\n\n    def pop(self) -> Any:\n        \"\"\"\
    \n        \u672B\u5C3E\u3092\u524A\u9664\u3057\u3066\u3001\u305D\u306E\u5024\u3092\
    \u8FD4\u3059\n        \"\"\"\n        assert(self)\n        self.size -= 1\n \
    \       itr = self.end.prev\n        if self.begin is itr:\n            self.end.prev\
    \ = None\n            self.begin = self.end\n        else:\n            itr.prev.next\
    \ = self.end\n            self.end.prev = itr.prev\n        return itr.value\n\
    \n    def popleft(self) -> Any:\n        \"\"\"\n        \u5148\u982D\u3092\u524A\
    \u9664\u3057\u3066\u3001\u305D\u306E\u5024\u3092\u8FD4\u3059\n        \"\"\"\n\
    \        assert(self)\n        self.size -= 1\n        itr = self.begin\n    \
    \    if itr.next is self.end:\n            self.end.prev = None\n            self.begin\
    \ = self.end\n        else:\n            itr.next.prev = None\n            self.begin\
    \ = itr.next\n        return itr.value\n\n    def insert(self, i: LinkedListElement,\
    \ v: Any) -> None:\n        \"\"\"\n        \u6307\u5B9A\u3057\u305F\u4F4D\u7F6E\
    \u306E\u524D\u306B\u8FFD\u52A0\u3059\u308B\n        \"\"\"\n        self.size\
    \ += 1\n        if i is self.begin:\n            self.appendleft(v)\n        if\
    \ i is self.end:\n            self.append(v)\n        else:\n            j = i.prev\n\
    \            itr = LinkedListElement(v, j, i)\n            j.next = itr\n    \
    \        i.prev = itr\n\n    def erase(self, i: LinkedListElement) -> None:\n\
    \        \"\"\"\n        \u6307\u5B9A\u3057\u305F\u3082\u306E\u3092\u524A\u9664\
    \u3059\u308B\n        \"\"\"\n        assert(i is not self.end)\n        self.size\
    \ -= 1\n        if i is self.begin:\n            self.popleft()\n        else:\n\
    \            j = i.next\n            i = i.prev\n            i.next = j\n    \
    \        j.prev = i\n\n    def find(self, v: Any) -> Optional[LinkedListElement]:\n\
    \        \"\"\"\n        \u6307\u5B9A\u3057\u305F\u5024\u306E\u8981\u7D20\u3092\
    \u8FD4\u3059\n        \"\"\"\n        for itr in self:\n            if itr.value\
    \ == v:\n                return itr\n        return None\n\n    def index(self,\
    \ v: Any) -> Optional[int]:\n        \"\"\"\n        \u6307\u5B9A\u3057\u305F\u5024\
    \u304C\u4F55\u756A\u76EE\u304B\u3092\u8FD4\u3059(0-based)\n        \"\"\"\n  \
    \      k = 0\n        for itr in self:\n            if itr.value == v:\n     \
    \           return k\n            else:\n                k = k + 1\n        return\
    \ None\n"
  dependsOn: []
  isVerificationFile: false
  path: py/linkedlist.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj-alds1-3-c.test.py
documentation_of: py/linkedlist.py
layout: document
redirect_from:
- /library/py/linkedlist.py
- /library/py/linkedlist.py.html
title: py/linkedlist.py
---
