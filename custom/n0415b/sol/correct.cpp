#include <bits/stdc++.h>

using namespace std;

int n, k, d[1000005], a;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        d[a]++;
    }
    bool ok = 0;
    for (int i = 1; i <= 1000001; i++)
    {
        if (d[i] == k)
            cout << i << ' ', ok = 1;
    }
    if (!ok)
        cout << -1;
    return 0;
}