// Independent references: difference Fenwick, interval assignment map and sqrt blocks.
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <vector>
using i64=long long;
struct Fenwick {
    int n;std::vector<i64> f;
    explicit Fenwick(int m):n(m),f(m+1){}
    void add(int p,i64 x){for(;p<=n;p+=p&-p)f[p]+=x;}
    i64 sum(int p)const{i64 s=0;for(;p;p-=p&-p)s+=f[p];return s;}
};
int main(int argc,char **argv) {
    if(argc!=2)return 2;
    int kind=std::atoi(argv[1]);std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
    int n,q;std::cin>>n>>q;std::vector<i64>a(n);for(i64 &x:a)std::cin>>x;
    if(kind==200) {
        Fenwick f(n);
        while(q--){int t,l;std::cin>>t>>l;if(t==1){int r;i64 x;std::cin>>r>>x;f.add(l,x);f.add(r+1,-x);}else std::cout<<a[l-1]+f.sum(l)<<'\n';}
        return 0;
    }
    if(kind==201) {
        std::map<int,i64> intervals;for(int i=0;i<n;++i)intervals[i+1]=a[i];intervals[n+1]=0;
        auto split=[&](int p){auto it=std::prev(intervals.upper_bound(p));return it->first==p ? it : intervals.emplace(p,it->second).first;};
        while(q--){
            int t,l;std::cin>>t>>l;
            if(t==1){int r;i64 c;std::cin>>r>>c;auto end=split(r+1);auto begin=split(l);intervals.erase(begin,end);intervals[l]=c;}
            else std::cout<<std::prev(intervals.upper_bound(l))->second<<'\n';
        }
        return 0;
    }
    const int B=450,count=(n+B-1)/B;
    i64 identity=kind==202 ? 0 : kind==203 ? 1000000001 : 0;
    std::vector<i64>tag(count,identity);
    const std::array<int,3> same={1,2,3};std::vector<std::array<int,3>>color(count,same);
    auto combine=[&](i64 v,i64 x){if(kind==202)return std::max(v,x);if(kind==203)return std::min(v,x);return std::gcd(v,x);};
    auto swap_color=[](i64 c,int x,int y)->i64{return c==x ? y : c==y ? x : c;};
    auto flush=[&](int id){
        for(int i=id*B;i<std::min(n,(id+1)*B);++i)a[i]=color[id][int(a[i])-1];
        color[id]=same;
    };
    while(q--){
        int t,l;std::cin>>t>>l;
        if(t==2){int p=l-1;std::cout<<(kind==205 ? color[p/B][int(a[p])-1] : combine(a[p],tag[p/B]))<<'\n';continue;}
        int r,x,y=0;std::cin>>r>>x;if(kind==205)std::cin>>y;
        for(int i=l-1;i<r;){
            int id=i/B;
            if(i%B==0&&i+B<=r){
                if(kind==205)for(int &c:color[id])c=int(swap_color(c,x,y));
                else tag[id]=combine(tag[id],x);
                i+=B;
            }else{
                int end=std::min(r,(id+1)*B);
                if(kind==205)flush(id);
                for(;i<end;++i)a[i]=kind==205 ? swap_color(a[i],x,y) : combine(a[i],x);
            }
        }
    }
}
