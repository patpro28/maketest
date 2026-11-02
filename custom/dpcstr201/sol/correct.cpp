#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    cin>>n>>m>>a>>b;
    vector<int> dp(m+1,0);
    int answer=0,best_a=0,best_b=0;
    for(int i=0;i<n;++i) {
        for(int j=m;j>=1;--j) {
            dp[j]=a[i]==b[j-1] ? dp[j-1]+1 : 0;
            int length=dp[j];
            int start_a=i-length+2,start_b=j-length+1;
            if(length>answer || (length>0 && length==answer &&
               (start_a<best_a || (start_a==best_a && start_b<best_b)))) {
                answer=length; best_a=start_a; best_b=start_b;
            }
        }
    }
    cout<<answer<<' '<<best_a<<' '<<best_b<<'\n';
}
