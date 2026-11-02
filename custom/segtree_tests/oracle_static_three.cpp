// Independent references: sorted sqrt blocks, capped 128-bit LCM blocks, sparse RMQ.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
using i64=long long;
constexpr i64 LIMIT=1000000000000000000LL,OVER=LIMIT+1;
i64 lcm(i64 a,i64 b) {
    if(a==OVER||b==OVER)return OVER;
    __int128 x=static_cast<__int128>(a/std::gcd(a,b))*b;
    return x>LIMIT ? OVER : static_cast<i64>(x);
}
int main(int argc,char **argv) {
    if(argc!=2)return 2;
    int kind=std::atoi(argv[1]);std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
    int n,q;std::cin>>n>>q;std::vector<i64>a(n);for(i64 &x:a)std::cin>>x;
    if(kind==9) {
        int m=n-1;std::vector<int>lg(n+1);for(int i=2;i<=n;++i)lg[i]=lg[i/2]+1;
        std::vector<std::vector<i64>>table(m ? lg[m]+1 : 0);
        if(m){table[0].resize(m);for(int i=0;i<m;++i)table[0][i]=a[i]+a[i+1];}
        for(int k=1;m && k<=lg[m];++k){table[k].resize(m-(1<<k)+1);for(int i=0;i+(1<<k)<=m;++i)table[k][i]=std::min(table[k-1][i],table[k-1][i+(1<<(k-1))]);}
        while(q--){int l,r;std::cin>>l>>r;if(l==r){std::cout<<-1<<'\n';continue;}int k=lg[r-l];std::cout<<std::min(table[k][l-1],table[k][r-1-(1<<k)])<<'\n';}
        return 0;
    }
    const int B=450;int blocks=(n+B-1)/B;
    std::vector<std::vector<i64>>sorted(blocks);std::vector<i64>cycles(blocks,1);
    for(int i=0;i<n;++i){sorted[i/B].push_back(a[i]);if(kind==7)cycles[i/B]=lcm(cycles[i/B],a[i]);}
    for(auto &block:sorted)std::sort(block.begin(),block.end());
    while(q--) {
        int l,r;std::cin>>l>>r;--l;
        if(kind==7) {
            i64 result=1;
            for(int i=l;i<r && result!=OVER;){if(i%B==0&&i+B<=r){result=lcm(result,cycles[i/B]);i+=B;}else result=lcm(result,a[i++]);}
            std::cout<<(result==OVER ? -1 : result)<<'\n';continue;
        }
        i64 minimum=std::numeric_limits<i64>::max(),second=minimum;
        for(int i=l;i<r;){if(i%B==0&&i+B<=r){minimum=std::min(minimum,sorted[i/B].front());i+=B;}else minimum=std::min(minimum,a[i++]);}
        for(int i=l;i<r;){
            if(i%B==0&&i+B<=r){const auto &block=sorted[i/B];auto it=std::upper_bound(block.begin(),block.end(),minimum);if(it!=block.end())second=std::min(second,*it);i+=B;}
            else{if(a[i]>minimum)second=std::min(second,a[i]);++i;}
        }
        std::cout<<(second==std::numeric_limits<i64>::max() ? -1 : second)<<'\n';
    }
}
