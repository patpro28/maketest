#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"
constexpr int KIND = 123;
inline int generate(int argc, char **argv, int mode) {
    int seed=argc>1?std::atoi(argv[1]):0;
    Random rnd(20261027ULL+KIND*10000ULL+mode*100ULL+seed);
    const int sizes[]={1,2,3,5,8,9,17,31,32,33,65,7};
    int n=mode==0?sizes[seed]:mode==1?rnd.uniform(1,30):mode==2?rnd.uniform(1000,20000):int(N_MAX)-(seed==5);
    int q=mode==0?60:mode==1?200:mode==2?rnd.uniform(1000,20000):int(Q_MAX);
    int pattern=mode==0?seed:seed%6;
    if (KIND==123) {
        int m=seed==6?1:n;
        int w=seed%5==0?1:seed%5==1?std::max(1,n/2):seed%5==2?std::min(n,2):seed%5==3?n:rnd.uniform(1,n);
        if (mode==3 && seed==1) w=n/2;
        if (mode==3 && seed==2) w=n/2;
        std::printf("%d %d %d\n",n,m,w);
        for (int i=0;i<n;++i) {
            int x=rnd.uniform(1,m);
            if (pattern==1 || (mode==3 && seed==1)) x=i%2?m:1;
            if (pattern==2) x=i%m+1;
            if (pattern==3) x=m;
            if (pattern==4) x=std::max(1,m-i%m);
            if (pattern==5) x=i%3==0?1:m;
            std::printf("%d%c",x,i+1==n?'\n':' ');
        }
        return 0;
    }
    const int low=KIND==113 || KIND==115?-1000000000:0;
    const int high=KIND==104?1048575:1000000000;
    auto value=[&]() -> long long {
        if (rnd.uniform(0,2)==0) return rnd.uniform(low,high);
        if (KIND==104) return rnd.uniform(0,1)?1<<rnd.uniform(0,19):rnd.uniform(0,1)?0:1048575;
        const int specials[]={-1000000000,-7,-1,0,1,2,3,6,7,1000000000};
        int x;do{x=specials[rnd.uniform(0,9)];}while(x<low||x>high);return x;
    };
    std::vector<long long> a(n),letters(n),other(n);
    long long total=0;int distinct=0;
    for(int i=0;i<n;++i) {
        long long x=value();
        if(pattern==1)x=low;
        if(pattern==2)x=high;
        if(pattern==3)x=std::clamp(7,low,high);
        if(pattern==4||pattern==11)x=i%2?low:high;
        if(pattern==5)x=std::clamp(i%7,low,high);
        if(pattern==6)x=std::clamp(1,low,high);
        if(pattern==7)x=std::clamp(n-i,low,high);
        letters[i]=pattern==1?0:pattern==2?i%26:pattern==3?25:rnd.uniform(0,25);
        other[i]=i%3==0?rnd.uniform(0,25):letters[i];
        if(pattern==1)other[i]=letters[i];
        if(pattern==2)other[i]=25-letters[i];
        if(pattern==3)other[i]=letters[i];
        if(mode==3 && seed==1) {
            if(KIND==103)x=i+1==n?2:1;
            if(KIND==104)x=i+1==n?524287:1048575;
            if(KIND==113)x=i+2==n?1:0;
            if(KIND==115)x=i+1==n?0:-1000000000;
            if(KIND==124)x=i+1==n?1000000000:0;
            if(KIND==125){x=i+1==n?1000000000:0;letters[i]=i+1==n?25:0;}
            if(KIND==114){letters[i]=0;other[i]=i+1==n?1:0;}
        }
        a[i]=x;total+=x;distinct+=x>0;
    }
    std::printf("%d %d\n",n,q);
    if(KIND==114||KIND==125) {
        for(int i=0;i<n;++i)std::putchar('a'+int(letters[i]));std::putchar('\n');
        if(KIND==114){for(int i=0;i<n;++i)std::putchar('a'+int(other[i]));std::putchar('\n');}
    }
    if(KIND!=114)for(int i=0;i<n;++i)std::printf("%lld%c",a[i],i+1==n?'\n':' ');
    const long long big=1000000000000000000LL;
    for(int j=0;j<q;++j) {
        int pos=rnd.uniform(0,n-1);
        if(j%7==0)pos=0;if(j%7==1)pos=n-1;if(j%7==2)pos=n/2;
        bool update=j%3==1;
        if(mode==2)update=rnd.uniform(0,99)<(seed%3==0?10:seed%3==1?50:90);
        if(mode==0&&seed==9)update=false;
        if(mode==0&&seed==10)update=true;
        if(mode==3&&seed==1)update=false;
        if(mode==3&&seed==5)update=j+1!=q;
        if(update) {
            if(KIND==103||KIND==124) {
                int type=rnd.uniform(1,2);if(a[pos]==0)type=1;
                distinct-=a[pos]>0;a[pos]+=type==1?1:-1;distinct+=a[pos]>0;
                std::printf("%d %d\n",type,pos+1);continue;
            }
            if(KIND==114) {
                int which=rnd.uniform(1,2),c=rnd.uniform(0,25);
                if(j%4==0)c=int(which==1?other[pos]:letters[pos]);
                if(which==1)letters[pos]=c;else other[pos]=c;
                std::printf("1 %d %d %c\n",which,pos+1,'a'+c);continue;
            }
            long long x=value();
            if(j%5==1)x=a[pos];if(j%5==2)x=low;if(j%5==3)x=high;
            total+=x-a[pos];a[pos]=x;
            if(KIND==125){letters[pos]=rnd.uniform(0,25);std::printf("1 %d %c %lld\n",pos+1,'a'+int(letters[pos]),x);}
            else std::printf("1 %d %lld\n",pos+1,x);
            continue;
        }
        if(KIND==103)std::printf("3\n");
        if(KIND==104) {
            int mask=j%4==0?1048575:j%4==1?1<<rnd.uniform(0,19):j%4==2?3:rnd.uniform(1,1048575);
            if(mode==3&&seed==1)mask=1<<19;
            std::printf("2 %d\n",mask);
        }
        if(KIND==113||KIND==114||KIND==115)std::printf("2\n");
        if(KIND==124) {
            int k=j%4==0?1:j%4==1?n:j%4==2?std::max(1,distinct):std::min(n,distinct+1);
            if(mode==3&&seed==1)k=1;
            std::printf("3 %d\n",k);
        }
        if(KIND==125) {
            long long k=j%7==0?1:j%7==1?std::max(1LL,total):j%7==2?total+1:j%7==3?big:j%7==4?2147483648LL:j%7==5?std::max(1LL,a[pos]):rnd.uniform(1LL,std::max(1LL,total));
            if(mode==3&&seed==1)k=1000000000;
            std::printf("2 %lld\n",k);
        }
    }
    return 0;
}
