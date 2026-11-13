#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int to, weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> graph(n);
    vector<vector<int>> reverseGraph(n);
    auto add = [&](int u, int v, int weight) {
        graph[u].push_back({v, weight});
        reverseGraph[v].push_back(u);
    };
    for (int i = 0; i < m; ++i) {
        int u, v;
        char op;
        cin >> u >> op;
        bool strict = op != '=' && cin.peek() != '=';
        if (op != '=' && !strict) cin.get();
        cin >> v;
        --u;
        --v;
        if (op == '>') swap(u, v);
        add(u, v, strict);
        if (op == '=') add(v, u, 0);
    }

    vector<char> seen(n);
    vector<int> order;
    vector<pair<int, size_t>> dfs;
    for (int root = 0; root < n; ++root) {
        if (seen[root]) continue;
        seen[root] = true;
        dfs.emplace_back(root, 0);
        while (!dfs.empty()) {
            auto& [u, next] = dfs.back();
            if (next == graph[u].size()) {
                order.push_back(u);
                dfs.pop_back();
            } else {
                int v = graph[u][next++].to;
                if (!seen[v]) {
                    seen[v] = true;
                    dfs.emplace_back(v, 0);
                }
            }
        }
    }

    vector<int> component(n, -1);
    vector<vector<int>> groups;
    vector<int> pending;
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int root = *it;
        if (component[root] != -1) continue;
        int id = static_cast<int>(groups.size());
        groups.emplace_back();
        component[root] = id;
        pending.push_back(root);
        while (!pending.empty()) {
            int u = pending.back();
            pending.pop_back();
            groups.back().push_back(u);
            for (int v : reverseGraph[u]) {
                if (component[v] == -1) {
                    component[v] = id;
                    pending.push_back(v);
                }
            }
        }
    }

    // Kosaraju assigns component IDs in topological order.
    vector<int> value(groups.size());
    for (int id = 0; id < static_cast<int>(groups.size()); ++id) {
        for (int u : groups[id]) {
            for (auto [v, weight] : graph[u]) {
                int next = component[v];
                if (id != next) value[next] = max(value[next], value[id] + weight);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << value[component[i]] << (i + 1 == n ? '\n' : ' ');
    }
}
