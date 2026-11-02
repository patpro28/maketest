#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

long long target;

bool matches(long long sum) {
    return sum == target;
}

int main() {
    int n, k;
    if (scanf("%d%d%lld", &n, &k, &target) != 3) return 0;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x;
        if (scanf("%lld", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + x;
    }
    int answer = 0;
    for (int r = k; r <= n; ++r)
        if (matches(prefix[r] - prefix[r - k])) ++answer;
    printf("%d\n", answer);
}
