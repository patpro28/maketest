#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;
constexpr int KIND=4;
inline int generate(int argc,char**argv,int mode){
    int seed=argc>1?atoi(argv[1]):0;
    Random rnd(20261022ULL+KIND*100000ULL+mode*1000ULL+seed);
    int sizes[]={1,2,3,5,7,8,9,16,17,31};
    int n=mode==0?sizes[seed]:mode==1?rnd.uniform(1,25):mode==2?rnd.uniform(500,5000):int(N_MAX)-(seed==5);
    int q=mode==0?50:mode==1?80:mode==2?rnd.uniform(500,5000):int(Q_MAX);
    int pat=seed%6;
    auto word=[&](int len){
        string s(len,'a');string motif=pat==2?"ab":pat==3?"abacaba":"a";
        for(int i=0;i<len;++i){
            s[i]=pat==0?'a'+rnd.uniform(0,25):pat==5?'a'+rnd.uniform(0,1):motif[i%motif.size()];
        }
        if(pat==4 && len>1)s[len-1]='b';
        return s;
    };
    auto interval=[&](int len,int j){int l=rnd.uniform(1,len),r=rnd.uniform(1,len);if(l>r)swap(l,r);if(j%5==0){l=1;r=len;}if(j%5==1)l=r;if(j%5==2)l=1;if(j%5==3)r=len;return pair<int,int>{l,r};};
    if(KIND==0){int k=pat==0?1:pat==1?n:pat==2?min(2,n):pat==3?min(3,n):rnd.uniform(1,n);printf("%d %d\n%s\n",n,k,word(n).c_str());}
    if(KIND==2)printf("%d\n%s\n",n,word(n).c_str());
    if(KIND==1 || KIND==3){
        int m=pat==0?1:pat==1?n:pat==2?max(1,n/2):pat==3?min(int(N_MAX),n+1):pat==4?max(1,n-1):rnd.uniform(1,n);
        printf("%d %d\n",n,m);
        if(KIND==1){
            vector<int>a(n),b(m);
            for(int i=0;i<n;++i)a[i]=pat==0?(i%2?1000000000:-1000000000):pat==1?7:pat==2?i%7:pat==3?rnd.uniform(-1000,1000):pat==4?i:rnd.uniform(-2,2);
            for(int i=0;i<m;++i)b[i]=rnd.uniform(-1000,1000);
            if(m<=n && pat!=0){int start=rnd.uniform(0,n-m);for(int i=0;i<m;++i)b[i]=a[start+i]+10000;}
            if(pat==4 && m>1)b[m-1]++;
            for(int i=0;i<n;++i)printf("%d%c",a[i],i+1==n?'\n':' ');
            for(int i=0;i<m;++i)printf("%d%c",b[i],i+1==m?'\n':' ');
        }else{
            string s=word(n),p=word(m);
            if(m<=n){int start=rnd.uniform(0,n-m);p=s.substr(start,m);if(pat==2 || pat==4){int j=pat==2?0:m-1;p[j]=p[j]=='z'?'a':p[j]+1;}}
            printf("%s\n%s\n",s.c_str(),p.c_str());
        }
    }
    if(KIND==4 || KIND==8){
        string s=word(n);printf("%d %d\n%s\n",n,q,s.c_str());
        for(int j=0;j<q;++j){
            auto [l,r]=interval(n,j);
            if(KIND==4){auto [u,v]=interval(n,j+2);if(j%4==0){u=l;v=r;}if(j%4==1){u=rnd.uniform(1,n-(r-l));v=u+r-l;}printf("%d %d %d %d\n",l,r,u,v);}
            else{
                bool update=j%3==1;if(mode==0 && seed==8)update=false;if(mode==0 && seed==9)update=true;
                if(mode==3 && seed==1)update=false;
                if(update){int p=j%4==0?1:j%4==1?n:rnd.uniform(1,n);char c=j%4==2?s[p-1]:j%4==3?'z':'a'+rnd.uniform(0,25);s[p-1]=c;printf("1 %d %c\n",p,c);}
                else printf("2 %d %d\n",l,r);
            }
        }
    }
    if(KIND==5){
        int total=n;
        int count=mode==3?(pat==0?1:pat==1?2:pat==2?10:pat==3?n:pat==4?5:max(1,n/6)):min(n,pat==0?1:pat==1?2:pat==2?3:pat==3?n:5);
        printf("%d\n",count);vector<int>lens(count,total/count);for(int i=0;i<total%count;++i)++lens[i];
        if(pat==4 && count>1){int z=lens.back()-1;lens.back()=1;lens[0]+=z;}
        for(int i=0;i<count;++i){string s=word(lens[i]);if(pat==3)s=string(lens[i],i%2?'b':'a');if(pat==2 && lens[i]>=3)s.replace((lens[i]-3)/2,3,"xyz");printf("%s\n",s.c_str());}
    }
    if(KIND==6){
        int count=mode==3?(pat==0?1:pat==1?200000:pat==2?400:pat==3?17:pat==4?5:333):min(n,pat==0?1:pat==1?n:pat==2?3:5);
        int m=max(1,n/count);printf("%d %d\n",count,m);string base=word(m);
        for(int i=0;i<count;++i){
            string s=base;
            if(i%4==1)s=word(m);
            if(i%4==2 && m>1)s[rnd.uniform(0,m-1)]='z';
            int shift=rnd.uniform(0,m-1);rotate(s.begin(),s.begin()+shift,s.end());
            printf("%s\n",s.c_str());
        }
    }
    if(KIND==7){
        int r,c;
        if(mode==3){int rs[]={1000,1000,999,1,1000,733},cs[]={1000,997,1000,1000,1,997};r=rs[seed];c=cs[seed];}
        else{r=mode==0?min(n,10):mode==1?rnd.uniform(1,8):rnd.uniform(30,120);c=mode==0?(seed%2?r:max(1,r-1)):mode==1?rnd.uniform(1,9):rnd.uniform(30,150);}
        vector<string>a(r);for(int i=0;i<r;++i){a[i]=word(c);if(pat==2)for(int j=0;j<c;++j)a[i][j]='a'+(i+j)%3;}
        if(pat==3)for(int i=0;i<r;++i)for(int j=0;j<c;++j)a[i][j]='a'+((i==0 || j==0)?1:0);
        printf("%d %d %d\n",r,c,q);for(auto&s:a)printf("%s\n",s.c_str());
        for(int j=0;j<q;++j){
            int d=j%4==0?1:j%4==1?min(r,c):rnd.uniform(1,min(r,c));
            int x=rnd.uniform(1,r-d+1),y=rnd.uniform(1,c-d+1),u=rnd.uniform(1,r-d+1),v=rnd.uniform(1,c-d+1);
            if(j%5==0){u=x;v=y;}if(j%5==1){x=1;y=1;u=r-d+1;v=c-d+1;}
            printf("%d %d %d %d %d\n",x,y,u,v,d);
        }
    }
    if(KIND==9){
        string s=word(n);printf("%d %d\n%s\n",n,q,s.c_str());
        vector<int>label(n);iota(label.begin(),label.end(),1);
        if(pat==4)for(int i=n-1;i>0;--i)swap(label[i],label[rnd.uniform(0,i)]);
        for(int i=1;i<n;++i){int p=pat==0 || pat==1?i-1:pat==2?0:pat==3?(i-1)/2:pat==4?rnd.uniform(0,i-1):max(0,i-(i%7+1));int u=label[p],v=label[i];if(i%2)swap(u,v);printf("%d %d\n",u,v);}
        for(int j=0;j<q;++j){
            int u=rnd.uniform(1,n),v=rnd.uniform(1,n),x=rnd.uniform(1,n),y=rnd.uniform(1,n);
            if(j%7==0){x=u;y=v;}if(j%7==1){x=v;y=u;}if(j%7==2){v=u;y=x;}
            if(j%7==3){u=1;v=n;x=n;y=1;}if(j%7==4){x=u;y=u;}
            printf("%d %d %d %d\n",u,v,x,y);
        }
    }
    return 0;
}
