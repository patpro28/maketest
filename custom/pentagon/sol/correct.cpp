#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll t,n;
    t = 1;
    while( t--)
    {
        cin>>n;
        ll sum=(3*n-2+1)*n/2;
        cout<<sum<<'\n';
    }
}