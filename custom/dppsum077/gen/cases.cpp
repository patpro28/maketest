#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
int main(int argc, char **argv) {
    (void)argc;
    const int code = 77;
    int seed = stoi(argv[1]);
    mt19937_64 rng(20261102ULL + seed);
    int n=seed>=16?500:seed==14?1:seed==15?500:seed<2?1:seed<4?2:2+seed;
    int m=seed>=16?500:seed==14?500:seed==15?1:seed==0||seed==2?1:seed==1?2:seed==3?3:1+seed%7;
    int q=seed>=16?200000:8+seed*3;
    int divisor=vector<int>{1,2,7,1000000000}[seed%4];
    int u=seed%4==0?0:seed%4==1?-5:seed%4==2?-1000000000:999999999;
    int v=seed%4==0?0:seed%4==1?5:1000000000;
    vector<int> good,bad;
    if(code==71){good={-1000000000,-2,0,2,1000000000};bad={-1,1,999999999};}
    if(code==72){good={1,1000000000};bad={-1000000000,-1,0};}
    if(code==73){good={-1,-1000000000};bad={0,1,1000000000};}
    if(code==74){good={0,divisor,-divisor};bad=divisor==1?good:vector<int>{1,-1,divisor-1};}
    if(code==75){good={u,v,(int)(((long long)u+v)/2)};bad=u>A_MIN?vector<int>{(int)A_MIN,u-1}:v<A_MAX?vector<int>{v+1,(int)A_MAX}:good;}
    if(code==76){good={0,1,4,9,999950884};bad={-1,2,999950883,999950885,1000000000};}
    if(code==77){good={2,3,17,999983};bad={0,1,4,25,999999,1000000};}
    if(code==78){good={0,7,11,121,1001,999999999};bad={10,1010,123,1000000000};}
    if(code==79){good={7,77,17,70,707,700000007};bad={0,1,123,999999999,1000000000};}
    cout<<n<<' '<<m<<' '<<q;
    if(code==74)cout<<' '<<divisor;
    if(code==75)cout<<' '<<u<<' '<<v;
    cout<<'\n';
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            int x;
            if(code==70){
                if(seed==0||seed==16)x=0;
                else if(seed==1||seed==17)x=(int)A_MAX;
                else if(seed==2||seed==18)x=(int)A_MIN;
                else if(seed%3==0)x=(i+j)%2?-1000000000:1000000000;
                else x=(int)(A_MIN+(long long)(rng()%(A_MAX-A_MIN+1)));
            }else{
                bool marked=seed==1||seed==17?true:seed==0||seed==2||seed==18?false:((i*m+j+seed)%3!=0);
                x=marked?good[rng()%good.size()]:bad[rng()%bad.size()];
                if(seed==16)x=0;
                if(seed==19&&(i*m+j)%3==0)x=(int)(A_MIN+(long long)(rng()%(A_MAX-A_MIN+1)));
            }
            cout<<x<<(j+1==m?'\n':' ');
        }
    }
    for(int t=0;t<q;++t){
        int x1=1+rng()%n,x2=1+rng()%n,y1=1+rng()%m,y2=1+rng()%m;
        if(x1>x2)swap(x1,x2);
        if(y1>y2)swap(y1,y2);
        if(t%8==0){x1=y1=1;x2=n;y2=m;}
        if(t%8==1){x1=x2=n;y1=y2=m;}
        if(t%8==2){x1=x2=y1=y2=1;}
        if(t%8==3)x2=x1;
        if(t%8==4)y2=y1;
        if(t%8==5&&n>2&&m>2){x1=y1=2;x2=n;y2=m;}
        if(t%8==6){x1=x2=n;y1=1;y2=m;}
        cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<'\n';
    }
}
