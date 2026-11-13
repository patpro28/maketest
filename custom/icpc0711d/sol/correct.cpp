#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vector<int>a(n+1),b(n+1);
    for(int i=0; i<n; i++) {
        cin>>a[i];
        a[n]^=a[i];
    }
    for(int i=0; i<n; i++) {
        cin>>b[i];
        b[n]^=b[i];
    }
    vector<int>va=a,vb=b;
    sort(va.begin(),va.end());
    sort(vb.begin(),vb.end());
    if(va!=vb) {
        cout<<-1<<'\n';
        return 0;
    }
    va.erase(unique(va.begin(),va.end()),va.end());
    int sz=va.size();
    vector<int>p(sz),used(sz);
    iota(p.begin(),p.end(),0);
    auto find=[&](int u) {
        while(p[u]!=u) {
            p[u]=p[p[u]];
            u=p[u];
        }
        return u;
    };
    auto id=[&](int x) {
        return int(lower_bound(va.begin(),va.end(),x)-va.begin());
    };
    int mismatches=0;
    for(int i=0; i<=n; i++)if(a[i]!=b[i]) {
        int u=id(a[i]),v=id(b[i]);
        used[u]=used[v]=1;
        p[find(u)]=find(v);
        mismatches+=(i<n);
    }
    int components=0;
    for(int u=0; u<sz; u++)components+=used[u]&&find(u)==u;
    cout<<mismatches+components-used[id(a[n])]<<'\n';
}
