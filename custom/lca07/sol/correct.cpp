/*

we store lin*d(x) + con, where lin and con are some coefficients.
We break up the path into increasing segments, and calculate the coefficients
using subtree sums.

*/

#include "bits/stdc++.h"
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main()
{
    cin.tie(NULL), cin.sync_with_stdio(false);

    int n, s;
    cin >> n >> s;

    vector<ll> con(n), lin(n);

    vvi par(__lg(n) + 1, vi(n)), adj(n);
    vi d(n), vis(n);

    rep(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](int at, int dep, auto &&dfs) -> void
    {
        vis[at] = 1;
        d[at] = dep;
        for (auto to : adj[at])
            if (!vis[to])
            {
                par[0][to] = at;
                dfs(to, dep + 1, dfs);
            }
    };
    dfs(0, 0, dfs);
    rep(i, 0, __lg(n)) rep(j, 0, n) par[i + 1][j] = par[i][par[i][j]];

    auto jmp = [&](int at, int k) -> int
    {
        for (int i = 0; k; ++i, k /= 2)
            if (k & 1)
                at = par[i][at];
        return at;
    };

    auto lca = [&](int u, int v) -> int
    {
        if (d[u] < d[v])
            swap(u, v);
        u = jmp(u, d[u] - d[v]);
        if (u == v)
            return u;
        for (int i = __lg(n); i >= 0; --i)
            if (par[i][u] != par[i][v])
                u = par[i][u], v = par[i][v];
        return par[0][u];
    };

    auto getmid = [&](int u, int v, int t) -> int
    {
        int luv = lca(u, v);
        int lut = lca(u, t);
        int lvt = lca(v, t);

        if (d[luv] > d[lut])
        {
            if (d[luv] > d[lvt])
                return luv;
            return lvt;
        }
        else
        {
            if (d[lut] > d[lvt])
                return lut;
            return lvt;
        }
    };

    // inclusive
    auto addLinFunc = [&](int lo, int hi, ll a, ll b) -> void
    {
        // f(lo) = b;
        // f(lo + x) = b + ba; <- reverse linear in depth

        con[lo] += a + d[lo] * b;
        lin[lo] -= b;

        if (hi != par[0][hi])
        {
            hi = par[0][hi];
            con[hi] -= a + d[lo] * b;
            lin[hi] += b;
        }
    };

    auto addPath = [&](int u, int v, int sval) -> void
    {
        auto mid = lca(u, v);
        addLinFunc(u, mid, sval, 1);
        addLinFunc(v, mid, sval + d[u] + d[v] - 2 * d[mid], -1);
        con[mid] -= sval + d[u] - d[mid]; // subtract doubly counted node
        if (par[0][mid] != mid)
            con[par[0][mid]] += sval + d[u] - d[mid];
    };

    auto dist = [&](int u, int v) -> int
    {
        int mid = lca(u, v);
        return d[u] + d[v] - d[mid] * 2;
    };

    auto addTri = [&](int u, int v, int t) -> void
    {
        int mid = getmid(u, v, t);
        int sd = dist(mid, t);
        addPath(mid, u, sd);
        addPath(mid, v, sd);
        con[mid] -= sd; // subtract doubly counted node
        if (par[0][mid] != mid)
            con[par[0][mid]] += sd;
    };

    auto prop = [&](int at, auto &&prop) -> void
    {
        vis[at] = 1;
        for (auto to : adj[at])
            if (!vis[to])
            {
                prop(to, prop);
                con[at] += con[to];
                lin[at] += lin[to];
            }
    };

    while (s--)
    {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--, t--;
        addTri(u, v, t);
    }

    fill(all(vis), 0);
    prop(0, prop);

    rep(i, 0, n)
    {
        cout << con[i] + d[i] * lin[i] << ' ';
    }
    cout << '\n';
}