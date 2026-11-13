// Submitted greedy algorithm; standard includes replace bits/stdc++.h for portability.
#include <algorithm>
#include <iostream>
using namespace std;
#define ll long long
#define fi first
#define se second
#define fast ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int a, b, c, s, need, sub, ans;
int main()
{
    fast;
    cin>>a>>b>>c>>s;
    need=s;
    while(a or b or c)
    {
        need=s;
        sub=min(need/3,c);
        c-=sub;
        need-=sub*3;
        sub=min(need/2,b);
        b-=sub;
        need-=sub*2;
        sub=min(need,a);
        a-=sub;
        need-=sub;
        if(need)
        {
            if(a and need)
            {
                sub=min(need,a);
                need-=sub;
                a-=sub;
            }
            if(b and need)
            {
                sub=min((need+1)/2,b);
                need-=sub*2;
                b-=sub;
            }
            if(c and need)
            {
                sub=min((need+2)/3,c);
                need-=sub*3;
                c-=sub;
            }
        }
        if(need<=0) ans++;
    }
    cout<<ans;
}
