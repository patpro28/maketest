#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, T;
    cin >> N >> T;

    vector<int> m(N), t(N);
    for (int i = 0; i < N; i++) cin >> m[i];
    for (int i = 0; i < N; i++) cin >> t[i];

    vector<vector<long long>> dp(T + 1, vector<long long>(2, 0));

    for (int i = 0; i < N; i++) {
        for (int j = T; j >= t[i]; j--) {
            // đã dùng double
            dp[j][1] = max({
                dp[j][1],
                dp[j - t[i]][1] + m[i],
                dp[j - t[i]][0] + 2LL * m[i]
            });

            // chưa dùng double
            dp[j][0] = max(
                dp[j][0],
                dp[j - t[i]][0] + m[i]
            );
        }
    }

    cout << dp[T][1] << '\n';
    return 0;
}