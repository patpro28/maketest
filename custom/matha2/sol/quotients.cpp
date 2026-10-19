#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        long long l, r, a;
        std::cin >> l >> r >> a;
        // Valid multiples are a*k, with ceil(l/a) <= k <= floor(r/a).
        long long first = l / a + (l % a != 0);
        long long last = r / a;
        if (first % 2 != 0) ++first;
        long long answer = first > last ? 0 : (last - first) / 2 + 1;
        std::cout << answer << '\n';
    }
}
