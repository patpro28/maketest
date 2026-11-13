#include <algorithm>
#include <cstdio>
#include <iterator>
#include <set>
#include <vector>

class Input {
    char buffer[1 << 16];
    std::size_t position = 0, length = 0;

    int nextChar() {
        if (position == length) {
            length = std::fread(buffer, 1, sizeof(buffer), stdin);
            position = 0;
            if (length == 0) return EOF;
        }
        return buffer[position++];
    }

public:
    int integer() {
        int ch;
        do {
            ch = nextChar();
            if (ch == EOF) return 0;
        } while (ch < '0' || ch > '9');

        int value = 0;
        do {
            value = value * 10 + ch - '0';
            ch = nextChar();
        } while (ch >= '0' && ch <= '9');
        return value;
    }
};

class Fenwick {
    std::vector<int> bit;

public:
    explicit Fenwick(int n) : bit(n + 1) {}

    void add(int p, int delta) {
        for (; p < static_cast<int>(bit.size()); p += p & -p) bit[p] += delta;
    }

    int prefix(int p) const {
        int result = 0;
        for (; p > 0; p -= p & -p) result += bit[p];
        return result;
    }
};

int main() {
    Input input;
    int n = input.integer();
    if (n == 0) return 0;
    int k = input.integer(), m = input.integer();
    std::vector<int> guard(n + 1);
    for (int u = 1; u <= n; ++u) guard[u] = input.integer();

    std::vector<std::vector<int>> edges(n + 1);
    for (int i = 1; i < n; ++i) {
        int u = input.integer(), v = input.integer();
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    std::vector<int> parent(n + 1), depth(n + 1), order{1};
    order.reserve(n);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : edges[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }

    std::vector<int> size(n + 1, 1), heavy(n + 1);
    for (int i = n - 1; i > 0; --i) {
        int u = order[i], p = parent[u];
        size[p] += size[u];
        if (heavy[p] == 0 || size[u] > size[heavy[p]]) heavy[p] = u;
    }

    std::vector<int> head(n + 1), pos(n + 1), city(n + 1), pending{1};
    int timer = 0;
    while (!pending.empty()) {
        int h = pending.back();
        pending.pop_back();
        for (int u = h; u != 0; u = heavy[u]) {
            head[u] = h;
            pos[u] = ++timer;
            city[timer] = u;
            for (int v : edges[u]) {
                if (v != parent[u] && v != heavy[u]) pending.push_back(v);
            }
        }
    }

    auto lca = [&](int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) std::swap(u, v);
            u = parent[head[u]];
        }
        return depth[u] < depth[v] ? u : v;
    };

    Fenwick coverage(n);
    auto addPath = [&](int u, int stop, int delta) {
        while (head[u] != head[stop]) {
            coverage.add(pos[head[u]], delta);
            coverage.add(pos[u] + 1, -delta);
            u = parent[head[u]];
        }
        if (u != stop) {
            coverage.add(pos[stop] + 1, delta);
            coverage.add(pos[u] + 1, -delta);
        }
    };

    using Positions = std::set<int>;
    auto attachment = [&](int u, const Positions& positions,
                          Positions::const_iterator split, Positions::const_iterator right) {
        int leftAncestor = 0, rightAncestor = 0;
        if (split != positions.begin()) leftAncestor = lca(u, city[*std::prev(split)]);
        if (right != positions.end()) rightAncestor = lca(u, city[*right]);
        return pos[leftAncestor] > pos[rightAncestor] ? leftAncestor : rightAncestor;
    };

    std::vector<Positions> group(k + 1);
    for (int p = 1; p <= n; ++p) {
        int u = city[p];
        auto& positions = group[guard[u]];
        int stop = positions.empty() ? 0 : lca(u, city[*positions.rbegin()]);
        addPath(u, stop, 1);
        positions.emplace_hint(positions.end(), p);
    }

    while (m--) {
        int type = input.integer(), u = input.integer();
        if (type == 2) {
            std::printf("%d\n", coverage.prefix(pos[u]));
            continue;
        }
        int newGuard = input.integer();
        if (newGuard == guard[u]) continue;

        auto& oldGroup = group[guard[u]];
        auto old = oldGroup.find(pos[u]);
        addPath(u, attachment(u, oldGroup, old, std::next(old)), -1);
        oldGroup.erase(old);

        auto& newGroup = group[newGuard];
        auto next = newGroup.lower_bound(pos[u]);
        addPath(u, attachment(u, newGroup, next, next), 1);
        newGroup.emplace_hint(next, pos[u]);
        guard[u] = newGuard;
    }
}
