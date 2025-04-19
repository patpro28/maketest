#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define md 1000000007
void dfs(ll x, ll pr, vector<ll> tr[], ll dp[], ll cor[], map<ll, vector<ll>> &mpp, ll a[]){
  auto it = mpp.find(a[x]);
  (*it).second.push_back(x);
  for(ll i = 0; i < (ll)tr[x].size(); i++){
    ll y = tr[x][i];
    if(y == pr){
      continue;
    }
    dfs(y, x, tr, dp, cor, mpp, a);
    dp[x] += dp[y];
    if((ll)tr[y].size() > 1){
      dp[x] += dp[y];
    }
    dp[x] -= cor[y];
    dp[x] %= md;
  }
  if((ll)tr[x].size() == 1 && x != 0){
    dp[x] = 1;
  }
  (*it).second.pop_back();
  if((*it).second.size()){
    cor[(*it).second.back()] += dp[x];
    cor[(*it).second.back()] %= md;
  }
}
int main(){
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  ll t;
  cin>>t;
  while(t--){
    ll n;
    cin>>n;
    ll dp[n+1] = {};
    ll cor[n+1] = {};
    ll a[n+1] = {};
    vector<ll> tr[n+1];
    tr[0].push_back(1);
    tr[1].push_back(0);
    for(ll i = 0; i<n-1; i++){
      ll u,v;
      cin>>u>>v;
      tr[u].push_back(v);
      tr[v].push_back(u);
    }
    map<ll, vector<ll>> mpp;
    vector<ll> temp;
    for(ll i = 0; i < n + 1; i++){
      if(i){
        cin>>a[i];
      }else{
        a[i] = 0;
      }
      mpp.insert(make_pair(a[i], temp));
    }
    dfs(0, -1, tr, dp, cor, mpp, a);
    ll ans = dp[0];
    ans %= md;
    ans += md;
    ans %= md;
    cout<<ans<<"\n";
  }
  return 0;
}