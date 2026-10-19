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

 string s;
 for(int i=0;i<100000;++i) {
  char c;
  if(seed==0) c='9';
  else if(seed==1) c='A';
  else if(seed==2) c='0';
  else if(seed==3) c=(i%2?'Z':'7');
  else c=rng.uniform(0,3)==0?'a':char('0'+rng.uniform(0,9));
  s+=c;
 }
 cout<<"1\n"<<s<<'\n';
}
