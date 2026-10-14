///HO SY PHAT - 11A3 - CDHV

#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define getbit(x,i) ((x >> i) & 1)
#define cntbit(x) (__builtin_popcount(x))

const ll mod = 1e9 + 7;
const ll base = 31;
const ll nmax = 1000005;
int n;
ll a[nmax];
map<ll, ll> m;
ll ans = 0;
void solve()
{
    cin>>n;
    for(int i = 1; i <= n; i++)
        cin>>a[i];
    ll ans = 0;
    for(int i = 2; i < n; i++)
    {
        for(int j = i + 1; j <= n; j++)
            ans += m[a[i] + a[j]];
        for(int j = 1; j < i; j++)
            m[a[i] + a[j]]++;
    }
    cout<<ans;
}
int main()
{
    //freopen(".inp","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    //cin>>T;
    while(T--)
    {
         solve();
         //cout<<'\n';
    }
}
///REMEMBER TO BE CUTE
