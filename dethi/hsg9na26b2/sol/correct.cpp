#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

int a[N + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    int res = k;
    for (int i = 1; i + k - 1 <= n; ++i)
    {
        res = min(res, a[i + k - 1] - a[i - 1]);
    }
    cout << a[n] + k - 2 * res << "\n";
    return 0;
}