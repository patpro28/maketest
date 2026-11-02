#include <array>
#include <cstdio>
#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;
const int MOD=1000000000;
struct Choice { int a,b,count; };
int main(){
    if(FILE* file=fopen("PLAN.INP","r")){
        fclose(file);
        if(!freopen("PLAN.INP","r",stdin))return 1;
        if(!freopen("PLAN.OUT","w",stdout))return 1;
    }
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int m,A,B;cin>>m>>A>>B;
    vector<int>a(m),b(m);int sa=0,sb=0;
    for(int i=0;i<m;++i){cin>>a[i]>>b[i];sa+=a[i];sb+=b[i];}
    vector<vector<int>>ways(sa+1,vector<int>(sb+1));ways[0][0]=1;
    for(int i=0;i<m;++i)
        for(int x=sa;x>=a[i];--x)for(int y=sb;y>=b[i];--y)
            ways[x][y]+=ways[x-a[i]][y-b[i]];
    array<vector<Choice>,4> choices;
    for(int x=0;x<=sa;++x)for(int y=0;y<=sb;++y)if(ways[x][y])
        choices[(x%2)*2+y%2].push_back({x,y,ways[x][y]});
    vector<vector<int>>dp(sa,vector<int>(sb));dp[0][0]=1;
#ifdef COUNT_TRANSITIONS
    uint64_t transitions=0;
#endif
    for(int bit=0;bit<30;++bit){
        vector<vector<int>>next(sa,vector<int>(sb));
        int da=(A>>bit)&1,db=(B>>bit)&1;
        for(int ca=0;ca<sa;++ca)for(int cb=0;cb<sb;++cb)if(dp[ca][cb]){
            int parity=((da^(ca&1))*2)+(db^(cb&1));
#ifdef COUNT_TRANSITIONS
            transitions+=choices[parity].size();
#endif
            for(auto [x,y,count]:choices[parity]){
                int na=(ca+x-da)/2,nb=(cb+y-db)/2;
                if(na<0 || nb<0)continue;
                int& value=next[na][nb];
                value=int((value+1LL*dp[ca][cb]*count)%MOD);
            }
        }
        dp.swap(next);
    }
    cout<<dp[0][0]<<'\n';
#ifdef COUNT_TRANSITIONS
    cerr<<transitions<<'\n';
#endif
}
