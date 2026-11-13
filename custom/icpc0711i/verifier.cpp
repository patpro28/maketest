#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,100000);
    inf.readSpace();
    long long X=inf.readLong(1LL,1000000000LL);
    inf.readEoln();
    set<pair<long long,long long>>l,r;
    for(int i=0; i<n; i++) {
        long long x=inf.readLong(-1000000000LL,1000000000LL);
        inf.readSpace();
        long long y=inf.readLong(1LL,1000000000LL);
        inf.readSpace();
        inf.readLong(1LL,1000000000LL);
        inf.readEoln();
        long long a=gcd(abs(x),y),b=gcd(abs(x-X),y);
        ensuref(l.insert( {x/a,y/a}).second&&r.insert( {(x-X)/b,y/b}).second,"treasure on fence or duplicate point");
    }
    inf.readEof();
}
