#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

int u, v;
bool matches(int x) { return u <= x && x <= v; }

int main() {
    int n, q;
    if (scanf("%d%d%d%d", &n, &q, &u, &v) != 4) return 0;
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
