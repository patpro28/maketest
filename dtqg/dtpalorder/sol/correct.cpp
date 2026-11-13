#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "palindrome.h"
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s;int k;cin>>s>>k;int n=s.size();
    vector<int> length(k);long long total=0;
    for(int& x:length){cin>>x;total+=x;}
    if(total>n){cout<<"NO\n";return 0;}
    Palindrome pal(s);vector<pair<int,int>> answer;int p=0;
    for(int x:length){
        while(p+x<=n && !pal.has(p,x))++p;
        if(p+x>n){cout<<"NO\n";return 0;}
        answer.push_back({p+1,p+x});p+=x;
    }
    cout<<"YES\n";
    for(auto [l,r]:answer)cout<<l<<' '<<r<<'\n';
}
