#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); inf.readInt(1,X_MAX,"X"); inf.readEoln();
    for(int i=0;i<n;++i) { inf.readLong(1,C_MAX,"C"); inf.readSpace(); inf.readInt(1,P_MAX,"P"); inf.readEoln(); }
    inf.readEof();
}
