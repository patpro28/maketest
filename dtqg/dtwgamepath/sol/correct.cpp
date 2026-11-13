#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n, mod; string s; cin >> m >> n >> mod >> s;
    vector<int> dp(n); dp[0] = 1 % mod;
    for (int i = 0; i < m; ++i) {
        string row; cin >> row;
        for (int j = 0; j < n; ++j) {
            if (row[j] == '#') dp[j] = 0;
            else if (j) { dp[j] += dp[j - 1]; if (dp[j] >= mod) dp[j] -= mod; }
        }
    }
    cout << dp.back() << '\n';
}
