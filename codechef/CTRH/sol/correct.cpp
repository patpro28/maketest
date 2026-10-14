#include<bits/stdc++.h>
using namespace std;
#define ll long long

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

vector <ll> v[200005];
ll dp[200005][3];
ll mod=1000000007;
ll inv2,inv3;

void dfs(ll pos,ll par){
    ll diff1=1;
    ll ways=1;
    ll same=1;
    ll cnt;
    for(auto it:v[pos]){
        if(it!=par){
            dfs(it,pos);
            cnt=(((((dp[it][1]*inv2)%mod)+dp[it][0]+dp[it][2]*2)%mod)*inv3)%mod;
            diff1*=cnt;diff1%=mod;
            cnt=(((dp[it][0]*2+dp[it][1]+dp[it][2]*3)%mod)*inv3)%mod;
            ways*=cnt;ways%=mod;
            same*=(dp[it][2]*inv3)%mod;same%=mod;
        }
    }
    dp[pos][1]=(6*(diff1-same+mod))%mod;
    dp[pos][2]=(3*(ways-same+mod)-dp[pos][1]+mod)%mod;
    if(v[pos].size()==1){
        dp[pos][0]=3;
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll tt=1;
    cin>>tt;
    inv2=binpow(2,mod-2,mod);
    inv3=binpow(3,mod-2,mod);
    while(tt--){
        ll n;
        cin>>n;
        for(int i=1;i<=n;i++){
            v[i].clear();
            dp[i][0]=dp[i][1]=dp[i][2]=0;
        }
        ll x,y;
        for(int i=1;i<n;i++){
            cin>>x>>y;
            v[x].push_back(y);
            v[y].push_back(x);
        }
        ll root=0;
        for(int i=1;i<=n;i++){
            if(v[i].size()>1){
                root=i;
                dfs(root,-1);
                break;
            }
        }
        cout<<dp[root][2]<<"\n";
    }
    return 0;
}