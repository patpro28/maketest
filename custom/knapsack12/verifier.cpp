#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); inf.readLong(0,A_MAX,"S"); inf.readSpace();
    inf.readInt(0,n,"K"); inf.readSpace(); inf.readLong(0,X_MAX,"X"); inf.readEoln();
    for(int i=0;i<n;++i) {
        long long a=inf.readLong(1,A_MAX,"A"); inf.readSpace();
        inf.readLong(a+1,a+D_MAX,"B"); inf.readEoln();
    }
    inf.readEof();
}
