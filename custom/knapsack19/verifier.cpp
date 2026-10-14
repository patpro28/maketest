#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); inf.readInt(0,W_MAX,"W"); inf.readEoln();
    for(int i=1;i<=n;++i) {
        inf.readInt(i==1 ? 0 : 1,i-1,"P"); inf.readSpace(); inf.readInt(1,C_MAX,"C"); inf.readSpace();
        inf.readLong(1,V_MAX,"V"); inf.readEoln();
    }
    inf.readEof();
}
