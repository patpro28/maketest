#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<vector<int>>g(n);
    while(m--) {
        int u,v;
        cin>>u>>v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>col(n,-1),st;
    long long isolated=0,bip=0,odd=0;
    for(int s=0; s<n; s++)if(col[s]<0) {
        if(g[s].empty()) {
            col[s]=0;
            isolated++;
            continue;
        }
        bool ok=true;
        st= {
            s
        };
        col[s]=0;
        for(size_t i=0; i<st.size(); i++)for(int v:g[st[i]]) {
            if(col[v]<0) {
                col[v]=col[st[i]]^1;
                st.push_back(v);
            }
            else if(col[v]==col[st[i]])ok=false;
        }
        if(ok)bip++;
        else odd++;
    }
    cout<<isolated*(2*n-isolated)+2*bip*bip+2*bip*odd+odd*odd<<'\n';
}
