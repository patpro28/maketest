#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n,ans=1;
    cin>>n;
    for(long long x=1; x<=1000000&&x*x*x<=n; x++) {
        long long k=x*x*x,t=k,rev=0;
        while(t) {
            rev=rev*10+t%10;
            t/=10;
        }
        if(rev==k)ans=k;
    }
    cout<<ans<<'\n';
}
