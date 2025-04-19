#include <bits/stdc++.h>
using namespace std;

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

int n;
const int M = 5e7 + 69;
const int N = 1e5 + 69;

struct node{
    int l, r; 
    int sum; // sum of ways?
};

struct S{
    // dp1, dp2 needs to be stored as implicit segtrees 
    int dp1v, dp2v;
    vector <int> a;
};

node seg[M];
int sub[N];
vector <int> adj[N];
int ptr = 0;
int a[N];
int dp1[N], dp2[N];
long long ans = 0;
const int mod = 1e9 + 7;

void add(int l, int r, int pos, int qp, int v){
    seg[pos].sum += v;
    if (seg[pos].sum >= mod) seg[pos].sum -= mod;
    
    if (l == r){
        return;
    }
    
    int mid = (l + r) / 2;
    if (qp <= mid){
        if (seg[pos].l == -1){
            seg[pos].l = ptr++;
        }
        add(l, mid, seg[pos].l, qp, v);
    } else {
        if (seg[pos].r == -1){
            seg[pos].r = ptr++;
        }
        add(mid + 1, r, seg[pos].r, qp, v);
    }
}

int query(int l, int r, int pos, int ql, int qr){
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return seg[pos].sum;
    
    int ans = 0;
    int mid = (l + r) / 2;
    
    if (seg[pos].l != -1 && ql <= mid){
        ans += query(l, mid, seg[pos].l, ql, qr);
    }
    if (seg[pos].r != -1 && qr > mid){
        ans += query(mid + 1, r, seg[pos].r, ql, qr);
    }
    
    if (ans >= mod) ans -= mod;
    return ans;
}

void getSub(int u, int p) {
    sub[u] = 1;
    pair<int, int> heavy = {-1, -1};
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == p) continue;
        getSub(v, u);
        sub[u] += sub[v];
        heavy = max(heavy, {sub[v], i});
    }
    // make the vertex with the largest subtree size the first
    if (heavy.first != -1) {
        swap(adj[u][0], adj[u][heavy.second]);
    }
}

S dp(int u, int p) {
    // do not initialize yet
    // dp1 -> this is greater 
    // dp2 -> this is smaller than previous 
    
    // case 1 : path passes through this node and includes it, and is not vertical 
    // case 2 : path doesnt pass through this node 
    
    S res;
    dp1[u] = 1;
    dp2[u] = 1;
    
    bool hasInit = false;
    for (int v : adj[u]) {
        if (v == p) continue;
        
        if (!hasInit){
            hasInit = true;
            S temp = dp(v, u);
            swap(temp, res);
            int v1 = query(1, n, res.dp2v, 1, a[u] - 1);
            int v2 = query(1, n, res.dp1v, a[u] + 1, n);
            ans += v1 + v2;
            ans %= mod;
            
            dp1[u] += v1;
            dp2[u] += v2;
            
            // cerr << "HANDLED " << v << " " << ans << "\n";
        } else {
            S temp = dp(v, u);
            // merge 
            for (auto x : temp.a){
                // add to answer for case when a[x] is used 
              //  cout << "HERE " << res.dp1v << " " << res.dp2v << endl;
            //     query(1, n, res.dp1v, 1, a[x] - 1);
            //   //  cout << "DONE" << endl;
            //     query(1, n, res.dp2v, a[x] + 1, n);
            
                int v1 = query(1, n, res.dp2v, 1, a[x] - 1);
                int v2 = query(1, n, res.dp1v, a[x] + 1, n);
                // cerr << dp1[x] << " " << v1 << "\n";
                // cerr << dp2[x] << " " << v2 << "\n";
                
                ans += 1LL * dp1[x] * v1;
                ans += 1LL * dp2[x] * v2;
                ans %= mod;
                
                res.a.push_back(x);
            }
            
            for (auto x : temp.a){
                add(1, n, res.dp1v, a[x], dp1[x]);
                add(1, n, res.dp2v, a[x], dp2[x]);
            }
            
            int v1 = query(1, n, temp.dp2v, 1, a[u] - 1);
            int v2 = query(1, n, temp.dp1v, a[u] + 1, n);
            
            ans += 1LL * dp1[u] * v1;
            ans += 1LL * dp2[u] * v2;
            dp1[u] += v1;
            dp2[u] += v2;
            
            if (dp1[u] >= mod) dp1[u] -= mod;
            if (dp2[u] >= mod) dp2[u] -= mod;
            
            ans %= mod;
        }
    }
    
    if (!hasInit) {
        res.dp1v = ptr++;
        res.dp2v = ptr++;
    }
    res.a.push_back(u);
    
    // for (int i = 1; i <= n; i++){
    //     cerr << query(1, n, res.dp1v, i, i) << " \n"[i == n];
    // }
    
    add(1, n, res.dp1v, a[u], dp1[u]);
    add(1, n, res.dp2v, a[u], dp2[u]);
    // cout << dp1[u] << "\n";
    
    // for (int i = 1; i <= n; i++){
    //     cerr << query(1, n, res.dp1v, i, i) << " \n"[i == n];
    // }
    // cout << u << " " << ans << "\n";
    // cout << "dp1 " << dp1[u] << " dp2 " << dp2[u] << "\n";
    return res;
}

void Solve() 
{
    cin >> n;
    
    for (int i = 1; i <= n; i++){
        adj[i].clear();
        dp1[i] = dp2[i] = 0;
        sub[i] = 0;
    }
    ans = 0;
    
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        // a[i] = 1 + RNG() % n;
    }
    
    for (int i = 2; i <= n; i++){
        int p; cin >> p;
        // int p = i / 2;
        
        adj[p].push_back(i);
    }
    
    getSub(1, -1);
    dp(1, -1);
    
    // cout << ptr << "\n";
    
    // for (int i = 1; i <= n; i++){
    //     cout << dp1[i] << " " << dp2[i] << "\n";
    // }
    
    ans %= mod;
    
    cout << ans << "\n";
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);
    
    for (int i = 0; i < M; i++){
        seg[i].l = seg[i].r = -1;
        
    }
    
    cin >> t;
    for(int i = 1; i <= t; i++) 
    {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}