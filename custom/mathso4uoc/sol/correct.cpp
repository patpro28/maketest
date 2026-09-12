#include <bits/stdc++.h>
#define ll long long
#define nmax 2000006
using namespace std;
ll d[nmax + 1];
ll t;
ll b[nmax + 1];
void sanguoc()
{
    for (int i = 1; i <= nmax; i++)
        for (int j = i; j <= nmax; j += i)
            b[j]++;
}
bool slp(ll n)
{
    ll k = cbrtl(n);
    return k * k * k == n;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sanguoc();
    for (int i = 1; i <= nmax; i++)
    {
        if (b[i] == 4 && !slp(i))
            d[i] = d[i - 1] + 1;
        else
            d[i] = d[i - 1];
    }
    cin >> t;
    while (t--)
    {
        ll l, r;
        cin >> l >> r;
        cout << d[r] - d[l - 1] << '\n';
    }
    return 0;
}