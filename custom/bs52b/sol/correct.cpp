#include <algorithm>
#include <iostream>
#include <vector>

long long choose3(long long n) { return n * (n - 1) * (n - 2) / 6; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t; std::cin >> t;
    while (t--) {
        int n, q; std::cin >> n >> q;
        std::vector<int> a(n);
        for (int &v : a) std::cin >> v;
        std::sort(a.begin(), a.end());
        while (q--) {
            long long k; std::cin >> k;
            int left = 3, right = n;
            while (left < right) {
                int middle = left + (right - left) / 2;
                if (choose3(middle) >= k) right = middle;
                else left = middle + 1;
            }
            std::cout << a[left - 1] << '\n';
        }
    }
}
