#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    const int MOD=1000000000;int m,A;cin>>m>>A;vector<int> dp(A+1);dp[0]=1;
    for(int i=0;i<m;++i){int a;cin>>a;for(int p=a;p<=A;++p){dp[p]+=dp[p-a];if(dp[p]>=MOD)dp[p]-=MOD;}}
    cout<<dp[A]<<'\n';
}
