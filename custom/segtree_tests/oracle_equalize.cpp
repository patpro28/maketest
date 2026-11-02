// Independent reference: Fenwick on floor(A_i/2), Fenwick on parity and sqrt maximum.
#include <algorithm>
#include <iostream>
#include <vector>
using i64 = long long;
struct Fenwick {
    int n; std::vector<i64> f;
    explicit Fenwick(int m) : n(m), f(m+1) {}
    void add(int i, i64 x) { for (; i<=n; i+=i&-i) f[i]+=x; }
    i64 prefix(int i) const { i64 result=0; for (; i; i-=i&-i) result+=f[i]; return result; }
    i64 range(int l,int r) const { return prefix(r)-prefix(l-1); }
};
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n,q; std::cin >> n >> q;
    std::vector<int> a(n);
    Fenwick halves(n), odd(n);
    for (int i=0; i<n; ++i) { std::cin>>a[i]; halves.add(i+1,a[i]/2); odd.add(i+1,a[i]%2); }
    const int B=700; std::vector<int> maxima((n+B-1)/B);
    auto rebuild=[&](int id) {
        int best=0; for (int i=id*B; i<std::min(n,(id+1)*B); ++i) best=std::max(best,a[i]);
        maxima[id]=best;
    };
    for (int id=0; id<int(maxima.size()); ++id) rebuild(id);
    while (q--) {
        int t,x,y; std::cin>>t>>x>>y;
        if (t==1) {
            halves.add(x,y/2-a[x-1]/2); odd.add(x,y%2-a[x-1]%2);
            a[x-1]=y; rebuild((x-1)/B); continue;
        }
        int maximum=0;
        for (int i=x-1; i<y;) {
            if (i%B==0 && i+B<=y) { maximum=std::max(maximum,maxima[i/B]); i+=B; }
            else { maximum=std::max(maximum,a[i]); ++i; }
        }
        // For even maximum: ceil((M-a)/2) = M/2-floor(a/2).
        // For odd maximum: ceil((M-a)/2) = (M+1)/2-floor(a/2)-[a odd].
        i64 result=i64((maximum+1)/2)*(y-x+1)-halves.range(x,y);
        if (maximum%2) result-=odd.range(x,y);
        std::cout<<result<<'\n';
    }
}
