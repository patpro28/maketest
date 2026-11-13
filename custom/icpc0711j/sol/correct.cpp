#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vector<long long>a(n),b(n);
    long long sum=0;
    for(auto &x:a) {
        cin>>x;
        for(long long t=x; t; t/=10)sum+=t%10;
    }
    long long ans=2*n*sum;
    for(long long p=10; p<=1000000000000000LL; p*=10) {
        for(int i=0; i<n; i++)b[i]=a[i]%p;
        sort(b.begin(),b.end());
        int j=n;
        for(int i=0; i<n; i++) {
            while(j>0&&b[i]+b[j-1]>=p)--j;
            ans-=9LL*(n-j);
        }
    }
    cout<<ans<<'\n';
}
