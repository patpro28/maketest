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
    int n=big?200000:rnd(1,20);
    cout<<n<<'\n';
    for(int i=0; i<n; i++) {
        long long x=seed==11?1000000000000000LL:seed==12?999999999999999LL:seed==13?(i%2?1:999999999999999LL):big?1+(long long)(rng()%1000000000000000ULL):rnd(1,100000);
        cout<<x<<(i+1==n?'\n':' ');
    }
}
