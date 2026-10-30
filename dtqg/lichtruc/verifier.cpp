#include "testlib.h"
#include "params.h"
int main(int argc,char** argv) {
    registerValidation(argc,argv);
    int p=inf.readInt(1,P_MAX,"P"); inf.readSpace(); inf.readLong(0,D_MAX,"D"); inf.readEoln();
    for(int i=0;i<p;++i) {
        for(int j=0;j<3;++j) {
            if(j) inf.readSpace(); inf.readInt(-VALUE_MAX,VALUE_MAX,"score");
        }
        inf.readEoln();
    }
    inf.readEof();
}
