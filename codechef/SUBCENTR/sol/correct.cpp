#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define ll long long int

using namespace std;

const int maxtk = 1e6, maxtn = 5e5, maxn = 1e5;
const string newln = "\n", space = " ";
vector<int> g[maxn + 10], nodes;
bool visited[maxn + 10], visitedk[maxn + 10];
int depth[maxn + 10], parent[maxn + 10][20];
int n, q;
bool isGraph(int u, int pa)
{
    parent[u][0] = pa;
    if (visited[u])
        return false;
    visited[u] = true;
    for (int v : g[u])
    {
        if (v == pa)
            continue;
        depth[v] = depth[u] + 1;
        if (!isGraph(v, u))
            return false;
    }
    return true;
}

int lca(int u, int v)
{
    if (u == v)
        return u;
    if (depth[u] < depth[v])
        swap(u, v);
    for (int i = 19; i >= 0; i--)
    {
        if (depth[u] - (1 << i) >= depth[v])
        {
            u = parent[u][i];
        }
    }
    if (u == v)
        return u;
    for (int i = 19; i >= 0; i--)
    {
        if (parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    int tn = 0, tk = 0;
    while (t--)
    {
        cin >> n >> q;
        tn += n;
        for (int i = 0; i <= n; i++)
        {
            g[i].clear();
            visited[i] = false;
        }
        int u, v;
        for (int i = 1; i < n; i++)
        {
            cin >> u >> v;
            assert(u != v);
            assert(u != 0);
            assert(v != 0);
            g[u].pb(v);
            g[v].pb(u);
        }
        depth[1] = 0;
        assert(isGraph(1, 0));
        for (int i = 1; i <= n; i++)
            assert(visited[i]);

        for (int i = 1; i < 20; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                parent[j][i] = parent[parent[j][i - 1]][i - 1];
            }
        }

        while (q--)
        {
            int k;
            cin >> k;
            tk += k;
            nodes.clear();
            int maxd = -1, n1 = -1;
            int x;
            for (int i = 1; i <= k; i++)
            {
                cin >> x;
                nodes.pb(x);
                assert(!visitedk[x]);
                visitedk[x] = true;
                if (depth[x] > maxd)
                {
                    maxd = depth[x];
                    n1 = x;
                }
            }
            int dia = -1;
            for (int i = 0; i < k; i++)
            {
                int node = nodes[i];
                int pdia = depth[n1] + depth[node] - 2 * depth[lca(n1, node)];
                if (pdia > dia)
                {
                    dia = pdia;
                }
                visitedk[node] = false;
            }
            int jump = dia / 2;
            for (int i = 19; i >= 0; i--)
            {
                if (jump >= (1 << i))
                {
                    n1 = parent[n1][i];
                    jump -= (1 << i);
                }
            }
            if (dia & 1)
            {
                cout << 2 << " " << min(n1, parent[n1][0]) << " " << max(n1, parent[n1][0]) << endl;
            }
            else
            {
                cout << 1 << " " << n1 << endl;
            }
        }
    }
}