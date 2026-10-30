#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>
int main(int argc,char** argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,N_MAX,"N"); inf.readSpace(); int q=inf.readInt(1,Q_MAX,"Q"); inf.readEoln();
    for(int i=0;i<n;++i) { if(i) inf.readSpace(); inf.readInt(-VALUE_MAX,VALUE_MAX,"W"); }
    inf.readEoln(); std::vector<int> parent(n+1); std::iota(parent.begin(),parent.end(),0);
    auto root=[&](int u) { while(u!=parent[u]) { parent[u]=parent[parent[u]]; u=parent[u]; } return u; };
    for(int i=1;i<n;++i) {
        int u=inf.readInt(1,n,"u"); inf.readSpace(); int v=inf.readInt(1,n,"v"); inf.readEoln();
        int a=root(u),b=root(v); ensuref(a!=b,"Edges must form a tree"); parent[a]=b;
    }
    for(int i=0;i<q;++i) {
        inf.readInt(1,n,"u"); inf.readSpace(); inf.readInt(-VALUE_MAX,VALUE_MAX,"x"); inf.readEoln();
    }
    inf.readEof();
}
