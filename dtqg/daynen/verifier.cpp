#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc,char** argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); int c=inf.readInt(1,C_MAX,"C"); inf.readEoln();
    std::vector<long long> length(n+1);
    for(int i=1;i<=n;++i) {
        int type=inf.readInt(1,3,"type"); inf.readSpace();
        if(type==1) { inf.readInt(1,c,"x"); length[i]=1; }
        else {
            ensuref(i>1,"No earlier sequence exists at the first instruction");
            int u=inf.readInt(1,i-1,"u"); inf.readSpace();
            if(type==2) {
                int v=inf.readInt(1,i-1,"v"); length[i]=length[u]+length[v];
            } else {
                long long k=inf.readLong(0,LENGTH_MAX,"k");
                ensuref(!length[u] || k<=LENGTH_MAX/length[u],"Sequence length exceeds limit");
                length[i]=length[u]*k;
            }
        }
        ensuref(length[i]<=LENGTH_MAX,"Sequence length exceeds limit"); inf.readEoln();
    }
    inf.readEof();
}
