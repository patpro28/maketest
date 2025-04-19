#include <bits/stdc++.h>
using namespace std;

//----------------------------------------------------------------------
#define JAI_SHREE_RAM cin.sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define int long long
#define pii pair<int, int>
#define vpl vector<pair<int, int>>
#define f(i, k, n) for (int i = k; i < n; i++)
#define endl '\n'

//----------------------------------------------------------------------
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n, -1);
        rank.resize(n, 1);
    }
    int find(int i) {
        if (parent[i] == -1) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};

//----------------------------------------------------------------------
class Graph {
    vector<tuple<int, int, int>> edges; // weight, u, v
    int V;
public:
    Graph(int V) : V(V) {}
    void addEdge(int x, int y, int w) {
        edges.emplace_back(w, x, y);
    }
    void kruskals_mst() {
        sort(edges.begin(), edges.end());
        DSU s(V);
        int maxEdgeWeight = 0;

        for (auto &[w, x, y] : edges) {
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                maxEdgeWeight = max(maxEdgeWeight, w);
            }
        }
        cout << maxEdgeWeight << endl;
    }
};

//----------------------------------------------------------------------
void Solve() {
    int n;
    cin >> n;
    vpl v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    Graph g(n);
    f(i, 0, n) f(j, i + 1, n) {
        int dx = abs(v[j].first - v[i].first);
        int dy = abs(v[j].second - v[i].second);
        int weight = max(dx, dy);
        if (dy == 0) weight = (dx + 1) / 2;
        if (dx == 0) weight = (dy + 1) / 2;
        g.addEdge(i, j, weight);
    }

    g.kruskals_mst();
}

//----------------------------------------------------------------------
int32_t main() {
    JAI_SHREE_RAM;
    int tc;
    cin >> tc;
    while (tc--) {
        Solve();
    }
    return 0;
}