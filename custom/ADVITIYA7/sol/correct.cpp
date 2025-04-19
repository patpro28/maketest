#include<bits/stdc++.h>
using namespace std;
/* Abhi-Atg */
#define ll long long
#define mod 1000000007

map<int,int> solve(int x){
    map<int,int> mp;
    for(ll i=2;i*i<=x;i++){
        if(x%i==0){
            while(x%i==0){
                x/=i;
                mp[i]++;
            }
        }  
    }
    if(x>1)mp[x]++;
    return mp;
}

int main(){


    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll t=1;
    cin >> t;
    while(t--){
        ll x,q;cin >> x >> q;
        map<int,int> mp=solve(x);
        while(q--){
            ll p;cin >> p;
            int ans=1;
            for(auto it:mp){
                if(it.second%p==0 && p!=1){
                    (ans=ans*2)%=mod;
                }
            }
            cout<<ans<<"\n";
        }
    }


    return 0;
}