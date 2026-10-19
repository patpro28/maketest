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

 int n=100000; vector<int>b;
 for(int i=1;i<=n;++i) {
  bool blocked=seed==0?false:(seed==1?true:(seed==2?i%2==0:(seed==3?(i==1||i==n):rng.uniform(0,1))));
  if(blocked) b.push_back(i);
 }
 reverse(b.begin(),b.end());
 cout<<n<<' '<<b.size()<<" 0\n";
 for(int i=0;i<int(b.size());++i) { if(i) cout<<' '; cout<<b[i]; } cout<<'\n';
}
