#include <algorithm>
#include <array>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;
using Key = uint64_t;
const int M1 = 1000000007, M2 = 1000000009, BASE = 911382323;
struct Hash {
    vector<int> a,b,p,q;
    explicit Hash(const vector<ll>& s):a(s.size()+1),b(s.size()+1),p(s.size()+1,1),q(s.size()+1,1) {
        for (int i=0;i<(int)s.size();++i) {
            ll x=(s[i]%M1+M1)%M1, y=(s[i]%M2+M2)%M2;
            a[i+1]=(a[i]*(ll)BASE+x)%M1; b[i+1]=(b[i]*(ll)BASE+y)%M2;
            p[i+1]=p[i]*(ll)BASE%M1; q[i+1]=q[i]*(ll)BASE%M2;
        }
    }
    explicit Hash(const string& s):Hash(vector<ll>(s.begin(),s.end())) {}
    Key get(int l,int r) const { // Half-open interval [l,r).
        ll x=(a[r]-a[l]*(ll)p[r-l]%M1+M1)%M1;
        ll y=(b[r]-b[l]*(ll)q[r-l]%M2+M2)%M2;
        return (Key(x)<<32)|Key(y);
    }
};
struct KeyHash {
    size_t operator()(Key x) const { // Deterministic mixing; generation remains reproducible.
        x+=0x9e3779b97f4a7c15ULL;x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;
        x=(x^(x>>27))*0x94d049bb133111ebULL;return x^(x>>31);
    }
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;cin>>n>>m;unordered_set<Key,KeyHash>groups;groups.reserve(n);
    while(n--){
        string s;cin>>s;s+=s;Hash h(s);int best=0;
        for(int i=1;i<m;++i){
            int lo=0,hi=m+1;
            while(hi-lo>1){int mid=(hi+lo)/2;if(h.get(i,i+mid)==h.get(best,best+mid))lo=mid;else hi=mid;}
            if(lo<m && s[i+lo]<s[best+lo])best=i;
        }groups.insert(h.get(best,best+m));
    }cout<<groups.size()<<'\n';
}
