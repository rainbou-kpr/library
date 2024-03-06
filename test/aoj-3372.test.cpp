#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3372"
#include "../cpp/tree.hpp"
using namespace std;
using ll = long long;

template <typename T, typename U>
inline bool chmax(T& x, const U& y) { return x < y ? (x = y, true) : false; }

int main() {
    int n; cin >> n;
    Tree tr(n); tr.read();
    vector<ll> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    auto rt = tr.set_root(0);
    Tree<ll> tr_costed(n);
    for(int u = 0; u < n; u++) {
        for(int v : rt.child[u]) {
            tr_costed.add_edge(u, v, a[v]);
        }
    }
    auto lcart = tr_costed.build_lca(0);
    vector<int> b(n-1);
    vector<int> b_cnt(n);
    for(int i = 0; i < n-1; i++) {
        cin >> b[i]; b[i]--;
        b_cnt[b[i]]++;
    }
    reverse(b.begin(), b.end());
    int init = -1;
    for(int i = 0; i < n; i++) {
        if(!b_cnt[i]) init = i;
    }
    tuple<ll, int, int> farthest = {a[init], init, init};
    vector<ll> ans = {a[init]};
    auto dist = [&](int i, int j) { return lcart.dist(i, j) + a[lcart.lca(i, j)]; };
    for(int bi : b) {
        auto [d, x, y] = farthest;
        chmax(farthest, make_tuple(dist(x, bi), x, bi));
        chmax(farthest, make_tuple(dist(y, bi), y, bi));
        ans.push_back(get<0>(farthest));
    }
    reverse(ans.begin(), ans.end());
    for(ll a : ans) { cout << a << endl; }
}
