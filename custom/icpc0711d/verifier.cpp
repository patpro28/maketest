#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(2,100000);
    inf.readEoln();
    for(int j=0; j<2; j++) {
        inf.readInts(n,0,(1<<30)-1);
        inf.readEoln();
    }
    inf.readEof();
}
