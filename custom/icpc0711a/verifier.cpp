#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,200000);
    inf.readSpace();
    int q=inf.readInt(1,200000);
    inf.readEoln();
    inf.readToken("[A-Z]{"+to_string(n)+"}");
    inf.readEoln();
    for(int i=0; i<q; i++) {
        inf.readInt(1,n);
        inf.readSpace();
        inf.readToken("[A-Z]");
        inf.readEoln();
    }
    inf.readEof();
}
