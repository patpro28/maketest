#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main(int argc,char**argv){
    int seed=argc>1?atoi(argv[1]):0;
    bool witness=argc>2 && string(argv[2])=="witness";
    if(seed==0){
        if(witness)cout<<"YES\n1 3\n4 4\n";
        else cout<<"aaab\n2\n1 1\n3 1\n";
        return 0;
    }
    vector<int> lengths,pattern,order;
    if(seed<=2){lengths={2,3};pattern={0,1,0};}
    else if(seed==3){lengths={3,4,5};pattern={0,1,2,0,2,1};}
    else if(seed==4){lengths={2,3};for(int i=0;i<20;++i){pattern.push_back(0);pattern.push_back(1);}}
    else{
        lengths=seed==5?vector<int>{3,4,5}:seed==6?vector<int>{1000,1001,1002}:vector<int>{1600,1601,1602};
        for(int i=0;i<20;++i){
            int start=seed==5?0:seed==6?2:1;
            for(int j=0;j<3;++j)pattern.push_back((start+j)%3);
        }
    }
    int total=0;for(int type:pattern)total+=lengths[type];
    string s;
    if(seed==7)for(int i=0;i<100000-total;++i)s+=char('x'+i%3);
    vector<pair<int,int>> segments;vector<int> counts(lengths.size());
    for(int i=0;i<int(pattern.size());++i){
        int type=pattern[i],left=int(s.size())+1;
        s+=string(lengths[type],char('a'+i%26));
        segments.push_back({left,int(s.size())});++counts[type];
    }
    if(witness){
        cout<<"YES\n";for(auto [l,r]:segments)cout<<l<<' '<<r<<'\n';return 0;
    }
    for(int i=0;i<int(lengths.size());++i)order.push_back(i);
    if(seed==2 || seed==7)reverse(order.begin(),order.end());
    if(seed==6)swap(order[1],order[2]);
    cout<<s<<'\n'<<lengths.size()<<'\n';
    for(int i:order)cout<<lengths[i]<<' '<<counts[i]<<'\n';
}
