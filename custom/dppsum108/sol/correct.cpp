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
int n,m;cin>>n>>m;vector<ll>cnt(m);cnt[0]=1;ll ans=0;int rem=0;for(int i=0;i<n;i++){ll x;cin>>x;rem=((rem+x)%m+m)%m;ans+=cnt[rem];cnt[rem]++;}cout<<ans<<"\n";
}
