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
    int n=big?(seed==11?1:seed==12?2:166666):rnd(1,7),k=seed==13?1:seed==14?n/2:n;
    vector<string>s(n);
    for(int i=0; i<n; i++) {
        if(big&&n<=2)s[i]=string(1000000/n,char('a'+i));
        else {
            int x=i;
            for(int j=0; j<(big?6:2); j++) {
                s[i]+=char('a'+x%26);
                x/=26;
            }
        }
    }
    shuffle(s.begin(),s.end(),rng);
    cout<<n<<' '<<k<<'\n';
    for(auto x:s)cout<<x<<'\n';
    shuffle(s.begin(),s.end(),rng);
    for(int i=0; i<k; i++)cout<<s[i];
    cout<<'\n';
}
