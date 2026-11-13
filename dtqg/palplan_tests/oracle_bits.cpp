#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
const int MOD=1000000000;
int m,sa,sb,masks,plane;
long long A,B;
vector<int>u,v,memo;
int solve(int bit,long long remaining_a,long long remaining_b,int forbidden){
    if(bit==60)return remaining_a==0 && remaining_b==0;
    int ca=int((A>>bit)-remaining_a),cb=int((B>>bit)-remaining_b);
    assert(0<=ca && ca<sa && 0<=cb && cb<sb);
    int& saved=memo[(bit*masks+forbidden)*plane+ca*sb+cb];
    if(saved!=-1)return saved;
    long long answer=0;int free=(masks-1)^forbidden,chosen=free;
    while(true){
        if(u[chosen]<=remaining_a && v[chosen]<=remaining_b &&
           ((remaining_a-u[chosen])&1)==0 && ((remaining_b-v[chosen])&1)==0){
            answer+=solve(bit+1,(remaining_a-u[chosen])/2,(remaining_b-v[chosen])/2,chosen);
            if(answer>=MOD)answer-=MOD;
        }
        if(!chosen)break;
        chosen=(chosen-1)&free;
    }
    return saved=int(answer);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);cin>>m>>A>>B;
    vector<int>a(m),b(m);for(int i=0;i<m;++i){cin>>a[i]>>b[i];sa+=a[i];sb+=b[i];}
    masks=1<<m;plane=sa*sb;u.resize(masks);v.resize(masks);
    for(int mask=0;mask<masks;++mask)for(int i=0;i<m;++i)if(mask>>i&1){u[mask]+=a[i];v[mask]+=b[i];}
    memo.assign(60*masks*plane,-1);
    cout<<solve(0,A,B,0)<<'\n';
}
