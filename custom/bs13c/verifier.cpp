#include "testlib.h"
#include <set>
#include <string>
int main(int argc,char **argv) {
 registerValidation(argc,argv);

 int n=inf.readInt(1,200000,"N"); inf.readSpace(); int q=inf.readInt(1,200000,"Q"); inf.readEoln();
 for(int i=0;i<n;++i) { if(i) inf.readSpace(); inf.readInt(1,1000000000,"A"); } inf.readEoln();
 for(int i=0;i<q;++i) { inf.readInt(1,1000000000,"X"); inf.readEoln(); }
 inf.readEof();
}
