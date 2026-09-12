#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[200005],cnt[200005],n,kq=0,m=-1e18;
int main()
{
    // freopen("D.INP","r",stdin);
    // freopen("D.OUT","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin>>n;
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
        cnt[a[i]]++;
        m=max(m,a[i]);
    }
    for(ll i=1;i<=m;i++)
    {
        if(cnt[i]==0)continue;
        for(ll j=1;i*j<=m;j++)
        {
            if(cnt[j]==0)continue;
            ll x=i*j;
            if(x<=m && cnt[x]>0)
                kq+=cnt[i]*cnt[j]*cnt[x];
        }
    }
    cout<<kq<<"\n";
}