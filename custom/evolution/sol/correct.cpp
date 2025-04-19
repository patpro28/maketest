// The Grass Type
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> g[100100];
int a[100100];
int ans=0;
void play(int u,int p,unordered_map<int,int> &mp)
{
    mp[a[u]]++;
    for(auto x:g[u])
    {
        if(x==p)
            continue;
        unordered_map<int,int> m;
        play(x,u,m);
        if(m.size()>mp.size())
            swap(m,mp);
        for(auto x:m)
            if(a[u]%x.first==0&&mp.find(a[u]/x.first)!=mp.end())
                ans+=x.second*mp[a[u]/x.first];
        for(auto x:m)
            mp[x.first]+=x.second;
    }
}
signed main()
{
    ios_base::sync_with_stdio(0),cin.tie(0);
    int n;
    cin >> n;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        cin >> a[i];
    unordered_map<int,int> mp;
    play(1,0,mp);
    cout << ans;
    return 0;
}