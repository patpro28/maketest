#include <bits/stdc++.h>
#define int long long
using namespace std;

int t[1000006], r[1000006], dp[1000006];
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> t[i];
  for (int i = 1; i < n; i++)
    cin >> r[i];
  dp[1] = t[1];
  dp[2] = min(t[1] + t[2], r[1]);
  for (int i = 3; i <= n; i++)
    dp[i] = min(dp[i - 1] + t[i], dp[i - 2] + r[i - 1]);
  cout << dp[n];
  return 0;
}