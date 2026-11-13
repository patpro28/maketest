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
    int n=big?100000:rnd(1,10);
    long long X=big?1000000000:rnd(1,10);
    cout<<n<<' '<<X<<'\n';
    set<pair<long long,long long>>l,r;
    for(int i=0; i<n; i++) {
        long long x,y;
        while(true) {
            x=big?(seed==11?X/2:seed==12?-X/2:rnd(-1000000000,1000000000)):rnd(-12,12);
            y=big?(seed<=12?i+1:rnd(1,1000000000)):rnd(1,15);
            long long a=gcd(abs(x),y),b=gcd(abs(x-X),y);
            pair<long long,long long>p= {
                x/a,y/a
            },q= {
                (x-X)/b,y/b
            };
            if(!l.count(p)&&!r.count(q)) {
                l.insert(p);
                r.insert(q);
                break;
            }
        }
        cout<<x<<' '<<y<<' '<<(big?1000000000:rnd(1,20))<<'\n';
    }
}
