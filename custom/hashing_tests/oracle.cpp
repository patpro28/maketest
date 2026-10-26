// Independent references: suffix arrays, KMP, Z, Booth, Fenwick and binary lifting.
#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>
#include "atcoder/string.hpp"
using namespace std;
using U=uint64_t;
using ll=long long;
struct Suffix {
    vector<int>sa,lcp,rank;vector<vector<int>>rmq;
    explicit Suffix(const string&s){sa=atcoder::suffix_array(s);lcp=atcoder::lcp_array(s,sa);rank.resize(s.size());for(int i=0;i<(int)sa.size();++i)rank[sa[i]]=i;}
    void build(){rmq.push_back(lcp);for(int j=1;(1<<j)<=(int)lcp.size();++j){int len=lcp.size()-(1<<j)+1;rmq.emplace_back(len);for(int i=0;i<len;++i)rmq[j][i]=min(rmq[j-1][i],rmq[j-1][i+(1<<(j-1))]);}}
    int common(int a,int b,int n)const{if(a==b)return n-a;int l=rank[a],r=rank[b];if(l>r)swap(l,r);int j=31-__builtin_clz(r-l);return min(rmq[j][l],rmq[j][r-(1<<j)]);}
};
vector<int> z(const string&p,const string&s){vector<int>a;for(char c:p)a.push_back(c);a.push_back(-1);for(char c:s)a.push_back(c);return atcoder::z_algorithm(a);}
int booth(const string&s){int n=s.size(),i=0,j=1,k=0;while(i<n && j<n && k<n){char a=s[(i+k)%n],b=s[(j+k)%n];if(a==b){++k;continue;}if(a>b){i+=k+1;if(i==j)++i;}else{j+=k+1;if(i==j)++j;}k=0;}return min(i,j);}
struct GH {
    int r,c;vector<U>h,p,q;static constexpr U X=1000003,Y=1000033;
    explicit GH(const vector<string>&s):r(s.size()),c(s[0].size()),h((r+1)*(c+1)),p(r+1,1),q(c+1,1){
        for(int i=1;i<=r;++i)p[i]=p[i-1]*X;
        for(int j=1;j<=c;++j)q[j]=q[j-1]*Y;
        for(int i=1;i<=r;++i)for(int j=1;j<=c;++j){int t=i*(c+1)+j;h[t]=s[i-1][j-1]+X*h[t-c-1]+Y*h[t-1]-X*Y*h[t-c-2];}
    }
    U get(int i,int j,int d)const{return h[(i+d)*(c+1)+j+d]-h[i*(c+1)+j+d]*p[d]-h[(i+d)*(c+1)+j]*q[d]+h[i*(c+1)+j]*p[d]*q[d];}
};
struct BIT {
    vector<U>t;explicit BIT(int n):t(n+1){}
    void add(int i,U x){for(++i;i<(int)t.size();i+=i&-i)t[i]+=x;}
    U pref(int i)const{U s=0;for(;i;i-=i&-i)s+=t[i];return s;}
    U get(int l,int r)const{return pref(r)-pref(l);}
};
int main(int argc,char**argv){
    if(argc!=2)return 1;int kind=stoi(argv[1]);ios::sync_with_stdio(false);cin.tie(nullptr);
    if(kind==0 || kind==2){
        int n,k=0;string s;cin>>n;if(kind==0)cin>>k;cin>>s;Suffix t(s);int ans=0;
        if(kind==0){
            if(k==1){cout<<n<<'\n';return 0;}
            deque<int>dq;
            for(int i=0;i<n-1;++i){while(!dq.empty() && t.lcp[dq.back()]>=t.lcp[i])dq.pop_back();dq.push_back(i);while(dq.front()<i-k+2)dq.pop_front();if(i>=k-2)ans=max(ans,t.lcp[dq.front()]);}
        }else{
            auto ok=[&](int d){int lo=t.sa[0],hi=lo;for(int i=1;i<n;++i){if(t.lcp[i-1]<d)lo=hi=t.sa[i];else{lo=min(lo,t.sa[i]);hi=max(hi,t.sa[i]);if(hi-lo>=d)return true;}}return false;};
            int l=0,r=n/2+1;while(r-l>1){int m=(l+r)/2;if(ok(m))l=m;else r=m;}ans=l;
        }cout<<ans<<'\n';
    }
    if(kind==1){
        int n,m;cin>>n>>m;vector<ll>a(n),b(m);for(ll&x:a)cin>>x;for(ll&x:b)cin>>x;
        if(m>n){cout<<0<<'\n';return 0;}if(m==1){cout<<n<<'\n';return 0;}
        vector<ll>p(m-1);for(int i=0;i<m-1;++i)p[i]=b[i+1]-b[i];vector<int>pi(m-1);
        for(int i=1;i<m-1;++i){int j=pi[i-1];while(j && p[i]!=p[j])j=pi[j-1];if(p[i]==p[j])++j;pi[i]=j;}
        int j=0,ans=0;for(int i=1;i<n;++i){ll x=a[i]-a[i-1];while(j && x!=p[j])j=pi[j-1];if(x==p[j])++j;if(j==m-1){++ans;j=pi[j-1];}}cout<<ans<<'\n';
    }
    if(kind==3){
        int n,m;string s,p;cin>>n>>m>>s>>p;auto a=z(p,s);reverse(s.begin(),s.end());reverse(p.begin(),p.end());auto b=z(p,s);int ans=0;
        for(int i=0;i+m<=n;++i){int l=min(m,a[m+1+i]),r=min(m,b[m+1+n-i-m]);ans+=l<m && l+r==m-1;}cout<<ans<<'\n';
    }
    if(kind==4){
        int n,q;string s;cin>>n>>q>>s;Suffix t(s);t.build();while(q--){int l,r,u,v;cin>>l>>r>>u>>v;--l;--u;int a=r-l,b=v-u,c=min({a,b,t.common(l,u,n)});char answer=c==min(a,b)?(a==b?'=':a<b?'<':'>'):(s[l+c]<s[u+c]?'<':'>');cout<<answer<<'\n';}
    }
    if(kind==5){
        int k;cin>>k;vector<int>a,owner;int total=0;for(int i=0;i<k;++i){string s;cin>>s;total+=s.size();for(char c:s){a.push_back(c-'a');owner.push_back(i);}a.push_back(26+i);owner.push_back(-1);}
        if(k==1){cout<<total<<'\n';return 0;}auto sa=atcoder::suffix_array(a,26+k);auto lcp=atcoder::lcp_array(a,sa);vector<int>count(k);int have=0,l=0,ans=0;deque<int>dq;
        for(int r=0;r<(int)sa.size();++r){
            if(r){while(!dq.empty() && lcp[dq.back()]>=lcp[r-1])dq.pop_back();dq.push_back(r-1);}
            int id=owner[sa[r]];if(id>=0 && !count[id]++)++have;
            while(have==k){ans=max(ans,lcp[dq.front()]);id=owner[sa[l++]];if(id>=0 && !--count[id])--have;while(!dq.empty() && dq.front()<l)dq.pop_front();}
        }cout<<ans<<'\n';
    }
    if(kind==6){int n,m;cin>>n>>m;set<string>groups;while(n--){string s;cin>>s;int p=booth(s);groups.insert(s.substr(p)+s.substr(0,p));}cout<<groups.size()<<'\n';}
    if(kind==7){
        int r,c,q;cin>>r>>c>>q;vector<string>s(r);for(auto&row:s)cin>>row;
        // Reflecting first, then transposing, gives a clockwise turn. Separate code from the solution.
        vector<GH>h;
        for(int turn=0;turn<4;++turn){h.emplace_back(s);reverse(s.begin(),s.end());vector<string>b(s[0].size(),string(s.size(),' '));for(int i=0;i<(int)s.size();++i)for(int j=0;j<(int)s[0].size();++j)b[j][i]=s[i][j];s.swap(b);}
        while(q--){int x,y,u,v,d;cin>>x>>y>>u>>v>>d;--x;--y;--u;--v;U target=h[0].get(x,y,d);bool ok=h[0].get(u,v,d)==target || h[1].get(v,r-u-d,d)==target || h[2].get(r-u-d,c-v-d,d)==target || h[3].get(c-v-d,u,d)==target;cout<<(ok?"YES":"NO")<<'\n';}
    }
    if(kind==8){
        int n,q;string s;cin>>n>>q>>s;vector<U>p(n+1,1);for(int i=1;i<=n;++i)p[i]=p[i-1]*1000003ULL;BIT f(n),b(n);
        for(int i=0;i<n;++i){f.add(i,U(s[i])*p[i]);b.add(i,U(s[i])*p[n-1-i]);}
        while(q--){int t;cin>>t;if(t==1){int i;char c;cin>>i>>c;--i;U delta=U(ll(c)-ll(s[i]));f.add(i,delta*p[i]);b.add(i,delta*p[n-1-i]);s[i]=c;}else{int l,r;cin>>l>>r;--l;cout<<(f.get(l,r)*p[n-r]==b.get(l,r)*p[l]?"YES":"NO")<<'\n';}}
    }
    if(kind==9){
        int n,q;string s;cin>>n>>q>>s;vector<vector<int>>g(n);for(int i=1;i<n;++i){int u,v;cin>>u>>v;--u;--v;g[u].push_back(v);g[v].push_back(u);}
        int lg=1;while((1<<lg)<=n)++lg;vector<vector<int>>up(lg,vector<int>(n));vector<vector<U>>f(lg,vector<U>(n)),b=f;vector<int>dep(n),order{0};vector<U>p(n+1,1);for(int i=1;i<=n;++i)p[i]=p[i-1]*1000033ULL;
        for(int i=0;i<n;++i){int u=order[i];f[0][u]=b[0][u]=s[u];for(int v:g[u])if(v!=up[0][u]){up[0][v]=u;dep[v]=dep[u]+1;order.push_back(v);}}
        for(int j=1;j<lg;++j)for(int u=0;u<n;++u){int mid=up[j-1][u];up[j][u]=up[j-1][mid];int half=1<<(j-1);f[j][u]=f[j-1][u]*p[half]+f[j-1][mid];b[j][u]=b[j-1][mid]*p[half]+b[j-1][u];}
        auto lca=[&](int u,int v){if(dep[u]<dep[v])swap(u,v);int diff=dep[u]-dep[v];for(int j=0;j<lg;++j)if(diff>>j&1)u=up[j][u];if(u==v)return u;for(int j=lg-1;j>=0;--j)if(up[j][u]!=up[j][v]){u=up[j][u];v=up[j][v];}return up[0][u];};
        auto get=[&](int u,int len){U a=0,z=0;int used=0;for(int j=lg-1;j>=0;--j)if(len>>j&1){int block=1<<j;a=a*p[block]+f[j][u];z=b[j][u]*p[used]+z;used+=block;u=up[j][u];}return pair<U,U>{a,z};};
        auto path=[&](int u,int v){int w=lca(u,v),a=dep[u]-dep[w]+1,bn=dep[v]-dep[w];auto x=get(u,a),y=get(v,bn);return pair<int,U>{a+bn,x.first*p[bn]+y.second};};
        while(q--){int u,v,x,y;cin>>u>>v>>x>>y;cout<<(path(u-1,v-1)==path(x-1,y-1)?"YES":"NO")<<'\n';}
    }
}
