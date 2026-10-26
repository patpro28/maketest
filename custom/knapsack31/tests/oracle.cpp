// Independent formulation: exact number of remaining casts and remaining damage.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int n,k,x; scanf("%d%d%d",&n,&k,&x);
    vector<long long> c(n); vector<int> d(n);
    for(int i=0;i<n;++i) scanf("%lld%d",&c[i],&d[i]);
    const long long INF=1LL<<60;
    vector<long long> previous(x+1,INF),current(x+1,INF);
    previous[0]=0;
    for(int remaining=1;remaining<=k;++remaining) {
        for(int need=0;need<=x;++need) {
            current[need]=INF;
            for(int i=0;i<n;++i) {
                int rest=max(0,need-d[i]);
                if(previous[rest]!=INF) current[need]=min(current[need],c[i]+previous[rest]);
            }
        }
        previous.swap(current);
    }
    printf("%lld\n",previous[x]==INF ? -1LL : previous[x]);
}
