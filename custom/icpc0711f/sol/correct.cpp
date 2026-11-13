#include <bits/stdc++.h>
using namespace std;
long long n,ans;
void dfs(long long x,int mask) {
    if(x>n)return;
    if(mask==7)ans++;
    for(int i=0; i<3; i++)if(x*10+3+2*i<=n)dfs(x*10+3+2*i,mask|(1<<i));
}
int main() {
    cin>>n;
    dfs(0,0);
    cout<<ans<<'\n';
}
