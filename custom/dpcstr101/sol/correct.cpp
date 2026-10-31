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
    vector<vector<int> > dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
        dp[i][j] = a[i-1] == b[j-1] ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);
    string answer;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) { answer += a[i-1]; --i; --j; }
        else if (dp[i-1][j] >= dp[i][j-1]) --i;
        else --j;
    }
    reverse(answer.begin(), answer.end());
    cout << answer.size() << '\n';
    if (!answer.empty()) cout << answer << '\n';
}
