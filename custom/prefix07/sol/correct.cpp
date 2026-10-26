#include <algorithm>
#include <climits>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
using ll=long long;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,k;cin>>n>>k;vector<ll>s(n+1);for(int i=1;i<=n;i++){ll x;cin>>x;s[i]=s[i-1]+x;}ll mn=LLONG_MAX,ans=LLONG_MIN;for(int r=k;r<=n;r++){mn=min(mn,s[r-k]);ans=max(ans,s[r]-mn);}cout<<ans<<"\n";
}
