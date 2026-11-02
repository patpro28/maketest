#include "testlib.h"
#include "params.h"
#include <vector>
void spaces(){inf.readSpace();while(!inf.eof() && inf.curChar()==' ')inf.readChar();}
int main(int argc,char**argv){
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"n");inf.readEoln();std::vector<int>seen(n+1,-1);
    for(int k=0;k<5;++k){
        for(int i=0;i<n;++i){
            if(i)spaces();int x=inf.readInt(1,n,"athlete");
            ensuref(seen[x]!=k,"Each photograph must be a permutation");seen[x]=k;
        }
        inf.readEoln();
    }
    inf.readEof();
}
