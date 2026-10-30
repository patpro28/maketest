#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

bool matches(int x) {
    while (x) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

int main() {
    int n, q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + (matches(x) ? x : 0LL);
    }
    while (q--) {
        int l, r;
        if (scanf("%d%d", &l, &r) != 2) return 0;
        printf("%lld\n", prefix[r] - prefix[l - 1]);
    }
}
