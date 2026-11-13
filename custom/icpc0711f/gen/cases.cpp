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
    long long cases[]= {
        1,356,357,358,374,375,537,573,777,1000,777777777,1000000000,999999999,777777776,735735735,100000000
    };
    cout<<cases[seed]<<'\n';
}
