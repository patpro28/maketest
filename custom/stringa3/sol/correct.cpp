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
    ll k,answer=0,value=0; string s; cin>>k>>s;
    s+='a';
    for(char c:s) {
        if(c>='0' && c<='9') value=(value*10+c-'0')%k;
        else { answer=(answer+value)%k; value=0; }
    }
    cout<<answer<<'\n';
}
