#include "testlib.h"
#include "params.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
int main(int argc,char**argv){
registerValidation(argc,argv);
vector<bool> composite(1000001);vector<int> primes;
for(int i=2;i<=1000000;++i)if(!composite[i]){primes.push_back(i);if(1LL*i*i<=1000000)for(int j=i*i;j<=1000000;j+=i)composite[j]=true;}
int T=inf.readInt(1,T_MAX,"T");inf.readEoln();
for(int t=0;t<T;++t){long long value=inf.readLong(2,VALUE_MAX,"N");inf.readEoln();int k=0;
for(int p:primes){if(1LL*p*p>value)break;if(value%p)continue;int e=0;do{value/=p;++e;}while(value%p==0);ensuref(k==0 || k==e,"Prime exponents must all be equal");k=e;}
if(value>1)ensuref(k==0 || k==1,"Prime exponents must all be equal");}
inf.readEof();
}
