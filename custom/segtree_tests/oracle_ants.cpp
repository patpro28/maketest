// Independent static reference: sparse-table GCD and occurrence-position vectors.
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n; std::cin >> n;
    std::vector<int> a(n), lg(n+1);
    std::map<int,std::vector<int>> positions;
    for (int i=0;i<n;++i) { std::cin>>a[i]; positions[a[i]].push_back(i); }
    for (int i=2;i<=n;++i) lg[i]=lg[i/2]+1;
    std::vector<std::vector<int>> table(lg[n]+1,std::vector<int>(n)); table[0]=a;
    for (int k=1;k<=lg[n];++k) for (int i=0;i+(1<<k)<=n;++i)
        table[k][i]=std::gcd(table[k-1][i],table[k-1][i+(1<<(k-1))]);
    int m; std::cin>>m;
    while (m--) {
        int l,r; std::cin>>l>>r; --l; --r;
        int k=lg[r-l+1],g=std::gcd(table[k][l],table[k][r-(1<<k)+1]);
        auto it=positions.find(g); int count=0;
        if (it!=positions.end()) count=int(std::upper_bound(it->second.begin(),it->second.end(),r)-std::lower_bound(it->second.begin(),it->second.end(),l));
        std::cout<<r-l+1-count<<'\n';
    }
}
