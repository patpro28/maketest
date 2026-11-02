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
    long long lower, upper;
    if (scanf("%d%lld%lld", &n, &lower, &upper) != 3) return 0;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x;
        if (scanf("%lld", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + x;
    }
    long long answer = count_at_most(prefix, upper) - count_at_most(prefix, lower - 1);
    printf("%lld\n", answer);
}
