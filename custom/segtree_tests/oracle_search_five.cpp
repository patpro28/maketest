// Independent references: ordered set and Fenwick selection; algebraic pair unranking.
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
using i64 = long long;
struct Fenwick {
    int n; std::vector<i64> f;
    explicit Fenwick(int m) : n(m), f(m + 1) {}
    void add(int p, i64 x) { for (; p <= n; p += p & -p) f[p] += x; }
    i64 sum(int p) const { i64 s=0; for (; p; p -= p & -p) s += f[p]; return s; }
    int select(i64 rank) const {
        int p=0, step=1; while (step <= n/2) step *= 2;
        for (; step; step /= 2) if (p+step <= n && f[p+step] < rank) { rank -= f[p+step]; p += step; }
        return p+1;
    }
};
i64 pairs(i64 c) { return c*(c-1)/2; }
int main(int argc, char **argv) {
    if (argc != 2) return 2;
    int kind=std::atoi(argv[1]); std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n,q; std::cin>>n>>q;
    std::vector<i64> a(n+1), b(n+1);
    if (kind != 128) for (int i=1; i<=n; ++i) std::cin>>a[i];
    if (kind == 116) for (int i=1; i<=n; ++i) std::cin>>b[i];
    Fenwick f(kind == 128 ? n+q : n);
    std::set<int> conflicts;
    std::vector<int> position(n+1), owner(n+q+1);
    int tail=n;
    auto flag=[&](int i) { return i==1 || a[i] != a[i-1]; };
    for (int i=1; i<=n; ++i) {
        if (kind == 116 && i<n && b[i] > a[i+1]) conflicts.insert(i);
        if (kind == 126) f.add(i,flag(i));
        if (kind == 127) f.add(i,a[i]==0);
        if (kind == 128) { f.add(i,1); position[i]=i; owner[i]=i; }
        if (kind == 129) f.add(i,pairs(a[i]));
    }
    while (q--) {
        int t; std::cin>>t;
        if (kind == 116) {
            if (t==1) {
                int i; i64 x; std::cin>>i>>x; b[i]=x;
                conflicts.erase(i); if (i<n && b[i]>a[i+1]) conflicts.insert(i);
            } else std::cout<<(conflicts.empty() ? -1 : *conflicts.begin())<<'\n';
        } else if (kind == 127) {
            int x; std::cin>>x;
            if (t<=2) { f.add(x,-int(a[x]==0)); a[x]+=t==1 ? 1 : -1; f.add(x,a[x]==0); }
            else std::cout<<(f.sum(n)<x ? -1 : f.select(x))<<'\n';
        } else if (kind == 128) {
            int x; std::cin>>x;
            if (t==1) { f.add(position[x],-1); position[x]=++tail; owner[tail]=x; f.add(tail,1); }
            else std::cout<<owner[f.select(x)]<<'\n';
        } else if (t==1) {
            int i; i64 x; std::cin>>i>>x;
            if (kind == 126) {
                f.add(i,-flag(i)); if (i<n) f.add(i+1,-flag(i+1));
                a[i]=x; f.add(i,flag(i)); if (i<n) f.add(i+1,flag(i+1));
            } else { f.add(i,pairs(x)-pairs(a[i])); a[i]=x; }
        } else {
            i64 k; std::cin>>k;
            if (f.sum(n)<k) { std::cout<<-1<<'\n'; continue; }
            int i=f.select(k);
            if (kind==126) { std::cout<<i<<'\n'; continue; }
            i64 c=a[i], rank=k-f.sum(i-1), remaining=pairs(c)-rank;
            // Count whole final rows via inverse triangular numbers, corrected exactly.
            i64 d=i64((1+std::sqrt(1.0L+8.0L*remaining))/2);
            while (pairs(d)>remaining) --d;
            while (pairs(d+1)<=remaining) ++d;
            i64 u=c-d, before=pairs(c)-pairs(c-u+1);
            i64 v=u+rank-before;
            std::cout<<i<<' '<<u<<' '<<v<<'\n';
        }
    }
}
