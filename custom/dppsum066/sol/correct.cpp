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
    int n, k, required;
    if (scanf("%d%d%d", &n, &k, &required) != 3) return 0;
    prepare();
    vector<long long> sums(n + 1);
    vector<int> counts(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) return 0;
        sums[i] = sums[i - 1] + x;
        counts[i] = counts[i - 1] + matches(x);
    }
    bool found = false;
    long long best = 0;
    int position = 0;
    for (int r = k; r <= n; ++r) {
        int count = counts[r] - counts[r - k];
        if (count < required) continue;
        long long total = sums[r] - sums[r - k];
        if (!found || total > best) {
            found = true;
            best = total;
            position = r - k + 1;
        }
    }
    if (!found) printf("NONE\n");
    else printf("%lld %d\n", best, position);
}
