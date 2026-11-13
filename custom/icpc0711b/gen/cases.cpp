#include <bits/stdc++.h>
using namespace std;
int main(int argc,char**argv) {
    if(argc!=2)return 1;
    int seed=stoi(argv[1]);
    mt19937_64 rng(7112025+seed);
    auto rnd=[&](int l,int r) {
        return l+(int)(rng()%(r-l+1));
    };
    [[maybe_unused]] bool big=seed>=11;
    (void)rnd;
    int n=big?100000:rnd(1,14);
    cout<<n<<'\n';
    for(int i=0; i<n; i++)cout<<(seed==11?1:seed==12?i+1:seed==13?n-i:seed==14?(i%2?1000000000:1):rnd(1,big?1000000000:10))<<(i+1==n?'\n':' ');
}
