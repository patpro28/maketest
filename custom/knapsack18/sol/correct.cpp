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
    int n; scanf("%d",&n); vector<int> t(n); int total=0;
    for(int &v:t) { scanf("%d",&v); total+=v; }
    int side=total+1; vector<char> dp(side*side,false); dp[0]=true; int prefix=0;
    for(int v:t) {
        vector<char> next(side*side,false);
        for(int x=0;x<=prefix;++x) for(int y=0;y<=prefix-x;++y) if(dp[x*side+y]) {
            next[(x+v)*side+y]=true; next[x*side+y+v]=true; next[x*side+y]=true;
        }
        prefix+=v; dp.swap(next);
    }
    int answer=total;
    for(int x=0;x<=total;++x) for(int y=0;y<=total-x;++y) if(dp[x*side+y]) answer=min(answer,max({x,y,total-x-y}));
    printf("%d\n",answer);
}
