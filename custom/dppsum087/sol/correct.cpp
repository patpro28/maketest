#include <cstdio>
#include <vector>
using namespace std;

long long count_at_most(const vector<long long> &prefix, long long limit) {
    if (limit < 0) return 0;
    int n = static_cast<int>(prefix.size()) - 1;
    int left = 1;
    long long answer = 0;
    for (int right = 1; right <= n; ++right) {
        while (left <= right && prefix[right] - prefix[left - 1] > limit) ++left;
        answer += right - left + 1;
    }
    return answer;
}

int main() {
    int n;
    long long target;
    if (scanf("%d%lld", &n, &target) != 2) return 0;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x;
        if (scanf("%lld", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + x;
    }
    long long answer = 1LL * n * (n + 1) / 2 - count_at_most(prefix, target);
    printf("%lld\n", answer);
}
