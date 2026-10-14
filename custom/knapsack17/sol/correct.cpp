#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main() {
    int n,c; scanf("%d%d",&n,&c); const long long NEG=-(1LL<<60);
    vector<long long> unused(c+1,NEG),used(c+1,NEG); unused[0]=0;
    for(int i=0;i<n;++i) {
        int w; long long v; scanf("%d%lld",&w,&v);
        auto nu=unused, ny=used;
        for(int s=0;s<=c;++s) {
            if(unused[s]!=NEG) {
                if(s+w<=c) nu[s+w]=max(nu[s+w],unused[s]+v);
                if(s+w/2<=c) ny[s+w/2]=max(ny[s+w/2],unused[s]+v);
            }
            if(used[s]!=NEG && s+w<=c) ny[s+w]=max(ny[s+w],used[s]+v);
        }
        unused.swap(nu); used.swap(ny);
    }
    long long answer=*max_element(used.begin(),used.end());
    printf("%lld\n",answer==NEG ? -1LL : answer);
}
