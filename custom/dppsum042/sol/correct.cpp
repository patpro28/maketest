#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n, k;
    if (scanf("%d%d", &n, &k) != 2) return 0;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x;
        if (scanf("%lld", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + x;
    }
    long long best = prefix[k];
    for (int r = k + 1; r <= n; ++r) {
        long long value = prefix[r] - prefix[r - k];
        if (value < best) {
            best = value;
        }
    }
    printf("%lld\n", best);
}
