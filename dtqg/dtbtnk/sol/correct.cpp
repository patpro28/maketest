#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

const int MOD = 111539786;
int bounded(const string &s, int limit)
{
    if (limit < 0)
        return 0;
    vector<int> dp(limit + 1), last_open(limit + 1), last_close(limit + 1), next(limit + 1);
    dp[0] = 1;
    for (char c : s)
    {
        next = dp;
        if (c == '(') {
            for (int b = 1; b <= limit; ++b)
                next[b] = (next[b] + dp[b - 1] - last_open[b - 1] + MOD) % MOD;
            last_open = dp;
        }
        else {
            for (int b = 0; b < limit; ++b)
                next[b] = (next[b] + dp[b + 1] - last_close[b + 1] + MOD) % MOD;
            last_close = dp;
        }
        dp.swap(next);
    }
    return dp[0];
}
int main()
{
    if (FILE *input = fopen("BTNK.INP", "r"))
    {
        fclose(input);
        freopen("BTNK.INP", "r", stdin);
        freopen("BTNK.OUT", "w", stdout);
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int k;
    cin >> s >> k;
    int answer = bounded(s, k) - bounded(s, k - 1);
    if (answer < 0)
        answer += MOD;
    cout << answer << '\n';
}
