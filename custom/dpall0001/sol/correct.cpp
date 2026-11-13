#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, target;
    std::cin >> n >> target;
    std::vector<long long> best(target + 1, -1);
    best[0] = 0;
    for (int i = 0; i < n; ++i) {
        int weight;
        long long value;
        std::cin >> weight >> value;
        for (int sum = target; sum >= weight; --sum) {
            if (best[sum - weight] >= 0) {
                best[sum] = std::max(best[sum], best[sum - weight] + value);
            }
        }
    }
    std::cout << best[target] << '\n';
}
