#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n);
    for (long long &value : a) std::cin >> value;
    std::sort(a.begin(), a.end());
    while (q--) {
        long long x, k;
        std::cin >> x >> k;
        long long left = x, right = x + k;
        auto first = std::lower_bound(a.begin(), a.end(), left);
        auto after = std::upper_bound(a.begin(), a.end(), right);
        std::cout << after - first << '\n';
    }
}
