#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "random.h"
#include "../params.h"
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261101ULL+KIND*10000ULL+mode*100ULL+seed);
    const int small[]={1,2,3,4,5,6,7,8,9,5,6,8};
    int n=mode==0 ? small[seed] : mode==1 ? rnd.uniform(1,8) : mode==2 ? rnd.uniform(30,150) : int(N_MAX);
    int m=mode==0 ? small[(seed+3)%12] : mode==1 ? rnd.uniform(1,8) : mode==2 ? rnd.uniform(30,150) : int(N_MAX);
    int p=mode==0 ? small[(seed+1)%12] : mode==1 ? rnd.uniform(1,8) : mode==2 ? rnd.uniform(30,150) : int(N_MAX);
    if(mode==3 && seed==5) n=1;
    int pattern=mode==1 ? 0 : seed;
    std::string a(n,'a'),b(m,'a'),d(p,'a');
    auto fill=[&](std::string &s,int shift) {
        for(int i=0;i<(int)s.size();++i) {
            s[i]=char('a'+rnd.uniform(0,mode==2 && seed%2==0 ? 25 : 3));
            if(pattern==1) s[i]='a';
            if(pattern==2) s[i]=char('a'+shift);
            if(pattern==3) s[i]="ab"[(i+shift)%2];
            if(pattern==4) s[i]="abc"[(i/3+shift)%3];
            if(pattern==5) s[i]="abcdefghijklmnopqrstuvwxyz"[(i+shift)%26];
            if(pattern==6) s[i]="abcabcx"[(i+shift)%7];
        }
    };
    fill(a,0);fill(b,1);fill(d,2);
    char target=seed%3==0 ? 'z' : seed%3==1 ? 'a' : 'b';
    int k=mode==3 ? (seed==2 ? 0 : 5) : seed%6;
    long long penalty=seed%3==0 ? 0 : seed%3==1 ? 1 : 1000000000LL;
    if(mode==0) {
        const char *aa[]={"a","a","abcde","ababa","aaaa","axbc","xabc","abxcd","abc","xabcy","aaab","abbacaba"};
        const char *bb[]={"a","b","abzde","babab","aaa","abcd","abcx","abycd","cba","abcxy","baaa","cabbacab"};
        a=aa[seed];b=bb[seed]; d=seed%2 ? "abc" : "a";
        if(seed==5 || seed==6 || seed==9) target='x';
        if(seed==0) target='a';
        if(KIND==250 && seed==2) { a="abx";b="aby";d="xaby"; }
        if(KIND==250 && seed==3) { a="xabcy";b="zabc";d="qabcw"; }
        if(KIND==231 && seed==6) { a="abxcd";b="abycd";k=1; }
        if(KIND==252 && seed==7) { a="aabaa";b="aacaa";k=1;penalty=1; }
        if(KIND==251 && seed==8) { a="ab";b="ab"; }
        if(KIND==251 && seed==9) { a="ab";b="ba"; }
    }
    if(mode==3 && KIND==202 && seed==3) { a[0]='z'; target='z'; }
    n=a.size();m=b.size();p=d.size();
    if(KIND==250) std::printf("%d %d %d\n",n,m,p);
    else if(KIND==231) std::printf("%d %d %d\n",n,m,k);
    else if(KIND==252) std::printf("%d %d %d %lld\n",n,m,k,penalty);
    else std::printf("%d %d\n",n,m);
    std::printf("%s\n%s\n",a.c_str(),b.c_str());
    if(KIND==250) std::printf("%s\n",d.c_str());
    if(KIND==202) std::printf("%c\n",target);
    if(KIND==230 || KIND==252) {
        for(int c=0;c<26;++c) {
            long long w=rnd.uniform(-1000000000LL,1000000000LL);
            if(pattern==1) w=1000000000LL;
            if(pattern==2) w=-1000000000LL;
            if(pattern==3) w=c%2 ? -1 : 5;
            if(pattern==4) w=0;
            if(mode==0 && seed==7) w=c==0 ? 5 : -20;
            std::printf("%lld%c",w,c==25 ? '\n' : ' ');
        }
    }
    return 0;
}
