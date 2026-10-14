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
    int n,w; scanf("%d%d",&n,&w); vector<int> c(n); vector<long long> v(n);
    for(int i=0;i<n;++i) scanf("%d%lld",&c[i],&v[i]);
    const long long NEG=-(1LL<<60); vector<long long> unused(w+1,NEG),used(w+1,NEG); unused[0]=0;
    for(int s=0;s<=w;++s) {
        if(unused[s]!=NEG) for(int i=0;i<n;++i) {
            if(s+c[i]<=w) unused[s+c[i]]=max(unused[s+c[i]],unused[s]+v[i]);
            if(s+c[i]/2<=w) used[s+c[i]/2]=max(used[s+c[i]/2],unused[s]+v[i]);
        }
        if(used[s]!=NEG) for(int i=0;i<n;++i) if(s+c[i]<=w) used[s+c[i]]=max(used[s+c[i]],used[s]+v[i]);
    }
    long long answer=*max_element(used.begin(),used.end()); printf("%lld\n",answer==NEG ? -1LL : answer);
}
