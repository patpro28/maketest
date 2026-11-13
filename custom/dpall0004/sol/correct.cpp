#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

constexpr long long INF = 1LL << 60;
enum Direction { RIGHT, DOWN };
using Costs = std::array<long long, 2>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rows, cols, turns;
    std::cin >> rows >> cols >> turns;
    std::vector<std::vector<long long>> fee(rows, std::vector<long long>(cols));
    for (auto& row : fee) {
        for (auto& cell : row) std::cin >> cell;
    }
    if (fee[0][0] == -1 || fee.back().back() == -1) {
        std::cout << -1 << '\n';
        return 0;
    }
    if (rows == 1 && cols == 1) {
        std::cout << (turns == 0 ? fee[0][0] : -1) << '\n';
        return 0;
    }

    const int stride = turns + 1;
    std::vector<Costs> previous(cols * stride, {INF, INF});
    std::vector<Costs> current(previous);
    for (int i = 0; i < rows; ++i) {
        std::fill(current.begin(), current.end(), Costs{INF, INF});
        for (int j = 0; j < cols; ++j) {
            if (fee[i][j] == -1) continue;
            const int cell = j * stride;
            if (i + j == 1) {
                current[cell][i == 0 ? RIGHT : DOWN] = fee[0][0] + fee[i][j];
                continue;
            }
            for (int k = 0; k <= turns; ++k) {
                if (j > 0) {
                    const int left = cell - stride + k;
                    const long long best = std::min(current[left][RIGHT],
                        k > 0 ? current[left - 1][DOWN] : INF);
                    if (best != INF) current[cell + k][RIGHT] = best + fee[i][j];
                }
                if (i > 0) {
                    const int above = cell + k;
                    const long long best = std::min(previous[above][DOWN],
                        k > 0 ? previous[above - 1][RIGHT] : INF);
                    if (best != INF) current[cell + k][DOWN] = best + fee[i][j];
                }
            }
        }
        previous.swap(current);
    }
    const auto [right, down] = previous.back();
    const long long answer = std::min(right, down);
    std::cout << (answer == INF ? -1 : answer) << '\n';
}
