#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rnd(20261104ULL+KIND*10000ULL+mode*100ULL+seed);
    const char *aa[]={"a","ab","abc","aba","aaa","aaaaaa","abababa","aabbaa","cba","abcabc","abacaba","cabaaabc"};
    const char *bb[]={"a","b","abc","aa","a","aaa","aba","ab","abc","abc","aba","aab"};
    int n=mode==0?1:mode==1?rnd.uniform(1,12):mode==2?rnd.uniform(100,400):int(N_MAX);
    int m=mode==0?1:mode==1?rnd.uniform(1,6):mode==2?rnd.uniform(10,100):int(N_MAX);
    if(mode==3 && seed==5) n=1;
    if(mode==3 && seed==1) m=std::max(1,n/2);
    if(mode==3 && seed==4) m=std::max(1,n/3);
    std::string a(n,'a'),b(m,'a');
    int alphabet=mode==2 && seed%2==0?26:3;
    for(char &c:a) c=char('a'+rnd.uniform(0,alphabet-1));
    for(char &c:b) c=char('a'+rnd.uniform(0,alphabet-1));
    int k=mode==3?int(K_MAX):seed%6;
    if(mode==0) { a=aa[seed];b=bb[seed]; }
    if(mode==3) {
        if(seed==1) { a.assign(n,'a');b.assign(m,'a'); }
        if(seed==2) { a.assign(n,'a');b.assign(m,'b');k=0; }
        if(seed==3) {
            for(int i=0;i<n;++i) a[i]="abc"[i%3];
            for(int j=0;j<m;++j) b[j]="abc"[j%3];
        }
        if(seed==4) {
            for(int i=0;i<n;++i) a[i]="ab"[i%2];
            b.assign(m,'a');
        }
        if(KIND<3) {
            if(seed==0) for(int i=0;i<n;++i) a[i]="abc"[i%3];
            if(seed==1) {
                for(int i=0;i<n;++i)
                    a[i]=KIND==0?(i<n/2?'a':'b'):KIND==1?(i<n/3?'a':i<2*n/3?'b':'c'):(i<n/3?'a':i<2*n/3?'b':'a');
            }
        }
    }
    if(KIND==30) {
        if(mode==0) {
            const char *wc[]={"?","??","a?c","?a?","???","a??a??","?ab?aba","a?b?aa","c?a","?bc?bc","ab?ca?a","c??aa?bc"};
            a=wc[seed];
        } else {
            for(char &c:a) if(rnd.uniform(0,3)==0) c='?';
            if(mode==3 && seed==1) a.assign(n,'?');
            if(mode==3 && seed==2) { a.assign(n,'?');b.assign(m,'z'); }
        }
    }
    n=int(a.size());m=int(b.size());
    std::string marked(n,'0');
    for(int i=0;i<n;++i) marked[i]=char('0'+rnd.uniform(0,1));
    if(mode==3 && seed==1) marked.assign(n,'0');
    if(mode==3 && seed==2) marked.assign(n,'1');
    if(mode==0 && seed==3) marked="101";
    if(mode==0 && seed==4) { marked.assign(n,'1');k=0; }
    if(mode==0 && seed==5) { marked.assign(n,'0');k=0; }
    if(mode==3 && seed==1 && KIND==31) for(int i=0;i<n;++i) marked[i]=char('0'+i%2);
    int low=1,high=n;
    if(mode==0) { low=seed%3+1;low=std::min(low,n);high=std::min(n,low+seed%4); }
    if(mode==1 || mode==2) { low=rnd.uniform(1,n);high=rnd.uniform(low,n); }
    if(mode==3 && seed==3) low=high=1;
    if(mode==3 && seed==4) { low=2;high=3; }
    if(KIND<3) std::printf("%d\n",n);
    else if(KIND==31 || KIND==50 || KIND==51) std::printf("%d %d %d\n",n,m,k);
    else if(KIND==52) std::printf("%d %d %d %d\n",n,m,low,high);
    else std::printf("%d %d\n",n,m);
    std::printf("%s\n",a.c_str());
    if(KIND>=3) std::printf("%s\n",b.c_str());
    if(KIND==31) std::printf("%s\n",marked.c_str());
    return 0;
}
