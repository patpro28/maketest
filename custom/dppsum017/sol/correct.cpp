#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

const int LIMIT = 1000000;
vector<bool> prime(LIMIT + 1, true);
void prepare() {
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= LIMIT; ++i)
        if (prime[i])
            for (int j = i * i; j <= LIMIT; j += i) prime[j] = false;
}
bool matches(int x) { return prime[x]; }

int main() {
    int n, q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    prepare();
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
