#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;
using ull=unsigned long long;
vector<ull> divisors;map<pair<ull,int>,ull> memo;
ull solve(ull value,int first){
 if(value<divisors[first])return 0;
 auto key=make_pair(value,first);auto it=memo.find(key);if(it!=memo.end())return it->second;
 ull answer=1;
 for(int i=first;i<int(divisors.size()) && divisors[i]<=value/divisors[i];++i)
  if(value%divisors[i]==0)answer+=solve(value/divisors[i],i);
 memo[key]=answer;return answer;
}
int main(){
 ios::sync_with_stdio(false);cin.tie(nullptr);int T;cin>>T;
 map<ull,ull> answers;
 while(T--){ull n;cin>>n;if(answers.count(n)){cout<<answers[n]<<'\n';continue;}
  ull remaining=n;vector<pair<ull,int>> factors;
  for(ull p=2;p<=remaining/p;++p)if(remaining%p==0){int e=0;do{remaining/=p;++e;}while(remaining%p==0);factors.push_back({p,e});}
  if(remaining>1)factors.push_back({remaining,1});
  divisors={1};for(auto [p,k]:factors){int size=divisors.size();ull power=1;for(int e=1;e<=k;++e){power*=p;for(int i=0;i<size;++i)divisors.push_back(divisors[i]*power);}}
  sort(divisors.begin(),divisors.end());divisors.erase(divisors.begin());memo.clear();
  ull answer=solve(n,0)-1;answers[n]=answer;cout<<answer<<'\n';
 }
}
