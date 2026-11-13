#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::string a, b;
    std::cin >> n >> m >> a >> b;
    std::vector<int> previous(m + 1), current(m + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            current[j] = std::max(previous[j], current[j - 1]);
            if (a[i - 1] == b[j - 1]) {
                current[j] = std::max(current[j], previous[j - 1] + 1);
            }
        }
        previous.swap(current);
    }
    std::cout << previous[m] << '\n';
}
