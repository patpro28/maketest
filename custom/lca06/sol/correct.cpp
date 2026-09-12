#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define foru(i, l, r) for (int i = (l); i <= (r); ++i)
#define ford(i, l, r) for (int i = (l); i >= (r); --i)
#define fore(x, v) for (auto &x : v)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int N = 1e5 + 5, LOG = 17;
int n, q, t, st[N], en[N], sub[N], anc[N][LOG], high[N];
vector<int> graph[N];

void dfs(int u, int p)
{
    st[u] = ++t;
    sub[u] = 1;
    high[u] = high[p] + 1;
    anc[u][0] = p;
    foru(j, 1, LOG - 1) anc[u][j] = anc[anc[u][j - 1]][j - 1];
    fore(v, graph[u]) if (v != p)
    {
        dfs(v, u);
        sub[u] += sub[v];
    }
    en[u] = t;
}

bool isanc(int u, int v)
{
    return st[u] <= st[v] && st[v] <= en[u];
}

int lca(int u, int v)
{
    if (isanc(u, v))
        return u;
    ford(j, LOG - 1, 0) if (!isanc(anc[u][j], v)) u = anc[u][j];
    return anc[u][0];
}

int lift(int u, int d)
{
    ford(j, LOG - 1, 0) if (d >> j & 1) u = anc[u][j];
    return u;
}

int query(int u, int v, int i)
{
    int l = lca(u, v);
    if (l == i)
        return n - sub[lift(u, high[u] - high[i] - 1)] - sub[lift(v, high[v] - high[i] - 1)];
    if (high[i] < high[l])
        return 0;
    if (lift(u, high[u] - high[i]) != i)
        swap(u, v);
    if (lift(u, high[u] - high[i]) != i)
        return 0;
    return sub[i] - sub[lift(u, high[u] - high[i] - 1)];
}

int main()
{
    cin >> n >> q;

    foru(i, 2, n)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    high[0] = -1;
    en[0] = n + 1;
    dfs(1, 0);

    foru(i, 1, q)
    {
        int a, b, c;
        cin >> a >> b >> c;
        cout << query(a, b, c) << "\n";
    }
}