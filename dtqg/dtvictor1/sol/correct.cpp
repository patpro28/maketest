#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, m;
    if (!(std::cin >> n >> k >> m)) return 0;
    std::vector<int> guard(n + 1);
    for (int u = 1; u <= n; ++u) std::cin >> guard[u];

    std::vector<std::vector<int>> edges(n + 1), children(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    std::vector<int> parent(n + 1), order{1};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : edges[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            children[u].push_back(v);
            order.push_back(v);
        }
    }

    std::vector<int> seen(k + 1), stack;
    stack.reserve(n);
    for (int event = 1; event <= m; ++event) {
        int type, u;
        std::cin >> type >> u;
        if (type == 1) {
            std::cin >> guard[u];
            continue;
        }

        int distinct = 0;
        stack.push_back(u);
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            if (seen[guard[v]] != event) {
                seen[guard[v]] = event;
                ++distinct;
            }
            for (int child : children[v]) stack.push_back(child);
        }
        std::cout << distinct << '\n';
    }
}
