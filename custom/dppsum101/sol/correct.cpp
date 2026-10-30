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
int n;cin>>n;ll lo,hi,x;cin>>lo;hi=lo;int ans=0;for(int i=1;i<n;i++){cin>>x;if(x<lo||x>hi)ans++;lo=min(lo,x);hi=max(hi,x);}cout<<ans<<"\n";
}
