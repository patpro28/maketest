#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace();
    int q=inf.readInt(1,Q_MAX,"Q"); inf.readEoln();
    for (int i=0; i<n; ++i) {
        if (i) inf.readSpace(); inf.readInt(VALUE_MIN,VALUE_MAX,"A_i");
    }
    inf.readEoln();
    for (int j=0; j<q; ++j) {
        int t=inf.readInt(1,2,"type"); inf.readSpace();
        int l=inf.readInt(1,n,t==1 ? "L" : "p");
        if (t==1) {
            inf.readSpace(); inf.readInt(l,n,"R");
            inf.readSpace(); inf.readInt(VALUE_MIN,VALUE_MAX,"x");

        }
        inf.readEoln();
    }
    inf.readEof();
}
