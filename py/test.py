def Main():
    Q = int(input())
    d = {}
    for i in range(Q):
        q = tuple(map(int, input().split()))
        if q[0] == 0:
            d[q[1]] = q[2]
        else:
            if q[1] in d:
                print(d[q[1]])
            else:
                print(0)
