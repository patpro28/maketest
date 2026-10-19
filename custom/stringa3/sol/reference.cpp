#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll k,total=0,power=1; string s; cin>>k>>s;
    for(int i=int(s.size())-1;i>=0;--i) {
        char c=s[i];
        if(c<'0'||c>'9') power=1;
        else { total=(total+(c-'0')*power)%k; power=power*10%k; }
    }
    cout<<total<<'\n';
}
