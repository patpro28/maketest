#pragma GCC optimize ("Ofast")
 
#include <bits/stdc++.h>
 
#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
 
// O(n log n), optimized from O(n log^2 n) solution
// to query deepest token in subtree, use euler tour tree and Segment Tree
 
void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<vi> g(n + 1);
    rep(i, 2, n + 1) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    ll ans = 0;
    vi tree(4 * n, n);
    vi a(n + 1, -1);
    function<int(int, int, int, int, int)> query = [&](int i, int l, int r, int L, int R) {
        if(r < L || R < l) return n;
        if(L <= l && r <= R) return tree[i];
        int m = (l + r) / 2;
        int j = query(2 * i + 1, l, m, L, R);
        int k = query(2 * i + 2, m + 1, r, L, R);
        return a[j] > a[k] ? j : k;
    };
    function<void(int, int, int, int, int)> upd = [&](int i, int l, int r, int k, int x) {
        if(l == r) {
            a[k] = x;
            tree[i] = k;
            return;
        }
        int m = (l + r) / 2;
        if(k <= m) upd(2 * i + 1, l, m, k, x);
        else upd(2 * i + 2, m + 1, r, k, x);
        tree[i] = (a[tree[2 * i + 1]] > a[tree[2 * i + 2]] ? tree[2 * i + 1] : tree[2 * i + 2]);
    };
 
    vi tin(n + 1), tout(n + 1), dep(n + 1);
    int ti = 0;
    function<void(int)> dfs = [&](int x) {
        tin[x] = ti++;
        for(int y : g[x]) {
            dep[y] = 1 + dep[x];
            dfs(y);
        }
        tout[x] = ti;
        upd(0, 0, n - 1, tin[x], dep[x]);
        if(s[x - 1] == '0') {
            int j = query(0, 0, n - 1, tin[x], tout[x] - 1);
            ans += a[j] - dep[x];
            upd(0, 0, n - 1, j, -1);
        }
    };
    dfs(1);
    cout << ans << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int te;
    cin >> te;
    while(te--) solve();
}