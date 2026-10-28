// Independent references use ordered sets/maps, two multisets, blocks and Fenwick trees.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>
using i64=long long;
struct Fenwick {
    int n;std::vector<i64> f;
    explicit Fenwick(int size):n(size),f(size+1){}
    void add(int i,i64 x){for(;i<=n;i+=i&-i)f[i]+=x;}
    i64 sum(int i)const{i64 s=0;for(;i;i-=i&-i)s+=f[i];return s;}
    int select(i64 k)const{
        int p=0,step=1;while(step<=n/2)step*=2;
        for(;step;step/=2)if(p+step<=n&&f[p+step]<k){k-=f[p+step];p+=step;}
        return p+1;
    }
};
int main(int argc,char **argv){
    if(argc!=2)return 2;
    int kind=std::atoi(argv[1]);std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
    int n,q;std::cin>>n>>q;
    if(kind==123){
        int w;std::cin>>w;std::vector<int>a(n);for(int &x:a)std::cin>>x;
        std::multiset<int>low,high;
        auto balance=[&](){
            size_t wanted=(low.size()+high.size()+1)/2;
            while(low.size()>wanted){auto it=std::prev(low.end());high.insert(*it);low.erase(it);}
            while(low.size()<wanted){auto it=high.begin();low.insert(*it);high.erase(it);}
        };
        auto insert=[&](int x){if(low.empty()||x<=*std::prev(low.end()))low.insert(x);else high.insert(x);balance();};
        for(int i=0;i<w;++i)insert(a[i]);
        for(int i=w;i<=n;++i){
            std::cout<<*std::prev(low.end())<<(i==n?'\n':' ');
            if(i==n)break;
            auto it=low.find(a[i-w]);
            if(it!=low.end())low.erase(it);else high.erase(high.find(a[i-w]));
            balance();insert(a[i]);
        }
        return 0;
    }
    std::vector<i64>a(n+1);std::string s,t;
    if(kind==114||kind==125)std::cin>>s;
    if(kind==114)std::cin>>t;else for(int i=1;i<=n;++i)std::cin>>a[i];
    Fenwick fenwick(n);
    std::set<std::pair<i64,int>> modes;
    std::map<i64,std::set<int>> scores;
    std::set<int> marked;
    auto peak=[&](int i){return i>1&&i<n&&a[i]>a[i-1]&&a[i]>a[i+1];};
    const int B=450;std::vector<int> masks((n+B-1)/B,1048575);
    auto rebuild=[&](int id){
        int mask=1048575;
        for(int i=id*B+1;i<=std::min(n,(id+1)*B);++i)mask&=int(a[i]);
        masks[id]=mask;
    };
    for(int i=1;i<=n;++i){
        if(kind==103&&a[i]>0)modes.insert({-a[i],i});
        if(kind==113&&peak(i))marked.insert(i);
        if(kind==114&&s[i-1]!=t[i-1])marked.insert(i);
        if(kind==115)scores[a[i]].insert(i);
        if(kind==124)fenwick.add(i,a[i]>0);
        if(kind==125)fenwick.add(i,a[i]);
    }
    if(kind==104)for(int id=0;id<int(masks.size());++id)rebuild(id);
    while(q--){
        int type;std::cin>>type;
        if(kind==103||kind==124){
            if(type<=2){
                int x;std::cin>>x;
                if(kind==103&&a[x]>0)modes.erase({-a[x],x});
                if(kind==124)fenwick.add(x,-int(a[x]>0));
                a[x]+=type==1?1:-1;
                if(kind==103&&a[x]>0)modes.insert({-a[x],x});
                if(kind==124)fenwick.add(x,a[x]>0);
            }else if(kind==103)std::cout<<(modes.empty()?-1:modes.begin()->second)<<'\n';
            else{int k;std::cin>>k;std::cout<<(fenwick.sum(n)<k?-1:fenwick.select(k))<<'\n';}
            continue;
        }
        if(type==1){
            int i;std::cin>>i;
            if(kind==114){
                int which=i;char c;std::cin>>i>>c;(which==1?s[i-1]:t[i-1])=c;
                marked.erase(i);if(s[i-1]!=t[i-1])marked.insert(i);
                continue;
            }
            if(kind==125){
                char c;i64 x;std::cin>>c>>x;s[i-1]=c;fenwick.add(i,x-a[i]);a[i]=x;continue;
            }
            i64 x;std::cin>>x;
            if(kind==115){auto it=scores.find(a[i]);it->second.erase(i);if(it->second.empty())scores.erase(it);scores[x].insert(i);}
            a[i]=x;
            if(kind==104)rebuild((i-1)/B);
            if(kind==113)for(int j=std::max(1,i-1);j<=std::min(n,i+1);++j){marked.erase(j);if(peak(j))marked.insert(j);}
            continue;
        }
        if(kind==104){
            int mask;std::cin>>mask;int i=1;
            for(;i<=n;){
                int id=(i-1)/B,end=std::min(n,(id+1)*B);
                if(i==id*B+1&&(masks[id]&mask)==mask){i=end+1;continue;}
                if((a[i]&mask)!=mask)break;
                ++i;
            }
            std::cout<<(i<=n?i:-1)<<'\n';
        }else if(kind==113)std::cout<<(marked.empty()?-1:*marked.begin())<<'\n';
        else if(kind==114)std::cout<<(marked.empty()?n:*marked.begin()-1)<<'\n';
        else if(kind==115){const auto &positions=scores.rbegin()->second;std::cout<<*positions.begin()<<' '<<*positions.rbegin()<<'\n';}
        else if(kind==125){
            i64 k;std::cin>>k;
            if(fenwick.sum(n)<k)std::cout<<-1<<'\n';
            else{int i=fenwick.select(k);std::cout<<s[i-1]<<' '<<i<<' '<<k-fenwick.sum(i-1)<<'\n';}
        }
    }
}
