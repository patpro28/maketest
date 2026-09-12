/*
Author: Tu Pham Anh
Date: 2025/12/08 - 14:37
*/
#include <bits/stdc++.h>

using namespace std;

template <typename T>
using V = vector<T>;
using ll = long long;
const ll mod = 1e9 + 7;

int n, m, k;
string a, b;
V<V<V<int>>> dp[2];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n >> m >> k;
    cin >> a >> b;
    dp[0].resize(n + 1, V<V<int>>(m + 1, V<int>(k + 1, -1)));
    dp[1].resize(n + 1, V<V<int>>(m + 1, V<int>(k + 1, -1)));
    for (int i = n; i >= 0; --i)
        for (int j = m; j >= 0; --j)
            for (int t = k; t >= 0; --t)
            {
                if (m - j < k - t)
                    continue;

                for (int in = 0; in <= 1; ++in)
                {
                    auto &res = dp[in][i][j][t];
                    if (j == m)
                    {
                        res = (t == k);
                        continue;
                    }
                    if (i == n || t > k)
                    {
                        res = 0;
                        continue;
                    }

                    res = 0;
                    if (in)
                    {
                        res += dp[0][i][j][t]; // close
                        if (a[i] == b[j])
                            res += dp[1][i + 1][j + 1][t]; // continue
                    }
                    else
                    {
                        if (a[i] == b[j])
                            res += dp[1][i + 1][j + 1][t + 1]; // open
                        res += dp[0][i + 1][j][t];             // skip
                    }

                    res %= mod;
                }
            }
    cout << dp[0][0][0][0] << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}