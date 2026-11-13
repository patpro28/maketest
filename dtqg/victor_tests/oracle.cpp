#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, m;
    if (!(std::cin >> n >> k >> m)) return 0;
    std::vector<int> guard(n + 1), count(k + 1);
    int active = 0;
    for (int u = 1; u <= n; ++u) {
        std::cin >> guard[u];
        if (count[guard[u]]++ == 0) ++active;
    }

    std::vector<std::vector<int>> edges(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    std::vector<int> parent(n + 1), queue{1};
    queue.reserve(n);
    for (int i = 0; i < n; ++i) {
        for (int v : edges[queue[i]]) {
            if (v != parent[queue[i]]) {
                parent[v] = queue[i];
                queue.push_back(v);
            }
        }
    }

    std::vector<int> seen(k + 1);
    for (int event = 1; event <= m; ++event) {
        int type, u;
        std::cin >> type >> u;
        if (type == 1) {
            if (--count[guard[u]] == 0) --active;
            std::cin >> guard[u];
            if (count[guard[u]]++ == 0) ++active;
            continue;
        }
        if (u == 1) {
            std::cout << active << '\n';
            continue;
        }

        int distinct = 0;
        queue.clear();
        queue.push_back(u);
        for (std::size_t i = 0; i < queue.size(); ++i) {
            int v = queue[i];
            if (seen[guard[v]] != event) {
                seen[guard[v]] = event;
                if (++distinct == active) break;
            }
            for (int w : edges[v]) {
                if (w != parent[v]) queue.push_back(w);
            }
        }
        std::cout << distinct << '\n';
    }
}
