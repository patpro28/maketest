#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD=1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b; cin>>n>>m>>a>>b;
    vector<int> f(m+1); f[0]=1;
    for(int i=0;i<n;++i) for(int j=min(m,i+1);j>=1;--j)
        if(a[i]==b[j-1]) { f[j]+=f[j-1]; if(f[j]>=MOD) f[j]-=MOD; }
    cout<<f[m]<<'\n';
}
