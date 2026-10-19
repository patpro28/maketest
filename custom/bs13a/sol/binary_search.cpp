#include <algorithm>
#include <iostream>
#include <vector>

// Return the number of elements strictly smaller than target.
int count_less(const std::vector<long long> &a, long long target) {
    int left = 0, right = static_cast<int>(a.size());
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (a[middle] < target) left = middle + 1;
        else right = middle;
    }
    return left;
}

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
        long long left = x - k, right = x;
        std::cout << count_less(a, right + 1) - count_less(a, left) << '\n';
    }
}
