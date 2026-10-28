#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

bool matches(int x) {
    int original = x;
    long long reversed = 0;
    do { reversed = reversed * 10 + x % 10; x /= 10; } while (x);
    return reversed == original;
}

int main() {
    int n, q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    vector<int> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + matches(x);
    }
    while (q--) {
        int l, r;
        if (scanf("%d%d", &l, &r) != 2) return 0;
        printf("%d\n", prefix[r] - prefix[l - 1]);
    }
}
