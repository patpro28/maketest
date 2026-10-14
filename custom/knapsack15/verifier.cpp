#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    inf.readInt(1,N_MAX,"N"); inf.readEoln();
    for(int d=0;d<10;++d) { if(d) inf.readSpace(); inf.readInt(1,C_MAX,"C"); } inf.readEoln();
    inf.readEof();
}
