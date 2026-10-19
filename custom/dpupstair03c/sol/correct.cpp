#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

constexpr int MOD=1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k,m; cin>>n>>k>>m; vector<bool> blocked(n+1,false);
    for(int i=0,x;i<k;++i) { cin>>x; blocked[x]=true; }
    vector<int> prev(m+1),prev2(m+1),cur(m+1); prev[0]=1;
    for(int i=1;i<=n;++i) {
        for(int j=0;j<=m;++j) {
            cur[j]=prev[j];
            if(!blocked[i] && i>=2 && !blocked[i-1] && j>0) {
                cur[j]+=prev2[j-1]; if(cur[j]>=MOD) cur[j]-=MOD;
            }
        }
        prev2=prev; prev=cur;
    }
    cout<<prev[m]<<'\n';
}
