/*
Author: Tu Pham Anh
Date: 2024/10/26 - 22:19
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
queue<int> qu;
int dist[N];

void bfs(int t) {
    while (!qu.empty()) {
        int u = qu.front();
        if (dist[u] == t) break;
        qu.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                qu.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(dist, -1, sizeof(dist));
    int now = 0;
    while (q--) {
        int type, s;
        cin >> type >> s;
        if (type == 1) {
            if (dist[s] == -1) {
                dist[s] = now;
                qu.push(s);
            }
        }
        if (type == 2) {
            now += s;
            bfs(now);
        }
        if (type == 3) 
            cout << (dist[s] >= 0 ? "YES" : "NO") << '\n';
    }
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}