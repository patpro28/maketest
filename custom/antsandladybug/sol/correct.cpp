#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

int n, k;
vector<int> adj[N], ans(N), pos(N), par(N);
vector<vector<pair<int, int>>> newAdj;
vector<pair<int, int>> trace;
vector<int> hist;

void dfs(int u, int time) {
    hist[u] = time;
    for (auto [v, t]: newAdj[u])
        dfs(v, min(time, t));
}

void makeTree(int u, int p) {
    par[u] = p;
    for (int v: adj[u])
        if (v != p)
            makeTree(v, u);
}

void bfs(int s) {
    makeTree(s, -1);
    queue<int> q;
    trace.assign(n + 1, make_pair(-1, -1));
    newAdj.assign(k + 1, vector<pair<int, int>>());
    hist.assign(n + 1, -1);
    for (int i = 0; i < k; ++i) {
        q.push(pos[i]);
        trace[pos[i]] = make_pair(i, 0);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int p = par[u];
        if (p == -1) continue;
        if (trace[p].first == -1) {
            q.push(p);
            trace[p] = make_pair(trace[u].first, trace[u].second + 1);
        } else {
            auto [ant, time] = trace[p];
            if (time > trace[u].second) time--;
            newAdj[ant].push_back({trace[u].first, time});
        }
    }
    dfs(trace[s].first, trace[s].second);
    for (int i = 1; i <= n; ++i)
        if (trace[i].first != -1 and trace[i].second == hist[trace[i].first])
            pos[trace[i].first] = i;
    ans[trace[s].first]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        pos[i] = x;
    }
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        bfs(x);
    }
    for (int i = 0; i < k; ++i)
        cout << pos[i] << ' ' << ans[i] << '\n';
    return 0;
}