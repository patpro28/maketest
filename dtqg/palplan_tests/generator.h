#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "random.h"
using namespace std;
template<class T> void row(const vector<T>& a){
    for(int i=0;i<int(a.size());++i)cout<<(i?" ":"")<<a[i];cout<<'\n';
}
int main(int argc,char**argv){
    int seed=argc>1?atoi(argv[1]):0;
    Random rng(2026110300ULL+1000*TASK_ID+seed);
    if(TASK_ID<4){
        const vector<vector<string>> edge={
            {"a\n1\n1\n","a\n1\n2\n","abacdc\n2\n3 3\n","abba\n2\n3 1\n","aaaa\n2\n2 2\n","abc\n3\n1 1 1\n","baaaac\n1\n4\n","aaab\n2\n3 1\n"},
            {"a\n1\n1 1\n","a\n1\n2 1\n","bbbbccaa\n2\n4 1\n2 2\n","aaaa\n2\n2 1\n3 1\n","aaaaaa\n3\n1 1\n2 1\n3 1\n","abba\n1\n2 2\n","abc\n1\n1 3\n","aaab\n2\n1 1\n3 1\n"},
            {"a\n1 0\n1\n","a\n1 0\n2\n","aaab\n2 1\n1 3\n2 1\n","aaab\n2 1\n1 3\n1 2\n","aaaa\n2 2\n2 2\n1 2\n2 1\n","abba\n2 0\n2 2\n","abc\n3 3\n1 1 1\n3 2\n2 1\n3 1\n","aaaaaa\n3 0\n1 2 3\n"},
            {"a\n1\n1\n0\n","a\n1\n2\n7\n","aaaaa\n1\n2\n10 1 1 10 1\n","abba\n1\n3\n1 1 1 1\n","aaaa\n2\n2 2\n1000000000 1000000000 1000000000 1000000000\n","abc\n2\n1 1\n8 0 0\n","aaab\n2\n1 3\n1 1 1 1\n","abba\n1\n4\n0 0 0 0\n"}
        };
        if(seed<8){cout<<edge[TASK_ID][seed];return 0;}
        bool large=seed>=16;int sizes[]={200000,100000,100000,5000};
        int n=large?sizes[TASK_ID]:rng.uniform(1,16);
        string s(n,'a');
        if(seed%8==1 || seed%8==5)for(int j=0;j<n;++j)s[j]=char('a'+j%2);
        if(seed%8==2 || seed%8==6)s=rng.lower_string(n,'a','c');
        if(seed%8==3)for(int j=0;j<n;++j)s[j]=char('a'+j%26);
        if(seed%8==4)for(int j=0;j<n;++j)s[j]=char('a'+j/101%3);
        cout<<s<<'\n';
        if(TASK_ID==0){
            int k=large?(seed==16?200000:seed==17?1:seed==23?100000:1000):rng.uniform(1,5);
            vector<int> lengths(k,1);
            if(seed==17)lengths[0]=200000;
            else if(seed!=16 && seed!=23)for(int& x:lengths)x=rng.uniform(1,max(1,n/(2*k)));
            cout<<k<<'\n';row(lengths);
        }else if(TASK_ID==1){
            int d=large?3:rng.uniform(1,3);cout<<d<<'\n';
            vector<int> lengths;
            for(int i=0;i<d;++i){
                int length=large?(seed%2?2*i+1:1600+i):i+1;
                lengths.push_back(length);
                cout<<length<<' '<<(large?20:rng.uniform(1,2))<<'\n';
            }
        }else if(TASK_ID==2){
            int k=large?18:rng.uniform(1,5);vector<int> lengths(k),perm(k);iota(perm.begin(),perm.end(),1);rng.shuffle(perm.begin(),perm.end());
            for(int i=0;i<k;++i)lengths[i]=large?(seed%2?2*i+1:i+1):rng.uniform(1,5);
            if(seed==23)fill(lengths.begin(),lengths.end(),1);
            vector<pair<int,int>> edges;
            if(seed%8==2 || seed%8==3 || seed==23){
                for(int i=1;i<k;++i)edges.push_back({perm[i-1],perm[i]});
                if(seed%8==3 && k>1)edges.push_back({perm.back(),perm.front()});
            }
            cout<<k<<' '<<edges.size()<<'\n';row(lengths);for(auto [u,v]:edges)cout<<u<<' '<<v<<'\n';
        }else{
            int k=large?10:rng.uniform(1,4);vector<int> lengths(k),weights(n);
            for(int i=0;i<k;++i)lengths[i]=large?(seed==17?500:seed==18?2*i+1:i+1):rng.uniform(1,5);
            for(int i=0;i<n;++i)weights[i]=seed==16?1000000000:seed==18?(i%2?0:1000000000):seed==23?0:rng.uniform(0,1000);
            cout<<k<<'\n';row(lengths);row(weights);
        }
    }else{
        const vector<vector<string>> edge={
            {"1 0\n1\n","1 3\n2\n","3 4\n1\n2\n3\n","2 2\n1\n1\n","2 3\n2\n4\n","1 6\n2\n","3 1\n1000\n999\n998\n","3 10\n2\n3\n5\n"},
            {"1 0 0 0\n1 1\n","1 0 0 1\n1 1\n","3 3 3 2\n1 1\n2 2\n3 3\n","2 3 3 2\n1 1\n1 1\n","2 4 4 1\n1 1\n1 1\n","1 2 3 1\n1 1\n","3 1 1 0\n1 1\n2 2\n3 3\n","2 1 1 2\n1 1\n1 1\n"},
            {"1 0 0 0\n1 1\n","1 0 0 1\n1 1\n","3 3 3 2\n1 1\n1 1\n2 2\n","1 4 4 3\n1 1\n","2 3 3 2\n1 2\n2 1\n","2 4 4 2\n2 2\n2 2\n","2 1 2 1\n1 2\n1 2\n","2 2 1 1\n1 2\n1 2\n"},
            {"1 0 0\n1 1\n","1 1 1\n1 1\n","1 3 3\n1 1\n","1 5 5\n1 1\n","1 6 6\n1 1\n","2 3 3\n1 1\n1 1\n","2 3 3\n1 2\n2 1\n","1 2 1\n1 1\n"}
        };
        if(seed<8){cout<<edge[TASK_ID-4][seed];return 0;}
        bool large=seed>=16;
        if(TASK_ID==4){
            int m=large?30:rng.uniform(1,6),A=large?200000:rng.uniform(0,35);
            if(seed==18)--A;
            cout<<m<<' '<<A<<'\n';
            for(int i=0;i<m;++i)cout<<(seed==16?1:seed==17?1000:seed==18?2:rng.uniform(1,1000))<<'\n';
        }else if(TASK_ID==5){
            int m=large?20:rng.uniform(1,5),A=large?150:rng.uniform(0,15),B=large?150:rng.uniform(0,15),K=large?(seed==17?20:10):rng.uniform(0,m);
            cout<<m<<' '<<A<<' '<<B<<' '<<K<<'\n';
            for(int i=0;i<m;++i){int a=seed<=17?1:rng.uniform(1,5),b=seed<=17?1:rng.uniform(1,5);cout<<a<<' '<<b<<'\n';}
        }else{
            int m=large?8:rng.uniform(1,5);vector<int>a(m),b(m);long long A=0,B=0,C=0;
            for(int i=0;i<m;++i){
                a[i]=large && seed<=17?seed-15:rng.uniform(1,2);b[i]=large && seed<=17?seed-15:rng.uniform(1,2);
                long long x=large?rng.uniform(0LL,10000000000000000LL):rng.uniform(0LL,5LL);
                if(TASK_ID==7){x=0;int bits=large?55:3;bool previous=false;for(int j=0;j<bits;++j){bool take=!previous && rng.uniform_bool();if(take)x|=1LL<<j;previous=take;}}
                A+=a[i]*x;B+=b[i]*x;C+=x;
            }
            if(large && seed<=17){A=B=1000000000000000000LL;C=seed==16?A:A/2;}
            if(large && seed==19){A=1000000000000000000LL;B=A-1;C=A/2;}
            if(large && seed==22){A=B=C=1LL<<59;fill(a.begin(),a.end(),1);fill(b.begin(),b.end(),1);}
            if(large && seed==23){m=1;a={1};b={1};A=B=1000000000000000000LL;C=A;}
            cout<<m<<' '<<A<<' '<<B;if(TASK_ID==6)cout<<' '<<C;cout<<'\n';
            for(int i=0;i<m;++i)cout<<a[i]<<' '<<b[i]<<'\n';
        }
    }
}
