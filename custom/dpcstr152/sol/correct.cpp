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
    const int NEG = -1000000;
    typedef array<int, 3> State;
    const State empty = {{NEG, NEG, NEG}};
    vector<State> dp(m + 1, empty);
    for (int i = 0; i < n; ++i) {
        vector<State> next(m + 1, empty);
        for (int j = 1; j <= m; ++j) {
            for (int c = 0; c < 3; ++c) next[j][c] = max(dp[j][c], next[j-1][c]);
            if (a[i] == b[j-1]) {
                int c = a[i]-'a', previous = 0;
                for (int d = 0; d < 3; ++d) if (c != d) previous = max(previous, dp[j-1][d]);
                next[j][c] = max(next[j][c], previous + 1);
            }
        }
        dp.swap(next);
    }
    cout << max(0, *max_element(dp[m].begin(), dp[m].end())) << '\n';
}
