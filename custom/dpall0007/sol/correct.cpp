#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> latestStart(m + 1);
    for (int i = 0; i < n; ++i) {
        int left, right;
        std::cin >> left >> right;
        latestStart[right] = std::max(latestStart[right], left);
    }
    long long answer = 0;
    int boundary = 0;
    for (int right = 1; right <= m; ++right) {
        boundary = std::max(boundary, latestStart[right]);
        answer += right - boundary;
    }
    std::cout << answer << '\n';
}
