#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
using ll = long long;
int main(int argc, char **argv) {
    (void)argc;
    const int code=88;
    int seed=stoi(argv[1]);
    mt19937_64 rng(20261102ULL+seed);
    int n=seed<2?1:seed<4?seed:seed<16?7+seed*5:200000;
    vector<ll>a(n);
    for(int i=0;i<n;++i){
        ll x;
        if(seed==0||seed==9||seed==16||seed==18)x=0;
        else if(seed==1||seed==3||seed==8)x=1;
        else if(seed==2)x=i%2;
        else if(seed==4)x=i;
        else if(seed==5)x=i==n-1?1000000000:0;
        else if(seed==6)x=(i/3)%2;
        else if(seed==7)x=i==0?1000000000:0;
        else if(seed==10)x=i%2?0:1000000000;
        else if(seed==11)x=rng()%10;
        else if(seed==12)x=i==0?0:1000000000;
        else if(seed==13)x=i==n-1?0:1000000000;
        else if(seed==14||seed==17)x=1000000000;
        else if(seed==15)x=i%3?0:1;
        else x=rng()%1000000001ULL;
        a[i]=x;
    }
    ll total=0;for(ll x:a)total+=x;
    ll target;
    if(seed==0||seed==5||seed==7||seed==8||seed==18)target=1;
    else if(seed==1||seed==2||seed==6||seed==9||seed==16||seed==17)target=0;
    else if(seed==3||seed==15)target=total+1;
    else if(seed==10||seed==12||seed==13)target=1000000000;
    else if(seed==11)target=total;
    else if(seed==14)target=S_MAX;
    else target=total/2;
    cout<<n<<' ';
    if(code==89){
        ll lower=seed%3==0?0:target;
        ll upper=min(S_MAX,target+seed%3);
        if(seed==16||seed==17){lower=upper=0;}
        if(seed==18){lower=0;upper=1;}
        if(seed==19){lower=total/4;upper=total/2;}
        cout<<lower<<' '<<upper;
    }else cout<<target;
    cout<<'\n';
    for(int i=0;i<n;++i)cout<<a[i]<<(i+1==n?'\n':' ');
}
