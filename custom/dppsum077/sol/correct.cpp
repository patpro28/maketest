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
    int n, m, q;
    if (scanf("%d%d%d", &n, &m, &q) != 3) return 0;
    prepare();
    vector<vector<long long>> prefix(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int x;
            if (scanf("%d", &x) != 1) return 0;
            long long value = matches(x);
            prefix[i][j] = value + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }
    while (q--) {
        int x1, y1, x2, y2;
        if (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) != 4) return 0;
        long long answer = prefix[x2][y2] - prefix[x1-1][y2] - prefix[x2][y1-1] + prefix[x1-1][y1-1];
        printf("%lld\n", answer);
    }
}
