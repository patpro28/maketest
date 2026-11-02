#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

bool matches(long long sum) {
    if (sum < 0) return false;
    long long root = static_cast<long long>(sqrt(static_cast<double>(sum)));
    while (root * root < sum) ++root;
    while (root * root > sum) --root;
    return root * root == sum;
}

int main() {
    int n, k;
    if (scanf("%d%d", &n, &k) != 2) return 0;
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
