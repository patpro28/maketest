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
int n,q;cin>>n>>q; vector<ll>s(n+1); for(int i=1;i<=n;i++){ll x;cin>>x;s[i]=s[i-1]+x;}while(q--){int l,r;cin>>l>>r;cout<<s[r]-s[l-1]<<"\n";}
}
