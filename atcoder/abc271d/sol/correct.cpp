#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s;
    cin >> n >> s;
    vector<int> a(n), b(n);
    vector<vector<char>> dp(n + 1, vector<char>(s + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        for (int t = 0; t <= s; ++t) if (dp[i][t]) {
            if (t + a[i] <= s) dp[i+1][t+a[i]] = 'A';
            if (t + b[i] <= s) dp[i+1][t+b[i]] = 'B';
        }
    }
    if (!dp[n][s]) { cout << "No\n"; return 0; }
    string answer(n, 'A');
    for (int i = n - 1; i >= 0; --i) {
        answer[i] = dp[i+1][s];
        s -= answer[i] == 'A' ? a[i] : b[i];
    }
    cout << "Yes\n" << answer << '\n';
}
