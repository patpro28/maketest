#include <array>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    vector<long long> p(n + 1);
    long long previous = 0;
    for (int i = 1; i <= n; ++i) {
        long long x; if (scanf("%lld", &x) != 1) return 0;
        p[i] = p[i-1];
        if (i > 1) {
            p[i] += ((x % 2 == 0) != (previous % 2 == 0));
        }
        previous = x;
    }
    while (q--) {
        int l, r; if (scanf("%d%d", &l, &r) != 2) return 0;
        printf("%lld\n", p[r]-p[l]);
    }
}
