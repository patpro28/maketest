#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD=1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m,k; string a,b; cin>>n>>m>>k>>a>>b;
    using Cell=array<int,2>;
    vector<vector<Cell>> prev(k+1,vector<Cell>(m+1,Cell{{0,0}})),cur=prev;
    prev[0][0][0]=1;
    for(int i=0;i<n;++i) {
        for(int t=0;t<=k;++t) for(int j=0;j<=m;++j) {
            cur[t][j][0]=(prev[t][j][0]+prev[t][j][1])%MOD;
            int take=0;
            if(j && a[i]==b[j-1]) {
                take=prev[t][j-1][1];
                if(t) { take+=prev[t-1][j-1][0]; if(take>=MOD) take-=MOD; }
            }
            cur[t][j][1]=take;
        }
        prev.swap(cur);
    }
    cout<<(prev[k][m][0]+prev[k][m][1])%MOD<<'\n';
}
