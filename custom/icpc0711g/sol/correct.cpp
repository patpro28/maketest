#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long MOD=1000000007;
    int n,k;
    cin>>n>>k;
    vector<string>s(n);
    for(auto &z:s)cin>>z;
    sort(s.begin(),s.end());
    string x;
    cin>>x;
    vector<int>bit(n+1);
    for(int i=1; i<=n; i++)bit[i]=i&-i;
    vector<long long>w(k,1);
    for(int i=k-2; i>=0; i--)w[i]=w[i+1]*(n-i-1)%MOD;
    size_t pos=0;
    long long ans=1;
    for(int i=0; i<k; i++) {
        auto it=lower_bound(s.begin(),s.end(),pos,[&](const string &z,size_t p) {return z.compare(0,z.size(),x,p,min(z.size(),x.size()-p))<0;});
        int id=it-s.begin(),less=0;
        for(int t=id; t; t-=t&-t)less+=bit[t];
        ans=(ans+less*w[i])%MOD;
        for(int t=id+1; t<=n; t+=t&-t)--bit[t];
        pos+=it->size();
    }
    cout<<ans<<'\n';
}
