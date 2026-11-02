// Expand palindrome centers, then DP by multiplicities, choosing the last piece.
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s;cin>>s;int n=int(s.size()),t;cin>>t;vector<vector<int>>queries(t);vector<bool>ok(t,true);vector<int>lengths;
    for(auto& query:queries){int k;cin>>k;query.resize(k);for(int& length:query){string token;cin>>token;int v=0;for(char c:token)v=min(n+1,v*10+c-'0');length=v;}}
    for(int q=0;q<t;++q){int sum=0;for(int x:queries[q])sum+=x;if(sum>n)ok[q]=false;else for(int x:queries[q])lengths.push_back(x);}
    bool uniform=all_of(s.begin(),s.end(),[&](char c){return c==s[0];});
    bool alternating=n>=2 && s[0]!=s[1];for(int i=2;i<n;++i)alternating=alternating && s[i]==s[i-2];
    if(uniform || alternating){
        for(int q=0;q<t;++q){bool answer=ok[q];if(alternating)for(int x:queries[q])if(x%2==0)answer=false;cout<<(answer?"YES\n":"NO\n");}return 0;
    }
    sort(lengths.begin(),lengths.end());lengths.erase(unique(lengths.begin(),lengths.end()),lengths.end());
    const uint16_t inf=uint16_t(n+1);vector<int>row(n+1,-1);vector<vector<uint16_t>>after(lengths.size(),vector<uint16_t>(n+1,inf));
    for(int i=0;i<int(lengths.size());++i)row[lengths[i]]=i;
    auto record=[&](int l,int r){int id=row[r-l+1];if(id!=-1)after[id][l]=uint16_t(r+1);};
    for(int center=0;center<n;++center){
        for(int l=center,r=center;l>=0 && r<n && s[l]==s[r];--l,++r)record(l,r);
        for(int l=center-1,r=center;l>=0 && r<n && s[l]==s[r];--l,++r)record(l,r);
    }
    for(auto& v:after)for(int p=n-1;p>=0;--p)v[p]=min(v[p],v[p+1]);
    for(int q=0;q<t;++q){
        if(!ok[q]){cout<<"NO\n";continue;}
        vector<int>query=queries[q];sort(query.begin(),query.end());vector<pair<int,int>>groups;
        for(int x:query){if(groups.empty() || groups.back().first!=x)groups.push_back({x,1});else ++groups.back().second;}
        vector<int>place;int states=1;for(auto [length,count]:groups){(void)length;place.push_back(states);states*=count+1;}
        vector<uint16_t>best(states,inf);best[0]=0;
        for(int state=1;state<states;++state)for(int i=0;i<int(groups.size());++i){
            if(state/place[i]%(groups[i].second+1)==0)continue;
            int previous=best[state-place[i]];
            if(previous!=inf)best[state]=min(best[state],after[row[groups[i].first]][previous]);
        }
        cout<<(best.back()!=inf?"YES\n":"NO\n");
    }
}
