#include <bits/stdc++.h>
using namespace std;
long long a[1000005], n, q, x;
long long binary_search1(long long l, long long r, long long k)
{
    long long dau = l, cuoi = r;
    while (dau <= cuoi)
    {
        long long mid = (dau + cuoi) / 2;
        if (a[mid] >= k)
            cuoi = mid - 1;
        else
            dau = mid + 1;
    }
    return dau;
}
long long binary_search2(long long l, long long r, long long k)
{
    long long dau = l, cuoi = r;
    while (dau <= cuoi)
    {
        long long mid = (dau + cuoi) / 2;
        if (a[mid] <= k)
            dau = mid + 1;
        else
            cuoi = mid - 1;
    }
    return cuoi;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    cin >> q;
    while (q--)
    {
        cin >> x;
        long long s = binary_search1(1, n, x), s1 = binary_search2(1, n, x);
        if (s1 >= s)
            cout << s1 - s + 1 << "\n";
        else
            cout << 0 << "\n";
    }
}