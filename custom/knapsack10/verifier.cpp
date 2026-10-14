#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace();
    inf.readLong(-X_MAX,X_MAX,"X"); inf.readEoln();
    int sum=0;
    for(int i=0;i<n;++i) { if(i) inf.readSpace(); sum+=inf.readInt(1,SUM_MAX,"A"); }
    ensuref(sum<=SUM_MAX,"sum A exceeds limit"); inf.readEoln();
    inf.readEof();
}
