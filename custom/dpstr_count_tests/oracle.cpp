#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD=1000000007;
int main(int argc,char **argv) {
    if(argc!=2) return 1;
    int code=atoi(argv[1]),n,m=0,k=0,L=1,R=0;
    string a,b,marked;
    cin>>n;
    if(code>=3) cin>>m;
    if(code==31 || code==50 || code==51) cin>>k;
    if(code==52) cin>>L>>R;
    cin>>a;
    if(code>=3) cin>>b;
    if(code==31) cin>>marked;
    if(code<3) {
        long long answer=0,left=0,right=0;
        if(code==0) {
            for(char c:a) right+=(c=='b');
            for(char c:a) { if(c=='a') answer+=right; if(c=='b') --right; }
        } else {
            char last=code==1?'c':'a';
            for(char c:a) right+=(c==last);
            for(char c:a) {
                if(c==last) --right;
                if(c=='b') answer+=left*right;
                if(c=='a') ++left;
            }
        }
        cout<<answer<<'\n'; return 0;
    }
    if(code==50) {
        vector<vector<int>> prev(k+1,vector<int>(n+1)),cur=prev;
        if(k) for(int i=1;i<=n;++i) prev[1][i]=(a[i-1]==b[0]);
        for(int j=2;j<=m;++j) {
            vector<int> prefix(k+1);
            for(int i=1;i<=n;++i) {
                if(i>=3) for(int t=0;t<=k;++t) prefix[t]=(prefix[t]+prev[t][i-2])%MOD;
                for(int t=0;t<=k;++t) {
                    cur[t][i]=0;
                    if(a[i-1]==b[j-1]) {
                        int value=prev[t][i-1];
                        if(t) value=(value+prefix[t-1])%MOD;
                        cur[t][i]=value;
                    }
                }
            }
            prev.swap(cur);
        }
        int answer=0;
        for(int i=1;i<=n;++i) answer=(answer+prev[k][i])%MOD;
        cout<<answer<<'\n'; return 0;
    }
    if(code==31 || code==51) {
        vector<vector<int>> prev(k+1,vector<int>(n+1)),cur=prev;
        fill(prev[0].begin(),prev[0].end(),1);
        for(int j=1;j<=m;++j) {
            for(int t=0;t<=k;++t) cur[t][0]=0;
            for(int i=1;i<=n;++i) {
                int extra=code==31?marked[i-1]-'0':(a[i-1]!=b[j-1]);
                bool allowed=(code==51 || a[i-1]==b[j-1]);
                for(int t=0;t<=k;++t) {
                    int value=cur[t][i-1];
                    if(allowed && t>=extra) value=(value+prev[t-extra][i-1])%MOD;
                    cur[t][i]=value;
                }
            }
            prev.swap(cur);
        }
        int answer=prev[k][n];
        if(code==51) for(int t=0;t<k;++t) answer=(answer+prev[t][n])%MOD;
        cout<<answer<<'\n'; return 0;
    }
    vector<int> prev(n+1,1),cur(n+1);
    if(code==30) for(int i=1;i<=n;++i) prev[i]=int(1LL*prev[i-1]*(a[i-1]=='?'?26:1)%MOD);
    for(int j=1;j<=m;++j) {
        cur[0]=0;
        for(int i=1;i<=n;++i) {
            bool match=(a[i-1]==b[j-1] || (code==30 && a[i-1]=='?'));
            long long take=prev[i-1];
            if(code==32 || code==52) {
                int low=code==32?2:L,high=code==32?n:R;
                if(j==1) take=1;
                else {
                    int hi=max(0,i-low),lo=max(0,i-high-1);
                    take=(prev[hi]-prev[lo]+MOD)%MOD;
                }
            }
            long long skip=1LL*cur[i-1]*(code==30 && a[i-1]=='?'?26:1);
            cur[i]=int((skip+(match?take:0))%MOD);
        }
        prev.swap(cur);
    }
    cout<<prev[n]<<'\n';
}
