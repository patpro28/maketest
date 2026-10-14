#include <algorithm>
#include <set>
#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); int q=inf.readInt(1,Q_MAX,"Q"); inf.readEoln(); int smallest=1000001;
    for(int i=0;i<n;++i) { if(i) inf.readSpace(); smallest=std::min(smallest,inf.readInt(1,A_MAX,"A")); } inf.readEoln();
    ensuref(smallest<=MIN_MAX,"minimum A exceeds limit");
    for(int i=0;i<q;++i) { inf.readLong(0,X_MAX,"X"); inf.readEoln(); }
    inf.readEof();
}
