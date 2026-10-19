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

 ll a=seed==0?1:rng.uniform(1,1000000),b=seed==1?1:rng.uniform(1,1000000);
 ll l=seed==0?1:rng.uniform(1,1000000),r=seed==0?1000000:rng.uniform(int(l),1000000);
 if(seed==2) l=r=1000000;
 if(seed==3) { a=3; b=2; l=4; r=5; }
 if(seed==4) { a=b=1; l=1; r=1000000; }
 cout<<a<<' '<<b<<" 1\n"<<l<<' '<<r<<'\n';
}
