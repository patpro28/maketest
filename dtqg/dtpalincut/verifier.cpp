#include "testlib.h"
#include "params.h"
#include <algorithm>
#include <string>
void spaces(){inf.readSpace();while(!inf.eof() && inf.curChar()==' ')inf.readChar();}
int main(int argc,char**argv){
    registerValidation(argc,argv);
    inf.readToken("[a-z]{1,10000}","S");inf.readEoln();
    int t=inf.readInt(1,T_MAX,"T");inf.readEoln();
    for(int q=0;q<t;++q){
        int k=inf.readInt(1,K_MAX,"k");
        for(int i=0;i<k;++i){spaces();std::string length=inf.readToken("[0-9]+","length");
            ensuref(std::any_of(length.begin(),length.end(),[](char c){return c!='0';}),"Lengths must be positive");
        }
        inf.readEoln();
    }
    inf.readEof();
}
