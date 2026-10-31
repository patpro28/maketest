#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; string a, b;
    cin >> n >> m >> a >> b;
    vector<long long> u(n), v(m); for (auto &x : u) cin >> x; for (auto &x : v) cin >> x;
    vector<long long> dp(m + 1, 0);
    for (int j = 1; j <= m; ++j) dp[j] = dp[j-1] + v[j-1];
    for (int i = 0; i < n; ++i) {
        long long diagonal = dp[0]; dp[0] += u[i];
        for (int j = 1; j <= m; ++j) {
            long long old = dp[j];
            dp[j] = min(dp[j] + u[i], dp[j-1] + v[j-1]);
            if (a[i] == b[j-1]) dp[j] = min(dp[j], diagonal);
            diagonal = old;
        }
    }
    cout << dp[m] << '\n';
}
