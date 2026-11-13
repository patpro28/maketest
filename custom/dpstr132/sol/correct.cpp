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
    char c; cin >> c;
    vector<int> dp(m + 1, 0); int answer = -1;
    for (int i = 0; i < n; ++i) {
        int diagonal = 0;
        for (int j = 1; j <= m; ++j) {
            int old = dp[j];
            if (a[i] == b[j-1] && a[i] == c) answer = max(answer, diagonal + 1);
            dp[j] = a[i] == b[j-1] ? diagonal + 1 : max(dp[j], dp[j-1]);
            diagonal = old;
        }
    }
    cout << answer << '\n';
}
