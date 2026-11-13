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
    vector<int> older(m+1),prev(m+1),cur(m+1); older[0]=prev[0]=1;
    for(int i=1;i<=n;++i) {
        cur[0]=1;
        for(int j=1;j<=m;++j) {
            cur[j]=prev[j];
            if(a[i-1]==b[j-1]) { cur[j]+=older[j-1]; if(cur[j]>=MOD) cur[j]-=MOD; }
        }
        older.swap(prev); prev.swap(cur);
    }
    cout<<prev[m]<<'\n';
}
