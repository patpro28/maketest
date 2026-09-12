#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L;
    cin >> n >> L;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<long long> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];

        long long take = a[i];
        int pre = i - L - 1;

        if (pre > 0) take += dp[pre];

        dp[i] = max(dp[i], take);
    }

    cout << dp[n];
    return 0;
}