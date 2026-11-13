#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vector<int>a(n);
    for(int &x:a)cin>>x;
    vector<int>v=a;
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    long long need=(1LL*n*(n+1)/2+1)/2;
    auto ok=[&](int x) {
        vector<int>bit(2*n+4);
        long long cnt=0;
        int s=n+1;
        auto add=[&](int p) {
            for(; p<(int)bit.size(); p+=p&-p)bit[p]++;
        };
        add(s);
        for(int y:a) {
            s+=(y>=x?1:-1);
            for(int p=s; p; p-=p&-p)cnt+=bit[p];
            add(s);
        }
        return cnt>=need;
    };
    int l=0,r=(int)v.size();
    while(l+1<r) {
        int m=(l+r)/2;
        if(ok(v[m]))l=m;
        else r=m;
    }
    cout<<v[l]<<'\n';
}
