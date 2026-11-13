#include <iostream>
#include <vector>

constexpr int MOD = 1000000007;

struct Result {
    long long value = -1;
    int ways = 0;

    void relax(long long candidate, int count) {
        if (candidate > value) {
            value = candidate;
            ways = count;
        } else if (candidate == value) {
            ways = (ways + count) % MOD;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, target;
    std::cin >> n >> target;
    std::vector<Result> best(target + 1);
    best[0] = {0, 1};
    for (int i = 0; i < n; ++i) {
        int type, weight;
        long long value;
        std::cin >> type >> weight >> value;
        if (weight > target) continue;
        const int start = type == 0 ? target : weight;
        const int end = type == 0 ? weight - 1 : target + 1;
        const int step = type == 0 ? -1 : 1;
        for (int sum = start; sum != end; sum += step) {
            const auto source = best[sum - weight];
            if (source.value >= 0) best[sum].relax(source.value + value, source.ways);
        }
    }
    std::cout << best[target].value << ' ' << best[target].ways << '\n';
}
