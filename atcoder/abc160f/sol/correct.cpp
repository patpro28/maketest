#include <cstdio>
#include <vector>

constexpr long long MOD = 1000000007;

int main() {
    int n;
    if (std::scanf("%d", &n) != 1) return 0;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::scanf("%d%d", &a, &b);
        --a;
        --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // Traverse iteratively so a path of length 200000 cannot overflow the stack.
    std::vector<int> parent(n, -1), order;
    order.reserve(n);
    order.push_back(0);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : graph[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            order.push_back(v);
        }
    }

    std::vector<int> size(n, 1);
    for (int i = n - 1; i > 0; --i) {
        int u = order[i];
        size[parent[u]] += size[u];
    }

    std::vector<long long> inverse(n + 1);
    inverse[1] = 1;
    long long factorial = 1;
    for (int i = 2; i <= n; ++i) {
        inverse[i] = MOD - (MOD / i) * inverse[MOD % i] % MOD;
        factorial = factorial * i % MOD;
    }

    std::vector<long long> answer(n);
    answer[0] = factorial;
    for (int u = 0; u < n; ++u) {
        answer[0] = answer[0] * inverse[size[u]] % MOD;
    }
    for (int i = 1; i < n; ++i) {
        int u = order[i];
        answer[u] = answer[parent[u]] * size[u] % MOD
                    * inverse[n - size[u]] % MOD;
    }

    for (long long value : answer) std::printf("%lld\n", value);
}
