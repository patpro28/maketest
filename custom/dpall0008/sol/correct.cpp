#include <algorithm>
#include <array>
#include <iostream>
#include <string>

constexpr int COLORS = 4;
constexpr long long UNREACHABLE = -(1LL << 60);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string colors;
    std::cin >> n >> colors;
    colors = 'D' + colors + 'D';

    std::array<std::array<long long, COLORS>, COLORS> score{};
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) std::cin >> score[x][y];
    }
    std::array<std::array<long long, COLORS>, COLORS> bestStart;
    for (auto& row : bestStart) row.fill(UNREACHABLE);

    long long original = 0;
    long long prefix = 0;
    long long bestGain = 0;
    for (int right = 1; right <= n; ++right) {
        const int before = colors[right - 1] - 'A';
        const int end = colors[right] - 'A';
        const int after = colors[right + 1] - 'A';
        const long long outgoing = score[end][after];

        auto& start = bestStart[before][end];
        start = std::max(start, -prefix - score[before][end]);
        for (int x = 0; x < COLORS; ++x) {
            for (int y = 0; y < COLORS; ++y) {
                if (bestStart[x][y] == UNREACHABLE) continue;
                const long long gain = bestStart[x][y] + prefix - outgoing
                    + score[x][end] + score[y][after];
                bestGain = std::max(bestGain, gain);
            }
        }
        original += outgoing;
        prefix += score[after][end] - outgoing;
    }
    std::cout << original + bestGain << '\n';
}
