#include <array>
#include <iostream>
#include <vector>

constexpr int MOD = 1000000007;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k, m;
    std::cin >> n >> k >> m;
    std::vector<bool> slippery(n + 1, false);
    for (int i = 0; i < k; ++i) {
        int b; std::cin >> b;
        slippery[b] = true;
    }
    // ways[i][j]: paths from i to n that add exactly j counted events.
    std::vector<std::array<int, 31>> ways(n + 1);
    ways[n][0] = 1;
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 0; j <= m; ++j) {
            int first = 0;
            long long total = j >= first ? ways[i + 1][j - first] : 0;
            if (!slippery[i] && i + 2 <= n) {
                int second = 1;
                if (j >= second) total += ways[i + 2][j - second];
            }
            ways[i][j] = total % MOD;
        }
    }
    std::cout << ways[1][m] << '\n';
}
