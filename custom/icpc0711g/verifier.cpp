#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,1000000);
    inf.readSpace();
    int k=inf.readInt(1,n);
    inf.readEoln();
    vector<string>s(n);
    int total=0;
    for(auto &x:s) {
        x=inf.readToken();
        inf.readEoln();
        total+=x.size();
        ensuref(total<=1000000,"total length");
    }
    sort(s.begin(),s.end());
    for(int i=1; i<n; i++)ensuref(s[i].compare(0,s[i-1].size(),s[i-1])!=0,"prefix or duplicate");
    string x=inf.readToken();
    inf.readEoln();
    ensuref(x.size()<=size_t(total),"X too long");
    size_t pos=0;
    set<int>used;
    for(int i=0; i<k; i++) {
        ensuref(pos<x.size(),"too few components");
        auto it=lower_bound(s.begin(),s.end(),pos,[&](const string &z,size_t p) {return z.compare(0,z.size(),x,p,min(z.size(),x.size()-p))<0;});
        ensuref(it!=s.end()&&x.compare(pos,it->size(),*it)==0,"unknown component");
        ensuref(used.insert(it-s.begin()).second,"repeated component");
        pos+=it->size();
    }
    ensuref(pos==x.size(),"extra components");
    inf.readEof();
}
