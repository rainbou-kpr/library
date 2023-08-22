# verification-helper: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_3_C
from py.linkedlist import LinkedList


def main():
    l = LinkedList()
    for _ in range(int(input())):
        q = input().split()
        if q[0] == 'insert':
            l.appendleft(int(q[1]))
        elif q[0] == 'delete':
            i = l.index(int(q[1]))
            if i is not None:
                l.erase(i)
        elif q[0] == 'deleteFirst':
            l.popleft()
        else:
            l.pop()
    print(*list(l))


if __name__ == "__main__":
    main()
