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
    const int MOD=1000000000;int m,A,B,K;cin>>m>>A>>B>>K;
    int plane=(A+1)*(B+1);vector<int>f((K+1)*plane),next(f.size());f[0]=1;
    for(int i=0;i<m;++i){
        int a,b;cin>>a>>b;next=f;
        for(int t=0;t<K;++t)for(int p=0;p<=A;++p)for(int q=0;q<=B;++q){
            int value=f[t*plane+p*(B+1)+q];if(!value)continue;
            for(int x=1;p+a*x<=A && q+b*x<=B;++x){
                int& target=next[(t+1)*plane+(p+a*x)*(B+1)+q+b*x];
                target+=value;if(target>=MOD)target-=MOD;
            }
        }
        f.swap(next);
    }
    cout<<f[K*plane+A*(B+1)+B]<<'\n';
}
