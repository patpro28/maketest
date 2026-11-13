#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    string s;
    cin>>n>>q>>s;
    auto good=[&](int i) {
        return i>=0&&i+2<n&&s.compare(i,3,"ABC")==0;
    };
    int ans=0;
    for(int i=0; i<n; i++) ans+=good(i);
    while(q--) {
        int x;
        char c;
        cin>>x>>c;
        --x;
        for(int i=x-2; i<=x; i++) ans-=good(i);
        s[x]=c;
        for(int i=x-2; i<=x; i++) ans+=good(i);
        cout<<ans<<'\n';
    }
}
