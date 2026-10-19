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

 ll k=seed==0?1000000000:rng.uniform(2,1000000000);
 string s;
 while(true) {
  ll value=seed==0?1000000000000LL:(seed==1?0:rng.uniform(0LL,1000000000000LL));
  string token=string(rng.uniform(0,50),'0')+to_string(value);
  if(s.size()+token.size()+1>100000) break;
  s+=token; s+=(rng.uniform(0,1)?'a':'Z');
 }
 if(seed%2==0) s.pop_back();
 cout<<k<<'\n'<<s<<'\n';
}
