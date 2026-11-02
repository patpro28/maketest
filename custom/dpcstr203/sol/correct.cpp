#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    cin>>n>>m>>a>>b;
    reverse(b.begin(),b.end());
    vector<int> dp(m+1,0);
    int answer=0;
    for(int i=0;i<n;++i) {
        for(int j=m;j>=1;--j) {
            dp[j]=a[i]==b[j-1] ? dp[j-1]+1 : 0;
            answer=max(answer,dp[j]);
        }
    }
    cout<<answer<<'\n';
}
