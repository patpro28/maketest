#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "random.h"
inline std::string repeated(const std::string& word,int n){std::string s;while(int(s.size())<n)s+=word;s.resize(n);return s;}
inline int generate(int argc,char**argv,int group){
    int seed=argc>1?std::atoi(argv[1]):0;Random rng(2026110200ULL+1000*group+seed);
    int n=10000,t=200;std::string s;
    if(group==1){const int sizes[]={1,2,3,13,26,199,200,9999,10000,10000};n=sizes[seed];}
    if(group==2){const int sizes[]={1,2,6,8,13,26,50,100,199,200};n=sizes[seed];t=3;}
    if(group==3 && seed==6)n=201;
    if(group==3 && seed==7)n=200;
    if(group==3 && (seed==4 || seed==18))n=9999;
    s=rng.lower_string(n,'a',group==1?'d':group==2?'c':'z');
    if(group==1){
        if(seed==0 || seed==7)s=std::string(n,'a');
        if(seed==1)s="ab";
        if(seed==2)s="aba";
        if(seed==3)s="asaaabbrcaacw";
        if(seed==4 || seed==9)s=repeated("abcdefghijklmnopqrstuvwxyz",n);
        if(seed==5 || seed==8)s=repeated("ab",n);
    }
    if(group==2){
        if(seed==0)s="a";if(seed==1)s="ab";if(seed==2)s="ababax";
        if(seed==3)s="bbbbccaa";if(seed==4)s="asaaabbrcaacw";
        if(seed==5)s="abcdefghijklmnopqrstuvwxyz";
        if(seed==7)s=std::string(n,'a');
        if(seed==8)s=repeated("ab",n);
        if(seed==9)s=repeated("abba",n);
    }
    if(group==3){
        if(seed==0 || seed==17 || seed==18)s=std::string(n,'a');
        if(seed==1)s=repeated("ab",n);
        if(seed==3)s=repeated("aab",n);
        if(seed==4){std::string half=rng.lower_string(n/2,'a','f');s=half+'z'+std::string(half.rbegin(),half.rend());}
        if(seed==5){s=std::string(n,'a');for(int i=99;i<n;i+=100)s[i]=char('b'+i%20);}
        if(seed==6 || seed==13)s=rng.lower_string(n,'a','b');
        if(seed==7)s=repeated("asaaabbrcaacw",n);
        if(seed==8)s=repeated("ababax",n);
        if(seed==9){s.clear();for(int i=0;i<n/20;++i)s+=std::string(20,char('a'+i%26));}
        if(seed==10)s=repeated("abcdefghijklmnopqrstuvwxyz",n);
        if(seed==11)s=repeated("abba",n);
        if(seed==12)s=repeated("ab",n-2)+"aa";
        if(seed==14){std::string half=rng.lower_string(n/2,'a','d');s=half+half;}
        if(seed==15)s=std::string(3333,'a')+std::string(3334,'b')+std::string(3333,'a');
    }
    std::vector<int>planted;
    if(group==3 && seed==19){
        s.clear();
        for(int i=0;i<13;++i){int length=301+i;planted.push_back(length);std::string half=rng.lower_string(length/2,'a','t');s+=half;if(length%2)s+='u';s+=std::string(half.rbegin(),half.rend());s+="xyz";}
        s+=rng.lower_string(n-int(s.size()),'a','z');
    }
    std::cout<<s<<'\n'<<t<<'\n';
    for(int q=0;q<t;++q){
        std::vector<int>lengths;
        if(group==1){
            int length=q==0?1:q==1?n:q==2?n+1:q==3?1000000000:rng.uniform(1,n+2);
            lengths={length};
        }else{
            int k=q%4==0?13:rng.uniform(2,13);lengths.resize(k);
            for(int& length:lengths)length=rng.uniform(1,std::max(1,n/(k+1)));
            if(q%7==1)lengths.assign(k,1);
            if(q%7==2)lengths.assign(k,2);
            if(q%7==3)for(int& length:lengths)length=2*rng.uniform(0,std::max(0,n/(2*k)-1))+1;
            if(q%7==4){std::iota(lengths.begin(),lengths.end(),1);}
            if(q%7==5)lengths[0]=n;
        }
        if(group==2){
            if(seed==2)lengths=q==0?std::vector<int>{3,3}:q==1?std::vector<int>{3,1}:std::vector<int>{1,1,1,1,1,1};
            if(seed==3)lengths=q==0?std::vector<int>{4,4}:q==1?std::vector<int>{4,2,2}:std::vector<int>{1,2,2,3};
            if(seed==4)lengths=q==0?std::vector<int>{2,3,4}:q==1?std::vector<int>{2,2,2,2}:std::vector<int>{3,2,4};
        }
        if(group==3 && seed==17){
            lengths.clear();
            if(q<199)for(int column=0;column<10;++column)lengths.push_back(column*199+(column%2?199-q:q+1));
            else for(int i=1;i<=13;++i)lengths.push_back(i);
        }
        if(group==3 && seed==18){lengths.resize(13);for(int i=0;i<13;++i)lengths[i]=700+i;if(q%2)lengths.back()=n-std::accumulate(lengths.begin(),lengths.end()-1,0)+(q%4==1?0:1);}
        if(group==3 && seed==19 && q%5==0){lengths=planted;rng.shuffle(lengths.begin(),lengths.end());}
        if(q==t-2 && !(group==3 && seed==17)){std::cout<<"1 100000000000000000000000000000000000000000000000000000000000000000000000000000000\n";}
        else{
            std::cout<<lengths.size();for(int x:lengths)std::cout<<' '<<x;std::cout<<'\n';
        }
    }
    return 0;
}
