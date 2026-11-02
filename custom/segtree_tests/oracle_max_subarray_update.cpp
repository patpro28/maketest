// Independent reference: sqrt decomposition; blocks rebuilt by Kadane and boundary scans.
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using i64 = long long;
constexpr i64 NEG = std::numeric_limits<i64>::lowest() / 4;
struct Block { i64 sum, prefix, suffix, best; };
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n; std::cin >> n;
    std::vector<i64> a(n); for (i64 &x : a) std::cin >> x;
    const int B=700;
    std::vector<Block> blocks((n+B-1)/B);
    auto rebuild = [&](int id) {
        int l=id*B, r=std::min(n,l+B);
        i64 sum=0, prefix=NEG, ending=NEG, best=NEG;
        for (int i=l; i<r; ++i) {
            sum+=a[i]; prefix=std::max(prefix,sum);
            ending=std::max(a[i],ending+a[i]); best=std::max(best,ending);
        }
        i64 running=0,suffix=NEG;
        for (int i=r-1; i>=l; --i) { running+=a[i]; suffix=std::max(suffix,running); }
        blocks[id]={sum,prefix,suffix,best};
    };
    for (int id=0; id<int(blocks.size()); ++id) rebuild(id);
    int m; std::cin >> m;
    while (m--) {
        int type,x; i64 y; std::cin >> type >> x >> y;
        if (type==0) { a[x-1]=y; rebuild((x-1)/B); continue; }
        int l=x-1,r=int(y); i64 ending=NEG,best=NEG;
        for (int i=l; i<r;) {
            if (i%B==0 && i+B<=r) {
                const Block &block=blocks[i/B];
                best=std::max({best,block.best,ending+block.prefix});
                ending=std::max(block.suffix,ending+block.sum); i+=B;
            } else {
                ending=std::max(a[i],ending+a[i]); best=std::max(best,ending); ++i;
            }
        }
        std::cout << best << '\n';
    }
}
