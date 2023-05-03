#pragma once

/**
 * @brief floor(sqrt(n))
 * @param n 平方根を求めたい整数 long long 型で 0 <= n < 2^63 を満たす
 * @return long long
 */
long long sqrtll(long long n) { 
    // 3037000500 = ceil(sqrt(2^63))
    long long le = 0, ri = 3037000500; 
    while(ri - le > 1) {
        long long mid = (le + ri) / 2;
        if(mid * mid <= n) le = mid;
        else ri = mid;
    }
    return le;
}