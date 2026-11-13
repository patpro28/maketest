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
        1,8,9,26,27,343,344,1330,1331,1030300,1030301,1000000000000000000LL,999999999999999999LL,1000000000000LL,1000000000000000LL,999999999999LL
    };
    cout<<cases[seed]<<'\n';
}
