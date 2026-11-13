#pragma once
#include <algorithm>
#include <string>
#include <vector>
struct Palindrome {
    int n;
    std::vector<int> odd, even;
    explicit Palindrome(const std::string& s):n(s.size()),odd(n),even(n){
        for(int i=0,l=0,r=-1;i<n;++i){
            int k=i>r?1:std::min(odd[l+r-i],r-i+1);
            while(i-k>=0 && i+k<n && s[i-k]==s[i+k])++k;
            odd[i]=k--;
            if(i+k>r){l=i-k;r=i+k;}
        }
        for(int i=0,l=0,r=-1;i<n;++i){
            int k=i>r?0:std::min(even[l+r-i+1],r-i+1);
            while(i-k-1>=0 && i+k<n && s[i-k-1]==s[i+k])++k;
            even[i]=k--;
            if(i+k>r){l=i-k-1;r=i+k;}
        }
    }
    bool has(int p,int length)const{
        if(p<0 || length<1 || p+length>n)return false;
        int c=p+length/2;
        return length%2?odd[c]>=length/2+1:even[c]>=length/2;
    }
    std::vector<int> next(int length)const{
        std::vector<int> f(n+1,n+1);
        for(int p=n-1;p>=0;--p)f[p]=has(p,length)?p+length:f[p+1];
        return f;
    }
};
