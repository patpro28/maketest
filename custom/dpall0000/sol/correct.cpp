#include <algorithm>
#include <iostream>
#include <limits>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    long long twoBack = std::numeric_limits<long long>::max();
    long long previous = 0;
    for (int i = 0; i < n; ++i) {
        long long fee;
        std::cin >> fee;
        const long long current = fee + std::min(previous, twoBack);
        twoBack = previous;
        previous = current;
    }
    std::cout << previous << '\n';
}
