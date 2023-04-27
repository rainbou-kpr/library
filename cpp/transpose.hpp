#pragma once

#include <vector>

template<class T> std::vector<T> transpose(const std::vector<T> &v) {
    int n = v.size(), m = v[0].size();
    std::vector<T> ret(m);
    for(int i = 0; i < m; i ++) {
        ret[i].resize(n);
        for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];
    }
    return ret;
}
