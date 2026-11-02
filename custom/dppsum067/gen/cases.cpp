#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
int main(int argc, char **argv) {
    (void)argc;
    const int code = 67;
    int seed = stoi(argv[1]);
    mt19937_64 rng(20261102ULL + seed);
    int n = seed < 2 ? 1 : seed < 4 ? seed : seed < 16 ? 7 + seed * 5 : 200000;
    int k = seed % 4 == 0 ? 1 : seed % 4 == 1 ? n : seed % 4 == 2 ? max(1,n/2) : max(1,n-1);
    if (seed == 5 || seed == 13 || seed == 19) k = 1;
    if (seed == 16) k = n/2;
    int required = seed % 4 == 0 ? 0 : seed % 4 == 1 ? k : seed % 4 == 2 ? max(1,k/2) : 1;
    if (seed == 0 || seed == 4 || seed == 5 || seed == 12 || seed == 13) required = 1;
    if (seed == 16 || seed == 17) required = 0;
    int divisor = vector<int>{1,2,7,1000000000}[seed%4];
    int u = seed%4 == 0 ? 0 : seed%4 == 1 ? -5 : seed%4 == 2 ? -1000000000 : 999999999;
    int v = seed%4 == 0 ? 0 : seed%4 == 1 ? 5 : 1000000000;
    int h = vector<int>{0,1,81,7}[seed%4];
    vector<int> good,bad;
    if (code==60) { good={-1000000000,-2,0,2,1000000000}; bad={-1,1,999999999}; }
    if (code==61) { good={1,1000000000}; bad={-1000000000,-1,0}; }
    if (code==62) { good={-1,-1000000000}; bad={0,1,1000000000}; }
    if (code==63) { good={0,divisor,-divisor}; bad=divisor==1?good:vector<int>{1,-1,divisor-1}; }
    if (code==64) { good={u,v,(int)(((long long)u+v)/2)};bad=u>A_MIN?vector<int>{(int)A_MIN,u-1}:v<A_MAX?vector<int>{v+1,(int)A_MAX}:good; }
    if (code==65) { good={0,1,4,9,999950884}; bad={-1,2,999950883,999950885,1000000000}; }
    if (code==66) { good={2,3,17,999983}; bad={0,1,4,25,999999,1000000}; }
    if (code==67) { good={0,7,11,121,1001,999999999}; bad={10,1010,123,1000000000}; }
    if (code==68) { good={7,77,17,70,707,700000007}; bad={0,1,123,999999999,1000000000}; }
    if (code==69) {
        good=h==0?vector<int>{0}:h==1?vector<int>{1,10,1000000000}:h==81?vector<int>{999999999}:vector<int>{7,16,70};
        bad=h==0?vector<int>{1,2,1000000000}:h==1?vector<int>{0,2,11}:h==81?vector<int>{0,1,1000000000}:vector<int>{0,1,10};
    }
    cout<<n<<' '<<k<<' '<<required;
    if(code==63)cout<<' '<<divisor;
    if(code==64)cout<<' '<<u<<' '<<v;
    if(code==69)cout<<' '<<h;
    cout<<'\n';
    for(int i=0;i<n;++i) {
        bool marked;
        if(seed==0||seed==3||seed==8)marked=false;
        else if(seed==1||seed==9)marked=true;
        else if(seed==4||seed==13)marked=i==0;
        else if(seed==5||seed==12)marked=i==n-1;
        else if(seed==2||seed==10||seed==18)marked=i%2;
        else if(seed==6)marked=(i/3)%2;
        else if(seed==7||seed==15)marked=i>=n/2;
        else marked=rng()%2;
        int x=marked?good[rng()%good.size()]:bad[rng()%bad.size()];
        if(seed==16)x=A_MIN<0?(int)A_MIN:(int)A_MAX;
        if(seed==17)x=(int)A_MAX;
        if(seed==19&&i%3==0)x=(int)(A_MIN+(long long)(rng()%(A_MAX-A_MIN+1)));
        cout<<x<<(i+1==n?'\n':' ');
    }
}
