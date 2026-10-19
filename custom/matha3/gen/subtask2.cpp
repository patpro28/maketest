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

 const ll LIM=1000000000000000000LL;
 ll b=seed==0?1:(seed==1?1000000:rng.uniform(1,1000000)); int q=seed%10==0?100000:1000;
 cout<<1<<' '<<b<<' '<<q<<'\n';
 for(int i=0;i<q;++i) {
  ll l,r;
  if(i==0) { l=1; r=LIM; }
  else if(i==1) l=r=LIM;
  else if(i%4==0) { l=rng.uniform(0LL,LIM/(b+1)-1)*(b+1)+1; r=l; }
  else { l=rng.uniform(1LL,LIM); r=rng.uniform(l,LIM); }
  cout<<l<<' '<<r<<'\n';
 }
}
