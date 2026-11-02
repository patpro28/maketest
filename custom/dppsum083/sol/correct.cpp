#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n;
    long long target;
    if (scanf("%d%lld", &n, &target) != 2) return 0;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x;
        if (scanf("%lld", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + x;
    }
    int left = 1, best = n + 1;
    int best_left = 0, best_right = 0;
    for (int right = 1; right <= n; ++right) {
        while (left <= right && prefix[right] - prefix[left - 1] >= target) {
            int length = right - left + 1;
            if (length < best) {
                best = length;
                best_left = left; best_right = right;
            }
            ++left;
        }
    }
    if (best == n + 1) best = 0;
    printf("%d %d %d\n", best, best_left, best_right);
}
