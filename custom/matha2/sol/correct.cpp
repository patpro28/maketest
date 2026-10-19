#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        long long l, r, a;
        std::cin >> l >> r >> a;
        long long answer = r / (2 * a) - (l - 1) / (2 * a);
        std::cout << answer << '\n';
    }
}
