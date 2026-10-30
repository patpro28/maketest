#include "testlib.h"
#include "params.h"
int main(int argc,char **argv){
 registerValidation(argc,argv);
 int n=inf.readInt(1,N_MAX,"N");
 inf.readSpace(); int extra=inf.readInt(1,N_MAX,"M");
 (void)extra;
 inf.readEoln();
 for(int i=0;i<n;i++){if(i)inf.readSpace();inf.readInt(-A_MAX,A_MAX,"A");}inf.readEoln();
 inf.readEof();
}
