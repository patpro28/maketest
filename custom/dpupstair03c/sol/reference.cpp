#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

constexpr ll MOD=1000000007;
ll power(ll a,ll e) { ll r=1; for(;e;e/=2,a=a*a%MOD) if(e%2) r=r*a%MOD; return r; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k,m; cin>>n>>k>>m;
    vector<int>b(k); for(int &x:b) cin>>x; sort(b.begin(),b.end()); b.push_back(n+1);
    vector<ll> fac(n+1,1),inv(n+1,1);
    for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD;
    inv[n]=power(fac[n],MOD-2);
    for(int i=n;i>=1;--i) inv[i-1]=inv[i]*i%MOD;
    vector<ll> dp(m+1),next(m+1); dp[0]=1; int last=0;
    for(int pos:b) {
        int len=pos-last-1; last=pos;
        fill(next.begin(),next.end(),0);
        for(int j=0;j<=min(m,len/2);++j) {
            ll ways=fac[len-j]*inv[j]%MOD*inv[len-2*j]%MOD;
            for(int used=0;used+j<=m;++used)
                next[used+j]=(next[used+j]+dp[used]*ways)%MOD;
        }
        dp.swap(next);
    }
    cout<<dp[m]<<'\n';
}
