#include <algorithm>
#include <climits>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
int main(int argc,char **argv){
 (void)argc;
 int seed=stoi(argv[1]); mt19937_64 rng(20261019ULL+seed);
 const int kind=4;
 int n=seed<8? (seed<2?1:2+seed):seed<16?37+seed*3:200000;
 if(kind==6)n=max(n,2);
 vector<long long>a(n),b(n);
 for(int i=0;i<n;i++){
  long long x=0;
  if(seed==0||seed==2||seed==16)x=0;
  else if(seed==1||seed==3||seed==17)x=1000000000LL;
  else if(seed==4||seed==18)x=-1000000000LL;
  else if(seed==5||seed==19)x=(i%2?1000000000LL:-1000000000LL);
  else if(seed==6||seed==20)x=i-n/2;
  else if(seed==7||seed==21)x=n/2-i;
  else if(seed==22)x=(i==n-1?-1000000000LL:1);
  else if(seed==23)x=(i==0?-1000000000LL:1);
  else x=(long long)(rng()%2000000001ULL)-1000000000LL;
  a[i]=(kind==0||kind==3)?abs(x):x;
  if(kind==9){a[i]=max(0LL,x);b[i]=max(0LL,-x);}
 }
 int extra=kind==0?(seed>=16?200000:1+seed*2):kind==7?(seed%4==0?1:seed%4==1?n:seed%4==2?max(1,n/2):n-1):seed%4==0?1:seed%4==1?200000:seed%4==2?2:97;
 if(kind==7)extra=max(1,extra);
 cout<<n; if(kind==0||kind==7||kind==8)cout<<" "<<extra;cout<<"\n";
 if(kind==9){for(int i=0;i<n;i++)cout<<a[i]<<" "<<b[i]<<"\n";}
 else {for(int i=0;i<n;i++)cout<<a[i]<<(i+1==n?'\n':' ');}
 if(kind==0)for(int j=0;j<extra;j++){
  int l,r;
  if(j%4==0){l=1;r=n;}
  else if(j%4==1){l=r=1+rng()%n;}
  else {l=1+rng()%n;r=1+rng()%n;if(l>r)swap(l,r);}
  cout<<l<<" "<<r<<"\n";
 }
}
