#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t; std::cin >> t;
    while (t--) {
        int n, q; std::cin >> n >> q;
        std::vector<int> a(n);
        for (int &v : a) std::cin >> v;
        std::sort(a.begin(), a.end());
        // Assign each group to its rightmost position in the sorted array.
        std::vector<long long> prefix(n + 1, 0);
        for (int i = 3; i <= n; ++i)
            prefix[i] = prefix[i - 1] + 1LL * (i - 1) * (i - 2) / 2;
        while (q--) {
            long long k; std::cin >> k;
            auto it = std::lower_bound(prefix.begin(), prefix.end(), k);
            int position = static_cast<int>(it - prefix.begin());
            std::cout << a[position - 1] << '\n';
        }
    }
}
