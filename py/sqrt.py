def isqrt(n: int) -> int:
    """
    floor(sqrt(n))
    :param int n: 平方根を求めたい非負整数
    :rtype: int
    """
    # python3.8以上ではmath.isqrtを推奨
    le = 0
    ri = 1
    while n >= ri*ri:
        ri <<= 1
    le = ri // 2
    while ri-le > 1:
        mid = (le+ri)//2
        if mid*mid <= n:
            le = mid
        else:
            ri = mid
    return le
