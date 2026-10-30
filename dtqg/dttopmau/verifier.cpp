#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>
int main(int argc,char** argv){
    registerValidation(argc,argv);const int kind=2;
    int n=inf.readInt(1,N_MAX,"N");int q=0;
    if(kind==2){inf.readSpace();q=inf.readInt(1,200000,"Q");}inf.readEoln();
    if(kind==4){
        for(int i=0;i<n;++i){inf.readInt(0,1000000000,"A");inf.readSpace();inf.readInt(1,1000,"W");inf.readEoln();}
    }else{
        for(int i=0;i<n;++i){if(i)inf.readSpace();
            if(kind<=2)inf.readInt(1,1000000000,"color");else inf.readInt(0,n,"K");
        }inf.readEoln();
    }
    std::vector<int>parent(n+1);std::iota(parent.begin(),parent.end(),0);
    auto root=[&](int u){while(parent[u]!=u){parent[u]=parent[parent[u]];u=parent[u];}return u;};
    for(int i=1;i<n;++i){
        int u=inf.readInt(1,n,"u");inf.readSpace();int v=inf.readInt(1,n,"v");
        if(kind==5){inf.readSpace();inf.readToken("[a-j]","letter");}inf.readEoln();
        int a=root(u),b=root(v);ensuref(a!=b,"Edges must form a tree");parent[a]=b;
    }
    for(int i=0;i<q;++i){inf.readInt(1,n,"u");inf.readSpace();inf.readInt(0,n,"k");inf.readEoln();}
    inf.readEof();
}
