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
    int n=big?100000:rnd(2,8);
    vector<pair<int,int>>edges;
    if(seed==11) {
    }
    else if(seed==12) {
        for(int i=1; i<n; i++)edges.push_back( {i,i+1});
    }
    else if(seed==13) {
        for(int i=1; i+2<=n; i+=3) {
            edges.push_back( {i,i+1});
            edges.push_back( {i+1,i+2});
            edges.push_back( {i+2,i});
        }
    }
    else {
        int m=big?200000:rnd(0,16);
        for(int i=0; i<m; i++)edges.push_back( {rnd(1,n),rnd(1,n)});
    }
    cout<<n<<' '<<edges.size()<<'\n';
    for(auto [u,w]:edges)cout<<u<<' '<<w<<'\n';
}
