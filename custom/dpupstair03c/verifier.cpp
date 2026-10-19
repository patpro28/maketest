#include "testlib.h"
#include <set>
#include <string>
int main(int argc,char **argv) {
 registerValidation(argc,argv);

 int n=inf.readInt(1,100000,"N"); inf.readSpace(); int k=inf.readInt(0,n,"K"); inf.readSpace(); inf.readInt(0,30,"M"); inf.readEoln();
 std::set<int> seen;
 for(int i=0;i<k;++i) { if(i) inf.readSpace(); int b=inf.readInt(1,n,"b"); ensuref(seen.insert(b).second,"Duplicate blocked position"); } inf.readEoln();
 inf.readEof();
}
