#include <bitset>
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
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    vector<bitset<10001>> dp(n+1);
    dp[n][0] = true;
    for (int i = n-1; i >= 0; --i)
        dp[i] = (dp[i+1] << a[i]) | (dp[i+1] << b[i]);
    if (!dp[0][s]) { cout << "No\n"; return 0; }
    string answer;
    for (int i = 0; i < n; ++i) {
        if (s >= a[i] && dp[i+1][s-a[i]]) {
            answer += 'A'; s -= a[i];
        } else { answer += 'B'; s -= b[i]; }
    }
    cout << "Yes\n" << answer << '\n';
}
