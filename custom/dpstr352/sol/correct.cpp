#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD=1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m,L,R; string a,b; cin>>n>>m>>L>>R>>a>>b;
    vector<int> prev(n+1),cur(n+1);
    for(int i=1;i<=n;++i) prev[i]=(a[i-1]==b[0]);
    for(int j=1;j<m;++j) {
        int window=0;
        for(int i=1;i<=n;++i) {
            if(i-L>=1) { window+=prev[i-L]; if(window>=MOD) window-=MOD; }
            if(i-R-1>=1) { window-=prev[i-R-1]; if(window<0) window+=MOD; }
            cur[i]=(a[i-1]==b[j]?window:0);
        }
        prev.swap(cur);
    }
    int answer=0;
    for(int i=1;i<=n;++i) { answer+=prev[i]; if(answer>=MOD) answer-=MOD; }
    cout<<answer<<'\n';
}
