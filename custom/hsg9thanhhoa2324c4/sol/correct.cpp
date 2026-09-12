#include <bits/stdc++.h>
using namespace std;
long long n;
int a[3 * 1000006];
long long ans = 0, x;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> x;
    }
    sort(a + 1, a + n + 1);
    long long tam;
    tam = 1;
    for (int i = 2; i <= n; i++)
    {
        if (a[i] == a[i - 1])
            tam++;
        if (a[i] != a[i - 1])
        {
            ans += tam * (tam - 1) / 2;
            tam = 1;
        }
    }
    ans += tam * (tam - 1) / 2;
    cout << ans;
}