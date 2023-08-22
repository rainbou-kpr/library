# verification-helper: PROBLEM https://atcoder.jp/contests/arc064/tasks/arc064_b
from py.linkedlist import LinkedList


def query(s):
    l = LinkedList(s)
    i = l.front
    t = 0
    while i.next.next is not None:
        if i.value == i.next.next.value:
            i += 1
        else:
            l.erase(i.next)
            t += 1
            if i.prev is not None:
                i -= 1
    return t % 2 == 1


def __main__():
    if query(input()):
        print('First')
    else:
        print('Second')
