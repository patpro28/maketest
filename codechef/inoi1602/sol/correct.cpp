#include <bits/stdc++.h>
using namespace std;
const int N = 702;

int dp[N][N], a[N], v[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int l = n - 1; l >= 0; l--) // Duyệt ngược lại để dp[l][r] phụ thuộc vào dp[l+1][r] và dp[l][k]
        for (int r = l + 1; r < n; r++)
        {
            if (a[l] + k == a[r])
                dp[l][r] = max(dp[l][r], dp[l + 1][r - 1] + v[l] + v[r]);
            for (int k = l; k < r; k++)
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r]);
        }
    cout << dp[0][n - 1] << endl;
    return 0;
}
