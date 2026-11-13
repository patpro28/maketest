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
    int n=big?200000:rnd(1,20),q=big?200000:rnd(1,40);
    string s(n,'A');
    for(int i=0; i<n; i++)s[i]=big&&seed%2?"ABC"[i%3]:char('A'+rnd(0,seed%2?2:25));
    cout<<n<<' '<<q<<'\n'<<s<<'\n';
    for(int i=0; i<q; i++)cout<<(i%5==0?1:i%5==1?n:rnd(1,n))<<' '<<char('A'+rnd(0,seed%2?2:25))<<'\n';
}
