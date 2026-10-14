#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); inf.readInt(0,C_MAX,"C"); inf.readEoln();
    for(int i=0;i<n;++i) { inf.readInt(1,W_MAX,"W"); inf.readSpace(); inf.readLong(1,V_MAX,"V"); inf.readEoln(); }
    inf.readEof();
}
