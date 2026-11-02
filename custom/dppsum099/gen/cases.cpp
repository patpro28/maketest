#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
using ll=long long;
int main(int argc,char **argv){
    (void)argc;
    const int code=99;
    int seed=stoi(argv[1]);mt19937_64 rng(20261102ULL+seed);
    int n=seed<2?1:seed<4?seed:seed<16?7+seed*5:200000;
    vector<ll>a(n);
    for(int i=0;i<n;++i){
        ll x;
        if(seed==0||seed==8||seed==16)x=0;
        else if(seed==1)x=1;
        else if(seed==2)x=i%2?-1:1;
        else if(seed==3)x=i==0?0:i%2?1:-1;
        else if(seed==17)x=1000000000;
        else if(seed==18)x=-1000000000;
        else if(seed==19)x=(ll)(rng()%11)-5;
        else if(seed%8==4)x=i-n/2;
        else if(seed%8==5)x=i%2?-1:0;
        else if(seed%8==6)x=i%2?-1000000000:1000000000;
        else if(seed%8==7)x=(ll)(rng()%7)-3;
        else if(seed%8==1)x=-1;
        else if(seed%8==2)x=i%3==0?0:i%3==1?1:-1;
        else x=i==0?1000000000:i==n-1?-1000000000:0;
        a[i]=x;
    }
    ll total=0;for(ll x:a)total+=x;
    ll target=seed==4?1:seed==5?-1:seed==7?2:seed==9?total:seed==11?total+1:seed==13?1000000000:seed==15?-1000000000:seed==17?total:seed==18?-100000000000000LL:0;
    int k=seed%4==0?1:seed%4==1?n:seed%4==2?max(1,n/2):max(1,n-1);
    if(seed==16)k=n/2;
    int lower=max(1,k/2),upper=k;
    if(seed%3==0)lower=upper=k;
    if(seed==16||seed==19){lower=1;upper=n;}
    if(seed==17)lower=upper=n;
    int divisor=vector<int>{1,2,7,200000}[seed%4];
    int residue=seed%3==0?divisor-1:seed%3==1?0:1%divisor;
    if(seed==16)residue=0;
    cout<<n;
    if(code>=91&&code<=96)cout<<' '<<target;
    if(code==94||code==95)cout<<' '<<k;
    if(code==96)cout<<' '<<lower<<' '<<upper;
    if(code==97||code==98)cout<<' '<<divisor;
    if(code==98)cout<<' '<<residue;
    cout<<'\n';
    for(int i=0;i<n;++i)cout<<a[i]<<(i+1==n?'\n':' ');
}
