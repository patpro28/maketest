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
int n;cin>>n;vector<ll>c(n),s(2*n+1);for(int i=0;i<n;i++){ll a,b;cin>>a>>b;c[i]=a-b;}for(int i=1;i<=2*n;i++)s[i]=s[i-1]+c[(i-1)%n];deque<int>d;vector<int>ans;for(int r=1;r<2*n;r++){while(!d.empty()&&d.front()<r-n+1)d.pop_front();while(!d.empty()&&s[d.back()]>=s[r])d.pop_back();d.push_back(r);if(r>=n){int start=r-n+1;if(s[d.front()]>=s[start-1])ans.push_back(start);}}cout<<ans.size()<<"\n";for(int i:ans)cout<<i<<" ";cout<<"\n";
}
