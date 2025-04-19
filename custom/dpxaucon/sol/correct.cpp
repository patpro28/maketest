#include <bits/stdc++.h>
using namespace std;
long long n, k, d[1000006], dem = 0;
long long chat(int i)
{
    long long dau = 0, cuoi = i, giua, kq = -1;
    while (dau <= cuoi)
    {
        giua = (dau + cuoi) / 2;
        if (d[i] - d[giua] >= k)
        {
            kq = giua;
            dau = giua + 1;
        }
        else
            cuoi = giua - 1;
    }
    return kq;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen(".inp", "r", stdin);
    // freopen(".out", "w", stdout);
    string s;
    cin >> n >> k >> s;
    s = ' ' + s;
    for (int i = 1; i <= n; i++)
    {
        d[i] = d[i - 1] + s[i];
        long long sc = chat(i);
        if (sc != -1)
        {
            dem += sc + 1;
        }
    }
    cout << dem;
    return 0;
}