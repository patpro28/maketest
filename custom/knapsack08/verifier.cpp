#include <set>
#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); inf.readInt(0,TARGET_MAX,"target"); inf.readEoln();
    std::set<int> seen;
    for(int i=0;i<n;++i) {
        if(i) inf.readSpace();
        int a=inf.readInt(1,A_MAX,"A");
        ensuref(seen.insert(a).second,"denominations must be distinct");
    }
    inf.readEoln();
    inf.readEof();
}
