#include "testlib.h"
#include "params.h"
void spaces(){inf.readSpace();while(!inf.eof() && inf.curChar()==' ')inf.readChar();}
int main(int argc,char** argv){
    registerValidation(argc,argv);
    int m=inf.readInt(1,M_MAX,"m");spaces();
    inf.readInt(1,RESOURCE_MAX,"A");spaces();inf.readInt(1,RESOURCE_MAX,"B");inf.readEoln();
    for(int i=0;i<m;++i){inf.readInt(1,COEF_MAX,"a_i");spaces();inf.readInt(1,COEF_MAX,"b_i");inf.readEoln();}
    inf.readEof();
}
