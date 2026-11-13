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
    string s;int k;cin>>s>>k;int n=s.size();vector<int>length(k);
    for(int& x:length)cin>>x;vector<long long>w(n+1);
    for(int i=1;i<=n;++i){cin>>w[i];w[i]+=w[i-1];}
    vector<unsigned char>pal(size_t(n)*n);
    for(int l=n-1;l>=0;--l)for(int r=l;r<n;++r)
        pal[size_t(l)*n+r]=s[l]==s[r] && (r-l<2 || pal[size_t(l+1)*n+r-1]);
    const long long INF=4000000000000000000LL;int states=1<<k;
    vector<long long>f(size_t(states)*(n+1),INF);f[0]=0;
    for(int mask=0;mask<states;++mask){
        long long best=INF;
        for(int p=0;p<=n;++p){
            best=min(best,f[size_t(mask)*(n+1)+p]);if(best==INF)continue;
            for(int i=0;i<k;++i)if(!(mask>>i&1)){
                int end=p+length[i];
                if(end<=n && pal[size_t(p)*n+end-1]){
                    auto& target=f[size_t(mask|(1<<i))*(n+1)+end];target=min(target,best+w[end]-w[p]);
                }
            }
        }
    }
    long long result=*min_element(f.end()-(n+1),f.end());cout<<(result==INF?-1:result)<<'\n';
}
