#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[200005],b[200005];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll n;
    cin>>n;
    ll dem=0;
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]<0)
            b[++dem]=a[i];
    }
    sort(b+1,b+dem+1);
    ll dem1=0;
    for(ll i=1;i<=n;i++)
    {
        if(a[i]<0)
            cout<<b[++dem1]<<" ";
        else
            cout<<a[i]<<" ";
    }

    for (int i = 1; i <= sqrt(n); ++i)
        for (int j = i; j <= n; j += i)
            d[j] += 1 + (i * i != j);
}