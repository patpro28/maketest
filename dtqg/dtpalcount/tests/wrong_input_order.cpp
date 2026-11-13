// Student submission: greedily finish each type in input order.
// Only standard includes and an equivalent size cast were adapted for portability.
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
const int mod1 = 1000000007;
const int mod2 = 1000000009;
const int base = 331;
string s;
int d;
vector<pair<int,int>> res;
ll cd(ll a,ll mod){return (a%mod+mod)%mod;}
struct Hash{
    int n;
    vector<ll> h1,h2,p1,p2;
    explicit Hash(string s){
        n=int(s.size());h1.resize(n+1);h2.resize(n+1);p1.resize(n+1);p2.resize(n+1);
        p1[0]=p2[0]=1;
        for(int i=1;i<=n;++i){
            p1[i]=p1[i-1]*base%mod1;p2[i]=p2[i-1]*base%mod2;
            h1[i]=cd(h1[i-1]*base+s[i-1]-'a'+1,mod1);
            h2[i]=cd(h2[i-1]*base+s[i-1]-'a'+1,mod2);
        }
    }
    pair<ll,ll> get(int l,int r){
        return {cd(h1[r]-h1[l-1]*p1[r-l+1],mod1),cd(h2[r]-h2[l-1]*p2[r-l+1],mod2)};
    }
};
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>s>>d;int sumc=0;Hash hs1(s);reverse(s.begin(),s.end());Hash hs2(s);
    int le=0,n=hs1.n;
    for(int i=1;i<=d;++i){
        int len,c;cin>>len>>c;sumc+=c;
        for(int dem=1;dem<=c;++dem){
            bool ok=false;
            for(int j=le+1;j+len-1<=n;++j){
                int l=j,r=j+len-1;
                if(hs1.get(l,r)==hs2.get(n-r+1,n-l+1)){
                    ok=true;le=r;res.push_back({l,r});break;
                }
            }
            if(!ok){cout<<"NO";return 0;}
        }
    }
    if(int(res.size())<sumc){cout<<"NO";return 0;}
    cout<<"YES\n";for(auto& p:res)cout<<p.first<<' '<<p.second<<'\n';
}
