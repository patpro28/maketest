#include <algorithm>
#include <iostream>
#include <vector>

long long choose3(long long n) { return n < 3 ? 0 : n * (n - 1) * (n - 2) / 6; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t; std::cin >> t;
    while (t--) {
        int n, q; std::cin >> n >> q;
        std::vector<int> a(n);
        for (int &v : a) std::cin >> v;
        std::sort(a.begin(), a.end());
        long long total = choose3(n);
        while (q--) {
            long long k; std::cin >> k;
            int left = 1, right = n - 2;
            while (left < right) {
                int middle = left + (right - left) / 2;
                long long cumulative = total - choose3(n - middle);
                if (cumulative >= k) right = middle;
                else left = middle + 1;
            }
            std::cout << a[left - 1] << '\n';
        }
    }
}
