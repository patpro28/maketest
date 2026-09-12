#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// Nhân chống tràn
ll mul_mod(ll a, ll b, ll m)
{
    a %= m;
    b %= m;
    ll c = (long double)a * b / m;
    ll r = (a * b - c * m) % m;
    return (r + m) % m;
}
ll mod_pow(ll a, ll n, ll m)
{
    if (n == 0)
        return 1;
    ll t = mod_pow(a, n / 2, m);
    t = mul_mod(t, t, m);
    if (n % 2)
        t = mul_mod(t, a, m);
    return t;
}

// S(n) = 1 + x + ... + x^(n-1)
ll sum(ll x, ll n, ll m)
{
    if (n == 0)
        return 0;
    if (n % 2 == 0)
    {
        // S(n) = S(n/2) * (1 + x^(n/2))
        return mul_mod(sum(x, n / 2, m), (1 + mod_pow(x, n / 2, m)) % m, m);
    }
    else
    {
        // S(n) = S(n-1) + x^(n-1)
        return (sum(x, n - 1, m) + mod_pow(x, n - 1, m)) % m;
    }
}

int main()
{
    ll x, n, m;
    cin >> x >> n >> m;
    ll res = sum(x, n + 1, m);
    cout << res << "\n";
    return 0;
}