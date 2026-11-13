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
    string s;int k,e;cin>>s>>k>>e;int n=s.size();
    vector<int> length(k),need(k);long long total=0;
    for(int& x:length){cin>>x;total+=x;}
    for(int j=0;j<e;++j){int u,v;cin>>u>>v;need[v-1]|=1<<(u-1);}
    if(total>n){cout<<"NO\n";return 0;}
    Palindrome pal(s);map<int,vector<int>> next;
    for(int x:length)if(!next.count(x))next[x]=pal.next(x);
    vector<const vector<int>*> table(k);
    for(int i=0;i<k;++i)table[i]=&next[length[i]];
    vector<int> dp(1<<k,n+1);dp[0]=0;
    for(int mask=0;mask<(1<<k);++mask)if(dp[mask]<=n){
        for(int i=0;i<k;++i)if(!(mask>>i&1) && (need[i]&mask)==need[i]){
            int& target=dp[mask|(1<<i)];target=min(target,(*table[i])[dp[mask]]);
        }
    }
    cout<<(dp.back()<=n?"YES\n":"NO\n");
}
