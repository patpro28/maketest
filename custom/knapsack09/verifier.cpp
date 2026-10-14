#include <set>
#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); inf.readInt(0,TARGET_MAX,"target"); inf.readEoln();
    for(int i=0;i<n;++i) { inf.readInt(1,A_MAX,"W"); inf.readSpace(); inf.readLong(1,V_MAX,"V"); inf.readEoln(); }
    inf.readEof();
}
