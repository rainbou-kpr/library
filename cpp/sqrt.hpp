#pragma once

/**
 * @brief floor(sqrt(n))
 */

long long sqrtll(long long n) { 
    long long le = 0, ri = 3'000'000'001;
    while(ri - le > 1) {
        long long mid = (le + ri) / 2;
        if(mid * mid <= n) le = mid;
        else ri = mid;
    }
    return le;
}