#include "random.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll=long long;
int main(int argc,char **argv) {
 int seed=argc>1?atoi(argv[1]):0; Random rng(seed);

 int n=20,m=seed==0?0:(seed==1?10:(seed==2?30:rng.uniform(0,10)));
 if(seed>=5) { n=rng.uniform(1,20); m=rng.uniform(0,n/2+2); }
 vector<int>b;
 for(int i=1;i<=n;++i) {
  bool blocked=seed==3?i%2==0:(seed>=4?rng.uniform(0,1):false);
  if(blocked) b.push_back(i);
 }
 reverse(b.begin(),b.end());
 cout<<n<<' '<<b.size()<<' '<<m<<'\n';
 for(int i=0;i<int(b.size());++i) { if(i) cout<<' '; cout<<b[i]; } cout<<'\n';
}
