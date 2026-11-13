#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace();
    int m=inf.readInt(1,N_MAX,"M");
    inf.readEoln();
    inf.readToken("[a-z]{"+std::to_string(n)+"}","A"); inf.readEoln();
    inf.readToken("[a-z]{"+std::to_string(m)+"}","B"); inf.readEoln();
    for(int i=0;i<26;++i) { if(i) inf.readSpace(); inf.readLong(W_MIN,W_MAX,"W_c"); }
    inf.readEoln();
    inf.readEof();
}
