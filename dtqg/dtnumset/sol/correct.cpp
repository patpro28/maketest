#include <cstdio>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Big {
    static const uint32_t BASE=1000000000;
    vector<uint32_t> digit;
    Big(uint32_t value=0){if(value)digit.push_back(value);}
    Big& operator+=(const Big& other){
        size_t size=max(digit.size(),other.digit.size());digit.resize(size);uint64_t carry=0;
        for(size_t i=0;i<size;++i){uint64_t value=uint64_t(digit[i])+carry+(i<other.digit.size()?other.digit[i]:0);digit[i]=value%BASE;carry=value/BASE;}
        if(carry)digit.push_back(carry);return *this;
    }
    Big& operator-=(const Big& other){
        int64_t borrow=0;
        for(size_t i=0;i<digit.size();++i){int64_t value=int64_t(digit[i])-borrow-(i<other.digit.size()?other.digit[i]:0);borrow=value<0;if(borrow)value+=BASE;digit[i]=value;}
        assert(!borrow);while(!digit.empty() && !digit.back())digit.pop_back();return *this;
    }
    string str()const{
        if(digit.empty())return "0";string s=to_string(digit.back());
        for(int i=int(digit.size())-2;i>=0;--i){string t=to_string(digit[i]);s+=string(9-t.size(),'0')+t;}return s;
    }
};
int bounded_difference(const string& a,const string& b,int cap){
    // Return b-a if it is at most cap, otherwise cap+1.
    int borrow=0,result=0;int64_t place=1;
    for(int i=int(b.size())-1,j=int(a.size())-1;i>=0;--i,--j){
        int x=b[i]-'0'-(j>=0?a[j]-'0':0)-borrow;borrow=x<0;if(borrow)x+=10;
        if(x){if(place>cap || result+place*x>cap)return cap+1;result+=int(place*x);}
        place=min<int64_t>(cap+1,place*10);
    }
    assert(!borrow);return result;
}
string decrement(string s){int i=int(s.size())-1;while(s[i]=='0'){s[i]='9';--i;}--s[i];if(s.size()>1 && s[0]=='0')s.erase(s.begin());return s;}
int main(){
    if(FILE* input=fopen("NUMSET.INP","r")){fclose(input);freopen("NUMSET.INP","r",stdin);freopen("NUMSET.OUT","w",stdout);}
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s,A,B;cin>>s>>A>>B;int n=s.size();
    vector<array<int,10>> next(n+1);next[n].fill(n);
    for(int i=n-1;i>=0;--i){next[i]=next[i+1];next[i][s[i]-'0']=i;}
    if(max({s.size(),A.size(),B.size()})>1000){
        int width=bounded_difference(A,B,1000000);assert(width<=1000000);
        string value=A;vector<int> matched(1,0);
        auto append=[&](int begin){for(int i=begin;i<int(value.size());++i){int p=matched.back();matched.push_back(p>n?n+1:next[p][value[i]-'0']+1);}};
        append(0);int answer=0;
        for(int t=0;t<=width;++t){
            answer+=matched.back()<=n;if(t==width)break;
            int i=int(value.size())-1;while(i>=0 && value[i]=='9'){value[i]='0';--i;}
            if(i<0){value='1'+value;matched.assign(1,0);append(0);}
            else{++value[i];matched.resize(i+1);append(i);}
        }
        cout<<answer<<'\n';return 0;
    }
    int maximum=min<int>(n,B.size());vector<vector<Big>> dp(n+1);
    const Big zero;
    auto get=[&](int p,int length)->const Big&{return length<int(dp[p].size())?dp[p][length]:zero;};
    dp[n].push_back(Big(1));array<int,10> last;last.fill(n);
    for(int i=n-1;i>=0;--i){
        int size=min(maximum,n-i);dp[i].resize(size+1);dp[i][0]=Big(1);int j=last[s[i]-'0'];
        for(int length=1;length<=size;++length){
            dp[i][length]=get(i+1,length);dp[i][length]+=get(i+1,length-1);
            if(j<n)dp[i][length]-=get(j+1,length-1);
        }
        last[s[i]-'0']=i;
    }
    auto count_le=[&](const string& bound){
        Big answer(next[0][0]<n?1:0);int length=bound.size();
        for(int L=1;L<length && L<=n;++L)for(int d=1;d<=9;++d){int j=next[0][d];if(j<n)answer+=get(j+1,L-1);}
        if(length>n || bound=="0")return answer;
        int p=0;
        for(int i=0;i<length;++i){
            int digit=bound[i]-'0';
            for(int d=i?0:1;d<digit;++d){int j=next[p][d];if(j<n)answer+=get(j+1,length-i-1);}
            int j=next[p][digit];if(j==n)return answer;p=j+1;
        }
        answer+=Big(1);return answer;
    };
    Big answer=count_le(B);if(A!="0")answer-=count_le(decrement(A));cout<<answer.str()<<'\n';
}
