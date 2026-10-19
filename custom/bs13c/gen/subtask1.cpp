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

 int n=seed==0?200000:(seed==1?5:1000),q=1000000/n;
 vector<int>a(n);
 for(int i=0;i<n;++i) a[i]=seed==2?7:(seed==3?2*(i+1):rng.uniform(1,1000000000));
 cout<<n<<' '<<q<<'\n';
 for(int i=0;i<n;++i) cout<<a[i]<<(i+1==n?'\n':' ');
 for(int i=0;i<q;++i) {
  int x=i%4==0?1:(i%4==1?1000000000:(i%4==2?a[rng.uniform(0,n-1)]:rng.uniform(1,1000000000)));
  cout<<x<<'\n';
 }
}
