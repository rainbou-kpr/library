#define PROBLEM "https://atcoder.jp/contests/jsc2021/tasks/jsc2021_g"
#define IGNORE

#include "../cpp/modint.hpp"
#include "../cpp/matrix.hpp"
#include "../cpp/unionfind.hpp"
#include <set>

using mint = modint1000000007;

int main(void) {
    int n; std::cin >> n;
    UnionFind uf(n), uf_all(n);
    int a[n][n];
    for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++) std::cin >> a[i][j];
    for(int i = 0; i < n; i ++) for(int j = i + 1; j < n; j ++) {
        if(a[i][j]) {
            uf_all.merge(i, j);
            if(a[i][j] == 1) {
                if(uf.same(i, j)) {
                    std::cout << 0 << std::endl;
                    return 0;
                }
                uf.merge(i, j);
            } 
        }
    }
    
    if(uf_all.size(0) != n) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::set<int> st;
    for(int i = 0; i < n; i ++) st.insert(uf.leader(i));
    int m = st.size();
    if(m == 1) {
        std::cout << 1 << std::endl;
        return 0;
    }

    Matrix<mint> mat(m - 1, m - 1);
    { // 座標圧縮とラプラシアン行列の余因子
        int id[n], cnt = 0;
        while(!st.empty()) {
            id[*st.begin()] = cnt ++;
            st.erase(st.begin());
        }
        for(int i = 0; i < n; i ++) for(int j = i + 1; j < n; j ++) {
            if(a[i][j] == -1) {
                int A = uf.leader(i), B = uf.leader(j);
                if(A == B) continue;
                A = id[A], B = id[B];
                if(A + 1 < m) mat[A][A] += 1;
                if(B + 1 < m) mat[B][B] += 1;
                if(A + 1 < m && B + 1 < m) {
                    mat[A][B] -= 1;
                    mat[B][A] -= 1;
                }
            }
        }
    }
    std::cout << mat.det().value() << std::endl; 
    return 0;
}
