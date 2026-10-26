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
int n;cin>>n;vector<ll>a(n),suf(n);for(auto &x:a)cin>>x;suf[n-1]=a[n-1];for(int i=n-2;i>=0;i--)suf[i]=min(a[i],suf[i+1]);ll mx=LLONG_MIN;int ans=0;for(int i=0;i<n-1;i++){mx=max(mx,a[i]);if(mx<=suf[i+1])ans++;}cout<<ans<<"\n";
}
