#include "testlib.h"
#include <set>
#include <string>
int main(int argc,char **argv) {
 registerValidation(argc,argv);

 inf.readInt(1,1000000,"A"); inf.readSpace(); inf.readInt(1,1000000,"B"); inf.readSpace();
 int q=inf.readInt(1,100000,"Q"); inf.readEoln();
 for(int i=0;i<q;++i) { long long l=inf.readLong(1LL,1000000000000000000LL,"L"); inf.readSpace(); inf.readLong(l,1000000000000000000LL,"R"); inf.readEoln(); }
 inf.readEof();
}
