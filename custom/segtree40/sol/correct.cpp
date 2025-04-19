#include "bits/stdc++.h"

using namespace std;

#define pb push_back
#define F first
#define S second
#define f(i, a, b)  for(int i = a; i < b; i++)
#define all(a)  a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define sz(x) (int)(x).size()
#define mp(x, y) make_pair(x,y)
#define popCnt(x) (__builtin_popcountll(x))
#define int ll

using ll = long long;
using ii = pair<int, int>;
using ull = unsigned long long;

const int N = 2e5 + 5, LG = 18, MOD = 1e9 + 7;
const long double PI = acos(-1);
const long double EPS = 1e-7;

int n, q;
int a[N];
int L[N], R[N];
int t[N << 2];
int lz[N << 2];

void build(int node, int s, int e) {
    lz[node] = t[node] = 0;
    if (s == e)return;
    int md = (s + e) >> 1;
    build(node << 1, s, md);
    build(node << 1 | 1, md + 1, e);
}

void push(int node, int s, int e) {
    t[node] += lz[node];
    if (s != e) {
        lz[node << 1] += lz[node];
        lz[node << 1 | 1] += lz[node];
    }
    lz[node] = 0;
}

void update(int node, int s, int e, int l, int r, int val) {
    push(node, s, e);
    if (r < s || e < l)return;
    if (l <= s && e <= r) {
        lz[node] += val;
        push(node, s, e);
        return;
    }
    int md = (s + e) >> 1;
    update(node << 1, s, md, l, r, val);
    update(node << 1 | 1, md + 1, e, l, r, val);
    t[node] = max(t[node << 1], t[node << 1 | 1]);
}

void update2(int node, int s, int e, int index, int val) {
    if (s == e) {
        t[node] = val;
        return;
    }
    int md = (s + e) >> 1;
    push(node << 1, s, md);
    push(node << 1 | 1, md + 1, e);
    if (index <= md)
        update2(node << 1, s, md, index, val);
    else
        update2(node << 1 | 1, md + 1, e, index, val);
    t[node] = max(t[node << 1], t[node << 1 | 1]);
}

int query(int node, int s, int e, int l, int r) {
    push(node, s, e);
    if (r < s || e < l)return -1e9;
    if (l <= s && e <= r)return t[node];
    int md = (s + e) >> 1;
    return max(query(node << 1, s, md, l, r),
               query(node << 1 | 1, md + 1, e, l, r));
}

vector<int> go[N];
vector<ii> qr[N];
int ans[N];

void doWork() {

    cin >> n >> q;
    vector<ii> vp;
    f(i, 1, n + 1) {
        go[i].clear();
        qr[i].clear();
        cin >> a[i];
        L[i] = 0;
        R[i] = n + 1;
        vp.push_back({a[i], i});
    }
    build(1, 1, n);
    sort(all(vp));
    set<int> st;
    for (auto [x, i]: vp) {
        auto it = st.lower_bound(i);
        if (it != st.begin()) {
            L[i] = *prev(it);
        }
        st.insert(i);
    }
    st.clear();
    reverse(all(vp));
    for (auto [x, i]: vp) {
        auto it = st.lower_bound(i);
        if (it != st.end()) {
            R[i] = *it;
        }
        st.insert(i);
    }

    f(i, 1, n + 1) {
        go[R[i]].push_back(i);
    }
    f(i, 1, q + 1) {
        int l, r;
        cin >> l >> r;
        qr[r].push_back({l, i});
        ans[i] = -1;
    }
    update(1, 1, n, 1, n, -1e9);
    vector<bool> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        for (auto j: go[i])
            if (L[j] && !vis[L[j]]) {
                vis[L[j]] = true;
                update2(1, 1, n, L[j], L[j] + 2);
            }
        update(1, 1, n, 1, n, +1);
        for (auto [l, j]: qr[i]) {
            int val = query(1, 1, n, l, i);
            ans[j] = max(ans[j], val - l);
            if (ans[j] < 3)ans[j] = -1;
        }
    }
    f(i, 1, q + 1) cout << ans[i] << '\n';

}

int32_t main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    int t = 1;
    cin >> t;
    while (t--) {
        doWork();
    }
}