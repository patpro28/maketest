#include "params.h"
#include "testlib.h"
#include <charconv>

struct Relation {
    int u, v;
    std::string op;
};

inline Relation readRelation(InStream& stream, int n) {
    std::string token = stream.readToken();
    auto middle = token.find_first_of("<=>");
    auto right = token.find_first_of("0123456789", middle);
    ensuref(middle != std::string::npos && right != std::string::npos,
            "Expected a relation i<j, i>j, i<=j, i>=j or i=j");
    std::string op = token.substr(middle, right - middle);
    ensuref(op == "<" || op == ">" || op == "<=" || op == ">=" || op == "=",
            "Invalid relation operator");

    int u = 0, v = 0;
    const char* start = token.data();
    auto leftResult = std::from_chars(start, start + middle, u);
    auto rightResult = std::from_chars(start + right, start + token.size(), v);
    ensuref(leftResult.ec == std::errc() && leftResult.ptr == start + middle &&
            rightResult.ec == std::errc() && rightResult.ptr == start + token.size() &&
            1 <= u && u <= n && 1 <= v && v <= n,
            "Invalid variable index");
    return {u - 1, v - 1, op};
}

// Iterative Tarjan traversal, with a cursor for the next edge of each DFS frame.
std::vector<int> components(const std::vector<std::vector<int>>& graph) {
    int n = static_cast<int>(graph.size());
    std::vector<int> enter(n, -1), low(n), component(n, -1);
    std::vector<size_t> next(n);
    std::vector<int> dfs, active;
    int time = 0, id = 0;
    auto enterVertex = [&](int u) {
        enter[u] = low[u] = time++;
        dfs.push_back(u);
        active.push_back(u);
    };

    for (int root = 0; root < n; ++root) {
        if (enter[root] != -1) continue;
        enterVertex(root);
        while (!dfs.empty()) {
            int u = dfs.back();
            if (next[u] < graph[u].size()) {
                int v = graph[u][next[u]++];
                if (enter[v] == -1) enterVertex(v);
                else if (component[v] == -1) low[u] = std::min(low[u], enter[v]);
                continue;
            }
            if (low[u] == enter[u]) {
                int v;
                do {
                    v = active.back();
                    active.pop_back();
                    component[v] = id;
                } while (v != u);
                ++id;
            }
            dfs.pop_back();
            if (!dfs.empty()) low[dfs.back()] = std::min(low[dfs.back()], low[u]);
        }
    }
    return component;
}

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n");
    inf.readSpace();
    int m = inf.readInt(1, M_MAX, "m");
    inf.readEoln();

    std::vector<std::vector<int>> graph(n);
    std::vector<std::pair<int, int>> strictEdges;
    for (int i = 0; i < m; ++i) {
        auto [u, v, op] = readRelation(inf, n);
        inf.readEoln();
        if (op[0] == '>') std::swap(u, v);
        graph[u].push_back(v);
        if (op == "=") graph[v].push_back(u);
        if (op == "<" || op == ">") strictEdges.emplace_back(u, v);
    }
    inf.readEof();

    auto component = components(graph);
    for (auto [u, v] : strictEdges) {
        ensuref(component[u] != component[v], "The relations are inconsistent");
    }
}
