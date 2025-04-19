//God & me 
//Oh my god, you did it!
#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
//#define int long long
using namespace std;
int in(){int x;return cin>>x,x;}
template<class T,class L>bool smax(T&x,L y){return x<y?(x=y,1):0;}template<class T,class L>bool smin(T&x,L y){return x>y?(x=y,1):0;}
typedef pair<int,int> pii;
const int maxn=1e5+17;
int n,q,col[maxn],cnt[maxn],sz[maxn],fen[maxn],ans[maxn];
bool bl[maxn];
vector<int>g[maxn];
vector<pii>as[maxn];
void getsz(int v=0,int p=-1){
  sz[v]=1;
  for(auto u:g[v])
    if(u!=p)
      getsz(u,v),sz[v]+=sz[u];
}
void up(int p,int v){
  p=maxn-p-1;
  for(;p<=maxn;p+=p&-p)
    fen[p]+=v;
}
int get(int p){
  p=maxn-p-1;
  int ans=0;
  for(;p;p-=p&-p)
    ans+=fen[p];
  return ans;
}
void add(int v,int p,int x){
  up(cnt[col[v]],-1);
  cnt[col[v]]+=x;
  up(cnt[col[v]],1);
  for(auto u:g[v])
    if(u!=p && !bl[u])
      add(u,v,x);
}
void dfs(int v=0,int p=-1,bool cl=0){
  int bigi=-1,mx=0;
  for(auto u:g[v])
    if(u!=p && sz[u]>mx)
      bigi=u,mx=sz[u];
  if(mx)
    bl[bigi]=1;
  for(auto u:g[v])
    if(u!=p && !bl[u])
      dfs(u,v,1);
  if(mx)
    dfs(bigi,v);
  add(v,p,1);
  for(auto q:as[v])
    ans[q.Y]=get(q.X);
  if(mx)
    bl[bigi]=0;
  if(cl)
    add(v,p,-1);
}
int main(){
  scanf("%d%d",&n,&q);
  for(int i=0;i<n;i++)
    scanf("%d",&col[i]);
  for(int i=1,v,u;i<n;i++)
    scanf("%d%d",&v,&u),g[--v].pb(--u),g[u].pb(v);
  getsz();
  for(int i=0,v,x;i<q;i++)
    scanf("%d%d",&v,&x),as[--v].pb({x,i});
  dfs();
  for(int i=0;i<q;i++)
    printf("%d ",ans[i]);
  putchar('\n');
  return 0;
}
