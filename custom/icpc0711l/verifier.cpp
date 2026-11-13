#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(2,200000);
    inf.readEoln();
    string color=inf.readToken("[01]{"+to_string(n)+"}");
    inf.readEoln();
    vector<vector<int>>g(n);
    for(int i=1; i<n; i++) {
        int u=inf.readInt(1,n)-1;
        inf.readSpace();
        int v=inf.readInt(1,n)-1;
        inf.readSpace();
        inf.readLong(1LL,1000000000LL);
        inf.readEoln();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>par(n,-2),tin(n),tout(n),next(n),st= {
        0
    };
    par[0]=-1;
    int timer=0;
    while(!st.empty()) {
        int u=st.back();
        if(next[u]==0)tin[u]=timer++;
        if(next[u]==(int)g[u].size()) {
            tout[u]=timer;
            st.pop_back();
            continue;
        }
        int w=g[u][next[u]++];
        if(w==par[u])continue;
        ensuref(par[w]==-2,"not a tree");
        par[w]=u;
        st.push_back(w);
    }
    ensuref(timer==n,"disconnected tree");
    vector<int>bit(n+1);
    auto add=[&](int p,int d) {
        for(++p; p<=n; p+=p&-p)bit[p]+=d;
    };
    auto sum=[&](int p) {
        int s=0;
        for(; p; p-=p&-p)s+=bit[p];
        return s;
    };
    for(int i=0; i<n; i++)if(color[i]=='1')add(tin[i],1);
    int q=inf.readInt(2,200000);
    inf.readEoln();
    for(int i=0; i<q; i++) {
        int t=inf.readInt(1,3);
        inf.readSpace();
        int u=inf.readInt(1,n)-1;
        inf.readEoln();
        if(t==1) {
            color[u]^=1;
            add(tin[u],color[u]=='1'?1:-1);
        }
        else ensuref(sum(tout[u])-sum(tin[u])>0,"empty query");
    }
    inf.readEof();
}
