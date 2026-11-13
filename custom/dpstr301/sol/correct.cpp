#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; string a; cin>>n>>a;
    string b="abc";
    vector<long long> f(b.size()+1); f[0]=1;
    for(char ch:a) for(int j=int(b.size());j>=1;--j)
        if(ch==b[j-1]) f[j]+=f[j-1];
    cout<<f.back()<<'\n';
}
