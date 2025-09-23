#include<bits/stdc++.h>
using namespace std;
long long n,kq=0,a[100005];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        if(a[i]>=kq)
        {
            kq++;
        }
    }
    cout<<kq;
}