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
int n;cin>>n;ll lo,x,ans=0;cin>>lo;for(int i=1;i<n;i++){cin>>x;ans=max(ans,x-lo);lo=min(lo,x);}cout<<ans<<"\n";
}
