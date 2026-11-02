#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int length_value(const string& token,int cap){
    int value=0;
    for(char c:token){value=min(cap,value*10+c-'0');}
    return value;
}

int main(){
    if(FILE* file=fopen("PALINCUT.INP","r")){
        fclose(file);
        if(!freopen("PALINCUT.INP","r",stdin))return 1;
        if(!freopen("PALINCUT.OUT","w",stdout))return 1;
    }
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s;cin>>s;int n=int(s.size()),t;cin>>t;
    vector<vector<int>>query(t);vector<bool>possible(t,true);vector<int>needed;
    for(int q=0;q<t;++q){
        int k;cin>>k;query[q].resize(k);int sum=0;
        for(int& length:query[q]){string token;cin>>token;length=length_value(token,n+1);sum+=length;}
        if(sum>n)possible[q]=false;
        else if(k>1)for(int length:query[q])needed.push_back(length);
    }
    vector<int>odd(n),even(n);int max_odd=0,max_even=0;
    for(int i=0,l=0,r=-1;i<n;++i){
        int radius=i>r?1:min(odd[l+r-i],r-i+1);
        while(i-radius>=0 && i+radius<n && s[i-radius]==s[i+radius])++radius;
        odd[i]=radius;max_odd=max(max_odd,2*radius-1);
        if(i+radius-1>r){l=i-radius+1;r=i+radius-1;}
    }
    for(int i=0,l=0,r=-1;i<n;++i){
        int radius=i>r?0:min(even[l+r-i+1],r-i+1);
        while(i-radius-1>=0 && i+radius<n && s[i-radius-1]==s[i+radius])++radius;
        even[i]=radius;max_even=max(max_even,2*radius);
        if(i+radius-1>r){l=i-radius;r=i+radius-1;}
    }
    sort(needed.begin(),needed.end());needed.erase(unique(needed.begin(),needed.end()),needed.end());
    const uint16_t inf=uint16_t(n+1);vector<int>id(n+1,-1);
    vector<vector<uint16_t>>next(needed.size(),vector<uint16_t>(n+1,inf));
    for(int row=0;row<int(needed.size());++row){
        int length=needed[row];id[length]=row;
        for(int p=n-1;p>=0;--p){
            next[row][p]=next[row][p+1];
            if(p+length<=n){
                int center=p+length/2;
                bool palindrome=length%2?odd[center]>=length/2+1:even[center]>=length/2;
                if(palindrome)next[row][p]=uint16_t(p+length);
            }
        }
    }
    for(int q=0;q<t;++q){
        if(!possible[q]){cout<<"NO\n";continue;}
        const auto& lengths=query[q];int k=int(lengths.size());
        if(k==1){int length=lengths[0];cout<<((length%2?max_odd:max_even)>=length?"YES\n":"NO\n");continue;}
        vector<uint16_t>dp(1<<k,inf);dp[0]=0;
        for(int mask=0;mask<(1<<k);++mask)if(dp[mask]!=inf){
            for(int i=0;i<k;++i)if(!(mask>>i&1)){
                int to=mask|(1<<i);dp[to]=min(dp[to],next[id[lengths[i]]][dp[mask]]);
            }
        }
        cout<<(dp.back()!=inf?"YES\n":"NO\n");
    }
}
