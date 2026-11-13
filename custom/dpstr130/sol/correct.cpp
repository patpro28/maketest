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
    vector<long long> w(26); for (int c = 0; c < 26; ++c) cin >> w[c];
    vector<long long> dp(m + 1, 0);
    for (int i = 0; i < n; ++i) {
        long long diagonal = 0;
        for (int j = 1; j <= m; ++j) {
            long long old = dp[j];
            dp[j] = max(dp[j], dp[j-1]);
            if (a[i] == b[j-1]) dp[j] = max(dp[j], diagonal + w[a[i]-'a']);
            diagonal = old;
        }
    }
    cout << dp[m] << '\n';
}
