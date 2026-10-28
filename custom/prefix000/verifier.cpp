#include "testlib.h"
#include "params.h"
int main(int argc,char **argv){
 registerValidation(argc,argv);
 int n=inf.readInt(1,N_MAX,"N");
 inf.readSpace(); int extra=inf.readInt(1,N_MAX,"Q");
 inf.readEoln();
 for(int i=0;i<n;i++){if(i)inf.readSpace();inf.readInt(0,A_MAX,"A");}inf.readEoln();
 for(int i=0;i<extra;i++){int l=inf.readInt(1,n,"L");inf.readSpace();inf.readInt(l,n,"R");inf.readEoln();}
 inf.readEof();
}
