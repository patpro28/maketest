#include "testlib.h"
#include "params.h"
int main(int argc,char** argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); int q=inf.readInt(1,Q_MAX,"Q"); inf.readEoln();
    for(int i=0;i<n;++i) { if(i) inf.readSpace(); inf.readInt(-VALUE_MAX,VALUE_MAX,"A"); }
    inf.readEoln(); int queries=0;
    for(int i=0;i<q;++i) {
        int type=inf.readInt(1,2,"type"); inf.readSpace();
        if(type==1) { inf.readInt(1,n,"p"); inf.readSpace(); inf.readInt(-VALUE_MAX,VALUE_MAX,"x"); }
        else { int l=inf.readInt(1,n,"L"); inf.readSpace(); inf.readInt(l,n,"R"); ++queries; }
        inf.readEoln();
    }
    ensuref(queries>0,"At least one query is required"); inf.readEof();
}
