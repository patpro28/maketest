#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

constexpr int MOD = 1000000007;
constexpr long long INF = 1LL << 60;

struct Result {
    long long cost = INF;
    int ways = 0;

    void relax(long long candidate, int count) {
        if (candidate < cost) {
            cost = candidate;
            ways = count;
        } else if (candidate == cost) {
            ways = (ways + count) % MOD;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<long long> fee(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> fee[i];

    std::vector<std::array<Result, 4>> best(n + 1);
    best[0][0] = {0, 1};
    for (int i = 0; i < n; ++i) {
        for (int last = 0; last <= 3; ++last) {
            const auto [cost, ways] = best[i][last];
            if (cost == INF) continue;
            for (int jump = 1; jump <= 3 && i + jump <= n; ++jump) {
                if (jump != last) {
                    best[i + jump][jump].relax(cost + fee[i + jump], ways);
                }
            }
        }
    }

    Result answer;
    for (int last = 1; last <= 3; ++last) {
        answer.relax(best[n][last].cost, best[n][last].ways);
    }
    std::cout << answer.cost << ' ' << answer.ways << '\n';
}
