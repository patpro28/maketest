#include <cstdio>
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

int lca(int u, int v, const std::vector<int>& depth,
        const std::vector<std::vector<int>>& up) {
    if (depth[u] < depth[v]) std::swap(u, v);
    int gap = depth[u] - depth[v];
    for (int j = 0; gap; ++j, gap >>= 1) {
        if (gap & 1) u = up[j][u];
    }
    if (u == v) return u;
    for (int j = static_cast<int>(up.size()) - 1; j >= 0; --j) {
        if (up[j][u] != up[j][v]) {
            u = up[j][u];
            v = up[j][v];
        }
    }
    return up[0][u];
}

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

    int levels = 1;
    while ((1 << levels) <= n) ++levels;
    std::vector<std::vector<int>> up(levels, std::vector<int>(n + 1));
    std::vector<int> depth(n + 1), preorder, stack{1};
    preorder.reserve(n);
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        preorder.push_back(u);
        for (int v : edges[u]) {
            if (v == up[0][u]) continue;
            up[0][v] = u;
            depth[v] = depth[u] + 1;
            stack.push_back(v);
        }
    }
    for (int j = 1; j < levels; ++j) {
        for (int u = 1; u <= n; ++u) up[j][u] = up[j - 1][up[j - 1][u]];
    }

    std::vector<int> last(k + 1), answer(n + 1, 1);
    for (int u : preorder) {
        int& previous = last[guard[u]];
        if (previous != 0) --answer[lca(previous, u, depth, up)];
        previous = u;
    }
    for (int i = n - 1; i > 0; --i) {
        int u = preorder[i];
        answer[up[0][u]] += answer[u];
    }

    while (m--) {
        input.integer();  // Query type is always 2.
        int u = input.integer();
        std::printf("%d\n", answer[u]);
    }
}
