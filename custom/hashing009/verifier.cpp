#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>
using namespace std;
constexpr int KIND=9;
int main(int argc,char**argv){
    registerValidation(argc,argv);
    auto word=[](int len,const char*name){string s=inf.readToken("[a-z]+",name);ensuref((int)s.size()==len,"Wrong string length");inf.readEoln();return s;};
    auto range=[](int n){int l=inf.readInt(1,n,"l");inf.readSpace();inf.readInt(l,n,"r");};
    if(KIND==0 || KIND==2){int n=inf.readInt(1,N_MAX,"n");if(KIND==0){inf.readSpace();inf.readInt(1,n,"k");}inf.readEoln();word(n,"S");}
    if(KIND==1 || KIND==3){
        int n=inf.readInt(1,N_MAX,"n");inf.readSpace();int m=inf.readInt(1,N_MAX,"m");inf.readEoln();
        if(KIND==3){word(n,"S");word(m,"P");}
        else for(int len:{n,m}){for(int i=0;i<len;++i){if(i)inf.readSpace();inf.readInt(-1000000000,1000000000,"height");}inf.readEoln();}
    }
    if(KIND==4 || KIND==8 || KIND==9){
        int n=inf.readInt(1,N_MAX,"n");inf.readSpace();int q=inf.readInt(1,Q_MAX,"q");inf.readEoln();word(n,"S");
        if(KIND==9){
            vector<int>p(n+1);iota(p.begin(),p.end(),0);
            auto find=[&](int x){while(p[x]!=x){p[x]=p[p[x]];x=p[x];}return x;};
            for(int i=1;i<n;++i){int u=inf.readInt(1,n,"u");inf.readSpace();int v=inf.readInt(1,n,"v");inf.readEoln();u=find(u);v=find(v);ensuref(u!=v,"Edges must form a tree");p[u]=v;}
        }
        for(int i=0;i<q;++i){
            if(KIND==4){range(n);inf.readSpace();range(n);}
            if(KIND==9){for(int j=0;j<4;++j){if(j)inf.readSpace();inf.readInt(1,n,"vertex");}}
            if(KIND==8){int type=inf.readInt(1,2,"type");inf.readSpace();if(type==1){inf.readInt(1,n,"position");inf.readSpace();inf.readToken("[a-z]","character");}else range(n);}
            inf.readEoln();
        }
    }
    if(KIND==5){int k=inf.readInt(1,N_MAX,"k");inf.readEoln();int total=0;for(int i=0;i<k;++i){string s=inf.readToken("[a-z]+","S");total+=s.size();ensuref(total<=N_MAX,"Total length exceeded");inf.readEoln();}}
    if(KIND==6){int n=inf.readInt(1,N_MAX,"n");inf.readSpace();int m=inf.readInt(1,N_MAX,"m");inf.readEoln();ensuref(1LL*n*m<=N_MAX,"Total length exceeded");for(int i=0;i<n;++i)word(m,"S");}
    if(KIND==7){
        int r=inf.readInt(1,1000,"R");inf.readSpace();int c=inf.readInt(1,1000,"C");inf.readSpace();int q=inf.readInt(1,Q_MAX,"q");inf.readEoln();
        for(int i=0;i<r;++i)word(c,"row");
        for(int i=0;i<q;++i){int a=inf.readInt(1,r,"r1");inf.readSpace();int b=inf.readInt(1,c,"c1");inf.readSpace();int u=inf.readInt(1,r,"r2");inf.readSpace();int v=inf.readInt(1,c,"c2");inf.readSpace();inf.readInt(1,min(min(r-a+1,c-b+1),min(r-u+1,c-v+1)),"d");inf.readEoln();}
    }
    inf.readEof();
}
