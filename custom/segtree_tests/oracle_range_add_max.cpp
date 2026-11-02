// Independent reference: square-root decomposition with a uniform offset per block.
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using i64=long long;
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n,m; std::cin>>n>>m;
    std::vector<i64> a(n); for (i64 &x:a) std::cin>>x;
    const int B=450; int count=(n+B-1)/B;
    std::vector<i64> offset(count),maximum(count);
    auto rebuild=[&](int id) {
        i64 best=std::numeric_limits<i64>::lowest();
        for (int i=id*B; i<std::min(n,(id+1)*B); ++i) best=std::max(best,a[i]);
        maximum[id]=best;
    };
    for (int id=0; id<count; ++id) rebuild(id);
    while (m--) {
        int t,l,r; std::cin>>t>>l>>r; --l;
        if (t==0) {
            i64 k; std::cin>>k;
            for (int i=l; i<r;) {
                int id=i/B;
                if (i%B==0 && i+B<=r) { offset[id]+=k; i+=B; }
                else {
                    int end=std::min(r,(id+1)*B);
                    for (; i<end; ++i) a[i]+=k;
                    rebuild(id);
                }
            }
        } else {
            i64 best=std::numeric_limits<i64>::lowest();
            for (int i=l; i<r;) {
                if (i%B==0 && i+B<=r) { best=std::max(best,maximum[i/B]+offset[i/B]); i+=B; }
                else { best=std::max(best,a[i]+offset[i/B]); ++i; }
            }
            std::cout<<best<<'\n';
        }
    }
}
