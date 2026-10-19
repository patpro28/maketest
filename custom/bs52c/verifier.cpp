#include "testlib.h"
#include <set>
#include <string>
int main(int argc,char **argv) {
 registerValidation(argc,argv);

 int n=inf.readInt(3,300000,"N"); inf.readSpace(); int q=inf.readInt(1,300000,"Q"); inf.readEoln();
 for(int i=0;i<n;++i) { if(i) inf.readSpace(); inf.readInt(-1000000000,1000000000,"A"); } inf.readEoln();
 long long count=1LL*n*(n-1)*(n-2)/6;
 for(int i=0;i<q;++i) { inf.readLong(1LL,count,"K"); inf.readEoln(); }
 inf.readEof();
}
