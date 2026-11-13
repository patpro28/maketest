#include <algorithm>
#include <cstdio>
#include <iterator>
#include <set>
#include <utility>
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

class RangeMinimum {
    std::vector<int> logarithm;
    std::vector<std::vector<int>> table;

public:
    explicit RangeMinimum(std::vector<int> values) : logarithm(values.size() + 1) {
        int n = static_cast<int>(values.size());
        for (int i = 2; i <= n; ++i) logarithm[i] = logarithm[i / 2] + 1;
        table.reserve(logarithm[n] + 1);
        table.push_back(std::move(values));
        for (int length = 2; length <= n; length *= 2) {
            const auto& previous = table.back();
            std::vector<int> row(n - length + 1);
            for (int i = 0; i + length <= n; ++i) {
                row[i] = std::min(previous[i], previous[i + length / 2]);
            }
            table.push_back(std::move(row));
        }
    }

    int minimum(int left, int right) const {
        if (left > right) std::swap(left, right);
        int level = logarithm[right - left + 1];
        return std::min(table[level][left], table[level][right - (1 << level) + 1]);
    }
};

class Fenwick {
    std::vector<int> bit;

public:
    explicit Fenwick(std::vector<int> weights) : bit(std::move(weights)) {
        for (int p = 1; p < static_cast<int>(bit.size()); ++p) {
            int next = p + (p & -p);
            if (next < static_cast<int>(bit.size())) bit[next] += bit[p];
        }
    }

    void add(int p, int delta) {
        for (; p < static_cast<int>(bit.size()); p += p & -p) bit[p] += delta;
    }

    int prefix(int p) const {
        int result = 0;
        for (; p > 0; p -= p & -p) result += bit[p];
        return result;
    }
};

struct Edge {
    int to, next;
};

struct Frame {
    int position, nextEdge;
};

int main() {
    Input input;
    int n = input.integer();
    if (n == 0) return 0;
    int k = input.integer(), m = input.integer();
    std::vector<int> guardByCity(n + 1);
    for (int u = 1; u <= n; ++u) guardByCity[u] = input.integer();

    std::vector<int> head(n + 1, -1);
    std::vector<Edge> edges;
    edges.reserve(2 * (n - 1));
    auto addEdge = [&](int u, int v) {
        edges.push_back({v, head[u]});
        head[u] = static_cast<int>(edges.size()) - 1;
    };
    for (int i = 1; i < n; ++i) {
        int u = input.integer(), v = input.integer();
        addEdge(u, v);
        addEdge(v, u);
    }

    std::vector<int> pos(n + 1), last(n + 1), first(n + 1), guard(n + 1), euler;
    euler.reserve(2 * n - 1);
    std::vector<Frame> stack;
    stack.reserve(n);
    int timer = 0;
    auto enter = [&](int u) {
        int p = pos[u] = ++timer;
        guard[p] = guardByCity[u];
        first[p] = static_cast<int>(euler.size());
        euler.push_back(p);
        stack.push_back({p, head[u]});
    };
    enter(1);
    while (!stack.empty()) {
        Frame& frame = stack.back();
        if (frame.nextEdge == -1) {
            last[frame.position] = timer;
            stack.pop_back();
            if (!stack.empty()) euler.push_back(stack.back().position);
        } else {
            Edge edge = edges[frame.nextEdge];
            frame.nextEdge = edge.next;
            if (pos[edge.to] == 0) enter(edge.to);
        }
    }

    RangeMinimum rmq(std::move(euler));
    auto lca = [&](int p, int q) { return rmq.minimum(first[p], first[q]); };

    using Positions = std::set<int>;
    std::vector<Positions> group(k + 1);
    std::vector<int> weight(n + 1, 1);
    for (int p = 1; p <= n; ++p) {
        auto& positions = group[guard[p]];
        if (!positions.empty()) --weight[lca(*positions.rbegin(), p)];
        positions.emplace_hint(positions.end(), p);
    }
    Fenwick sums(std::move(weight));

    auto attachment = [&](int p, const Positions& positions,
                          Positions::const_iterator split, Positions::const_iterator right) {
        int leftAncestor = split == positions.begin() ? 0 : lca(p, *std::prev(split));
        int rightAncestor = right == positions.end() ? 0 : lca(p, *right);
        return std::max(leftAncestor, rightAncestor);
    };

    while (m--) {
        int type = input.integer(), u = input.integer();
        int p = pos[u];
        if (type == 2) {
            std::printf("%d\n", sums.prefix(last[p]) - sums.prefix(p - 1));
            continue;
        }
        int newGuard = input.integer();
        if (newGuard == guard[p]) continue;

        auto& oldGroup = group[guard[p]];
        auto old = oldGroup.find(p);
        int oldAncestor = attachment(p, oldGroup, old, std::next(old));
        oldGroup.erase(old);

        auto& newGroup = group[newGuard];
        auto next = newGroup.lower_bound(p);
        int newAncestor = attachment(p, newGroup, next, next);
        newGroup.emplace_hint(next, p);
        guard[p] = newGuard;

        if (oldAncestor != newAncestor) {
            if (oldAncestor != 0) sums.add(oldAncestor, 1);
            if (newAncestor != 0) sums.add(newAncestor, -1);
        }
    }
}
