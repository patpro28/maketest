// Per-variable binary choices, followed by carry extraction; no subset table.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int MOD=1000000000;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int m,A,B;cin>>m>>A>>B;vector<int>a(m),b(m);int sa=0,sb=0;
    for(int i=0;i<m;++i){cin>>a[i]>>b[i];sa+=a[i];sb+=b[i];}
    int width=2*sb+1;vector<int>carry(sa*sb);carry[0]=1;
    for(int bit=0;bit<30;++bit){
        vector<int>work((2*sa+1)*width);
        for(int x=0;x<sa;++x)for(int y=0;y<sb;++y)work[x*width+y]=carry[x*sb+y];
        int xmax=sa-1,ymax=sb-1;
        for(int i=0;i<m;++i){
            for(int x=xmax;x>=0;--x)for(int y=ymax;y>=0;--y){
                int value=work[x*width+y];int& target=work[(x+a[i])*width+y+b[i]];
                target+=value;if(target>=MOD)target-=MOD;
            }
            xmax+=a[i];ymax+=b[i];
        }
        fill(carry.begin(),carry.end(),0);
        for(int x=(A>>bit)&1;x<=xmax;x+=2)for(int y=(B>>bit)&1;y<=ymax;y+=2)
            carry[(x/2)*sb+y/2]=work[x*width+y];
    }
    cout<<carry[0]<<'\n';
}
