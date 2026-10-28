#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; string a, b;
    int k; cin >> n >> m >> k >> a >> b;
    const string vowels = "aeiou";
    vector<vector<int> > dp(k + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        vector<vector<int> > next(k + 1, vector<int>(m + 1, 0));
        int cost = vowels.find(a[i]) != string::npos;
        for (int j = 1; j <= m; ++j) for (int t = 0; t <= k; ++t) {
            next[t][j] = max(dp[t][j], next[t][j-1]);
            if (a[i] == b[j-1] && t >= cost)
                next[t][j] = max(next[t][j], dp[t-cost][j-1] + 1);
        }
        dp.swap(next);
    }
    cout << dp[k][m] << '\n';
}
