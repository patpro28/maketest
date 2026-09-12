#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int Nprime=1e7+5;
vector<int> prefix(string s){
    int n=s.size();
    vector<int> p(n);
    for(int i=1;i<n;i++){
        int j=p[i-1];
        while(j>0&&s[i]!=s[j])
            j=p[j-1];
        if(s[i]==s[j])
            j++;
        p[i]=j;
    }
    return p;
}
string s;
int main(){
    // testcase();
    // readfo();
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>s;
    vector<int> p=prefix(s);
    int n=s.size(),j=p[n-1];
    if(j==0) {
        cout<<"Just a legend";
        return 0;
    }
    for(int i = 0; i < n - 1; i++)
        if(p[i]==j){
            cout<<s.substr(0, j);
            return 0;
        }
    j=p[j-1];
    if(j==0){
        cout<<"Just a legend";
        return 0;
    }
    cout<<s.substr(0,j);
    return 0;
}