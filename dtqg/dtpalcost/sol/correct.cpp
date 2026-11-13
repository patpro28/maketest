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
#include "palindrome.h"
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s;int k;cin>>s>>k;int n=s.size(),states=1<<k;
    vector<int> length(k);long long total=0;
    for(int& x:length){cin>>x;total+=x;}
    vector<long long> prefix(n+1);
    for(int i=1;i<=n;++i){long long w;cin>>w;prefix[i]=prefix[i-1]+w;}
    if(total>n){cout<<-1<<'\n';return 0;}
    Palindrome pal(s);const long long INF=4000000000000000000LL;
    vector<long long> dp(size_t(n+1)*states,INF);dp[0]=0;
    for(int p=0;p<=n;++p)for(int mask=0;mask<states;++mask){
        long long value=dp[size_t(p)*states+mask];if(value==INF)continue;
        if(p<n){auto& target=dp[size_t(p+1)*states+mask];target=min(target,value);}
        for(int i=0;i<k;++i)if(!(mask>>i&1) && pal.has(p,length[i])){
            int end=p+length[i];auto& target=dp[size_t(end)*states+(mask|(1<<i))];
            target=min(target,value+prefix[end]-prefix[p]);
        }
    }
    long long answer=dp[size_t(n)*states+states-1];cout<<(answer==INF?-1:answer)<<'\n';
}
