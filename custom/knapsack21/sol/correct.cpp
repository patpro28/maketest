#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main() {
    int n,x; scanf("%d%d",&n,&x); const int MOD=1000000007,INF=x+1;
    vector<int> best(x+1,INF),ways(x+1,0); best[0]=0; ways[0]=1;
    for(int i=0;i<n;++i) {
        int a; scanf("%d",&a);
        for(int s=a;s<=x;++s) if(best[s-a]!=INF) {
            int candidate=best[s-a]+1;
            if(candidate<best[s]) { best[s]=candidate; ways[s]=ways[s-a]; }
            else if(candidate==best[s]) { ways[s]+=ways[s-a]; if(ways[s]>=MOD) ways[s]-=MOD; }
        }
    }
    printf("%d %d\n",best[x]==INF ? -1 : best[x],ways[x]);
}
