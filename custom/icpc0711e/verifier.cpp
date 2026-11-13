#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(2,100000);
    inf.readSpace();
    int m=inf.readInt(0,200000);
    inf.readEoln();
    for(int i=0; i<m; i++) {
        inf.readInt(1,n);
        inf.readSpace();
        inf.readInt(1,n);
        inf.readEoln();
    }
    inf.readEof();
}
