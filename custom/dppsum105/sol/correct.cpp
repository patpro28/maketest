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
int n;cin>>n;ll s=0,mn=0,ans=LLONG_MIN,x;while(n--){cin>>x;s+=x;ans=max(ans,s-mn);mn=min(mn,s);}cout<<ans<<"\n";
}
