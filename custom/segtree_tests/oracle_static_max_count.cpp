// Independent reference: sorted interval events, sparse-table maximum, sorted occurrences.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using i64=long long;
int main() {
    std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
    int n,m;std::cin>>n>>m;
    std::vector<std::pair<int,i64>> events;events.reserve(2*m);
    for(int i=0;i<m;++i){int l,r;i64 k;std::cin>>l>>r>>k;events.emplace_back(l,k);events.emplace_back(r+1,-k);}
    std::sort(events.begin(),events.end());
    std::vector<i64>a(n);i64 current=0;size_t at=0;
    for(int i=1;i<=n;++i){while(at<events.size()&&events[at].first<=i)current+=events[at++].second;a[i-1]=current;}
    std::vector<std::pair<i64,int>> positions;positions.reserve(n);
    for(int i=0;i<n;++i)positions.emplace_back(a[i],i+1);
    std::sort(positions.begin(),positions.end());
    std::vector<int> lg(n+1);for(int i=2;i<=n;++i)lg[i]=lg[i/2]+1;
    std::vector<std::vector<i64>> table(lg[n]+1);table[0]=a;
    for(int k=1;k<=lg[n];++k){table[k].resize(n-(1<<k)+1);for(int i=0;i+(1<<k)<=n;++i)table[k][i]=std::max(table[k-1][i],table[k-1][i+(1<<(k-1))]);}
    int q;std::cin>>q;
    while(q--){
        int l,r;std::cin>>l>>r;int k=lg[r-l+1];
        i64 maximum=std::max(table[k][l-1],table[k][r-(1<<k)]);
        auto first=std::lower_bound(positions.begin(),positions.end(),std::make_pair(maximum,l));
        auto last=std::upper_bound(positions.begin(),positions.end(),std::make_pair(maximum,r));
        std::cout<<maximum<<' '<<last-first<<'\n';
    }
}
