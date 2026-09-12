#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

void Solve()
{
    int n;
    cin >> n;

    vector<int> d;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            d.push_back(i);
            if (i * i != n)
            {
                d.push_back(n / i);
            }
        }
    }

    sort(d.begin(), d.end());

    map<int, int> dp;
    dp[1] = 1;

    for (auto x : d)
    {
        if (x == 1)
            continue;
        for (auto y : d)
            if (y % x == 0)
            {
                dp[y] += dp[y / x];
            }
    }

    cout << dp[n] << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);

    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        // cout << "Case #" << i << ": ";
        Solve();
    }

    return 0;
}