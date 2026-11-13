#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, budget;
    std::string a, b;
    std::cin >> n >> m >> budget >> a >> b;
    std::vector<int> costA(n), costB(m);
    std::array<long long, 26> score;
    for (int& cost : costA) std::cin >> cost;
    for (int& cost : costB) std::cin >> cost;
    for (long long& points : score) std::cin >> points;

    const int stride = budget + 1;
    std::vector<long long> previous((m + 1) * stride, -1);
    for (int j = 0; j <= m; ++j) previous[j * stride] = 0;
    std::vector<long long> current(previous);
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            const int cell = j * stride;
            const int left = cell - stride;
            const int cost = costA[i] + costB[j - 1];
            for (int s = 0; s <= budget; ++s) {
                long long best = std::max(previous[cell + s], current[left + s]);
                if (a[i] == b[j - 1] && s >= cost && previous[left + s - cost] >= 0) {
                    best = std::max(best, previous[left + s - cost] + score[a[i] - 'a']);
                }
                current[cell + s] = best;
            }
        }
        previous.swap(current);
    }
    std::cout << previous.back() << '\n';
}
