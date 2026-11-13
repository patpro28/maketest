#include <bits/stdc++.h>
using namespace std;
using i128=__int128_t;
i128 memo[19][20][20][19];
bool seen[19][20][20][19];
int n;
i128 countWays(int left,int a,int b,int hi) {
    if(a+b<=hi)return 0;
    if(left==0)return 1;
    i128 &res=memo[left][a][b][hi];
    if(seen[left][a][b][hi])return res;
    seen[left][a][b][hi]=true;
    for(int v=1; v<=n; v++)res+=countWays(left-1,min(a,v),v<a?a:min(b,v),max(hi,v));
    return res;
}
void print128(i128 x) {
    if(x>=10)print128(x/10);
    cout<<char('0'+x%10);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string ts;
    cin>>n>>ts;
    i128 t=0;
    for(char c:ts)t=t*10+c-'0';
    vector<int>A(n);
    for(int &v:A)cin>>v;
    print128(countWays(n,n+1,n+1,0));
    cout<<'\n';
    int a=n+1,b=n+1,hi=0;
    for(int i=0; i<n; i++)for(int v=1; v<=n; v++) {
        int aa=min(a,v),bb=v<a?a:min(b,v),hh=max(hi,v);
        i128 ways=countWays(n-i-1,aa,bb,hh);
        if(t>ways)t-=ways;
        else {
            cout<<v<<(i+1==n?'\n':' ');
            a=aa;
            b=bb;
            hi=hh;
            break;
        }
    }
    i128 rank=1;
    a=b=n+1;
    hi=0;
    for(int i=0; i<n; i++) {
        for(int v=1; v<A[i]; v++)rank+=countWays(n-i-1,min(a,v),v<a?a:min(b,v),max(hi,v));
        b=A[i]<a?a:min(b,A[i]);
        a=min(a,A[i]);
        hi=max(hi,A[i]);
    }
    print128(rank);
    cout<<'\n';
}
