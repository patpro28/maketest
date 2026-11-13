#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; string s; cin>>n>>s;
    const int MOD=1000000007;
    vector<int> nextSame(n),prevSame(n);
    array<int,26> last;last.fill(n);
    for(int i=n-1;i>=0;--i) { nextSame[i]=last[s[i]-'a'];last[s[i]-'a']=i; }
    last.fill(-1);
    for(int i=0;i<n;++i) { prevSame[i]=last[s[i]-'a'];last[s[i]-'a']=i; }
    vector<int> f(n*n);
    auto get=[&](int l,int r) { return l>r?0:f[l*n+r]; };
    for(int l=n-1;l>=0;--l) {
        f[l*n+l]=1;
        for(int r=l+1;r<n;++r) {
            long long inside=get(l+1,r-1),value;
            if(s[l]!=s[r]) value=1LL*get(l+1,r)+get(l,r-1)-inside;
            else {
                int low=nextSame[l],high=prevSame[r];
                value=2*inside;
                if(low>high) value+=2;
                else if(low==high) ++value;
                else value-=get(low+1,high-1);
            }
            f[l*n+r]=int((value+MOD)%MOD);
        }
    }
    cout<<get(0,n-1)<<'\n';
}
