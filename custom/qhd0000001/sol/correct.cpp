#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define nmax 1000005
ll n,a[nmax],sulf[nmax],ln=-1e18;
int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sulf[n]=a[n];
    for(int i=n-1;i>=1;i--)
    {
        sulf[i]=min(sulf[i+1],a[i]);
    }
    for(int i=1;i<n;i++)
    {
        ln=max(ln,a[i]-sulf[i+1]);
    }
    if(ln<=0)
        cout<<-1;
    else 
        cout<<ln;

}