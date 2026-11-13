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
    int n=big?200000:rnd(2,9),q=big?200000:rnd(2,30);
    vector<int>par(n,-1),tin(n),tout(n),order;
    vector<vector<int>>ch(n);
    for(int i=1; i<n; i++) {
        par[i]=big&&seed==11?i-1:big&&seed==12?0:big&&seed==13?(i-1)/2:rnd(0,i-1);
        ch[par[i]].push_back(i);
    }
    vector<int>st= {
        0
    },idx(n);
    while(!st.empty()) {
        int u=st.back();
        if(idx[u]==0) {
            tin[u]=order.size();
            order.push_back(u);
        }
        if(idx[u]==(int)ch[u].size()) {
            tout[u]=order.size();
            st.pop_back();
        }
        else st.push_back(ch[u][idx[u]++]);
    }
    vector<int>bit(n+1),color(n);
    auto add=[&](int p,int d) {
        for(++p; p<=n; p+=p&-p)bit[p]+=d;
    };
    auto sum=[&](int p) {
        int s=0;
        for(; p; p-=p&-p)s+=bit[p];
        return s;
    };
    string colors;
    for(int i=0; i<n; i++) {
        color[i]=i==0?1:rnd(0,1);
        colors+=char('0'+color[i]);
        if(color[i])add(tin[i],1);
    }
    cout<<n<<'\n'<<colors<<'\n';
    for(int i=1; i<n; i++)cout<<i+1<<' '<<par[i]+1<<' '<<(big?1000000000:rnd(1,20))<<'\n';
    cout<<q<<'\n';
    for(int i=0; i<q; i++) {
        int t=rnd(1,3),u=rnd(0,n-1);
        if(t==1) {
            if(u==0)u=1;
            color[u]^=1;
            add(tin[u],color[u]?1:-1);
        }
        else if(sum(tout[u])-sum(tin[u])==0)u=0;
        cout<<t<<' '<<u+1<<'\n';
    }
}
