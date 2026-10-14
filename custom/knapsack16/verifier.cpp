#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readEoln();
    for(int i=0;i<n;++i) { inf.readInt(1,A_MAX,"A"); inf.readSpace(); inf.readInt(1,B_MAX,"B"); inf.readEoln(); }
    inf.readEof();
}
