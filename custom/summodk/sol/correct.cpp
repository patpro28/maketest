#include <bits/stdc++.h>
using namespace std;
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - //
#define task ""
#define mu                        \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
void Hung()
{
    mu;
    if (fopen(task ".inp", "r"))
    {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
}
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - //
#define f(i, a, b) for (int i = a; i <= b; i++)
#define fr(i, a, b) for (int i = a; i >= b; i--)
#define whle(t) while (t--)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define lcm(a, b) a / __gcd(a, b) * b;
#define sz(s) (long long)(s.size())
/*/-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - //
#ifndef ONLINE_JUDGE
#if __has_include("algo/debug.h")
#include "algo/debug.h"
#endif
#else
#define debug(...) 42
#endif
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - /*/
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef float fl;
typedef long long int lli;
typedef string st;
const ll oo = 1e18;
const ll mod = 1e9 + 7;
const int N = 1e6 + 6;
const int Ns = 1e5 + 5;
const int nmax = 1e7 + 5;
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - //
void cerrtime(){
    cerr << "\nTime: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.\n";
}
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - //
signed main()
{
    Hung();
    int t;
    cin >> t;
    whle(t){
        long long n, m , k;
        cin >> n >> k >> m;
        long long sd = k, tmp = n;
        if(n % m == k) tmp = n;
        else if(n % m < k) tmp = n - (n % m) - (m - k);
        else{
            tmp = n -(n % m - k);
        }
        //n = n / m * m + k; 
        if(tmp < sd) cout << 0<<"\n";
        else
        cout << (tmp + sd) * ((tmp - sd) / m + 1) / 2<< "\n";
      // cerr << sd << " " << tmp <<"\n";
    }
    cerrtime();
}