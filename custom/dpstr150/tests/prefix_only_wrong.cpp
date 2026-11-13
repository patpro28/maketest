// Regression model of the submitted algorithm. The prefix underflow at i=0
// is guarded so failures demonstrate the algorithmic bug independently of UB.
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
ll dp[1006][1006], ans = -1;
ll ch1[1000006];
string a, b;
char ch;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll n, m;
    cin >> m >> n >> a >> b >> ch;
    for (int i = 0; i < int(a.size()); ++i)
        ch1[i] = (i ? ch1[i-1] : 0) + (a[i] == ch);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (ch1[i-1]) ans = max(ans, dp[i][j]);
            } else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    cout << ans << '\n';
}
