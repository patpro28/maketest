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
    vector<vector<int>> f(k+1,vector<int>(m+1)); f[0][0]=1;
    for(int i=0;i<n;++i) for(int j=min(m,i+1);j>=1;--j) {
        int error=(a[i]!=b[j-1]);
        for(int t=error;t<=k;++t) {
            f[t][j]+=f[t-error][j-1]; if(f[t][j]>=MOD) f[t][j]-=MOD;
        }
    }
    int answer=0;
    for(int t=0;t<=k;++t) { answer+=f[t][m]; if(answer>=MOD) answer-=MOD; }
    cout<<answer<<'\n';
}
