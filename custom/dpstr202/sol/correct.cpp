#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    cin>>n>>m>>a>>b;
    char target; cin>>target;
    vector<int> dp(m+1,0);
    int answer=-1,last=-1;
    for(int i=0;i<n;++i) {
        if(a[i]==target) last=i;
        for(int j=m;j>=1;--j) {
            dp[j]=a[i]==b[j-1] ? dp[j-1]+1 : 0;
            if(dp[j]>0 && last>=i-dp[j]+1) answer=max(answer,dp[j]);
        }
    }
    cout<<answer<<'\n';
}
