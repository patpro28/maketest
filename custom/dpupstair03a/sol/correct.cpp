#include <array>
#include <iostream>
#include <vector>

constexpr int MOD = 1000000007;
void add(int &target, int value) {
    target += value;
    if (target >= MOD) target -= MOD;
}

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
    std::array<std::array<int, 31>, 3> dp{};
    dp[1][0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int ways = dp[i % 3][j];
            int next_count = j + 0;
            if (next_count <= m) add(dp[(i + 1) % 3][next_count], ways);
            if (!slippery[i] && i + 2 <= n) {
                next_count = j + 1;
                if (next_count <= m) add(dp[(i + 2) % 3][next_count], ways);
            }
        }
        dp[i % 3].fill(0);
    }
    std::cout << dp[n % 3][m] << '\n';
}
