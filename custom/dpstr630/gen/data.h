#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rnd(20261106ULL+KIND*10000ULL+mode*100ULL+seed);
    const char *edges[]={"a","aa","ab","aba","abba","aaba","abca","bccb","aaaaaa","aabbaa","abacaba","bbabcbcab"};
    int n=mode==0?1:mode==1?rnd.uniform(1,12):mode==2?rnd.uniform(100,400):int(N_MAX);
    if(mode==3 && seed==5) n=1;
    std::string s(n,'a');
    int alphabet=mode==2 || (mode==3 && seed==0)?26:3;
    for(char &c:s) c=char('a'+rnd.uniform(0,alphabet-1));
    if(mode==0) s=edges[seed];
    if(mode==3) {
        if(seed==1) s.assign(n,'a');
        if(seed==2) for(int i=0;i<n;++i) s[i]=i<n/2?'a':'b';
        if(seed==3) for(int i=0;i<n;++i) s[i]="ab"[i%2];
        if(seed==4) {
            for(int i=0;i<n;++i) s[i]=char('a'+(std::min(i,n-1-i)%26));
        }
    }
    n=int(s.size());
    int k=mode==3?(seed==2?0:int(K_MAX)):seed%6;
    std::vector<long long> del(n),change(n);
    for(int i=0;i<n;++i) {
        del[i]=rnd.uniform(0LL,1000000000LL);change[i]=rnd.uniform(0LL,1000000000LL);
        if(mode==0) {
            del[i]=(seed+i)%4==0?0:(seed+i)%4==1?1:(seed+i)%4==2?7:1000000000LL;
            change[i]=(seed+2*i)%3==0?0:(seed+2*i)%3==1?1:1000000000LL;
        }
        if(mode==1) { del[i]=rnd.uniform(0LL,9LL);change[i]=rnd.uniform(0LL,9LL); }
        if(mode==3 && seed<=2) del[i]=change[i]=1000000000LL;
        if(mode==3 && seed==3) { if(KIND==631) del[i]=0;else change[i]=0; }
        if(mode==3 && seed==4 && KIND==650) del[i]=0;
    }
    // Equal endpoints do not justify keeping both when costs depend on positions.
    if(mode==0 && seed==5) {
        del={1,100,1000,1};change.assign(n,1000000000LL);
    }
    int q=mode==3?int(Q_MAX):mode==2?200:n*(n+1)/2;
    if(mode==3 && seed==5) q=1;
    if(KIND==600) std::printf("%d %d\n",n,q);
    else if(KIND==651) std::printf("%d %d\n",n,k);
    else std::printf("%d\n",n);
    std::printf("%s\n",s.c_str());
    if(KIND==600) {
        if(mode<=1) {
            for(int l=1;l<=n;++l) for(int r=l;r<=n;++r) std::printf("%d %d\n",l,r);
        } else for(int t=0;t<q;++t) {
            int l=rnd.uniform(1,n),r=rnd.uniform(l,n);
            if(t%7==0) { l=1;r=n; }
            if(t%7==1) r=l;
            if(t%7==2) { l=1;r=std::min(n,2); }
            if(t%7==3) { l=std::max(1,n-1);r=n; }
            std::printf("%d %d\n",l,r);
        }
    }
    if(KIND==631) for(int i=0;i<n;++i) std::printf("%lld%c",del[i],i+1==n?'\n':' ');
    if(KIND==650) for(int i=0;i<n;++i) std::printf("%lld %lld\n",del[i],change[i]);
    return 0;
}
