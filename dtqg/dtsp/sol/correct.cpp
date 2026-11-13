#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

int advance(int value,int cap,int s){int remaining=value%s;return remaining+cap>=s?value+s-remaining:value+cap;}
int main(){
    if(FILE* input=fopen("SP.INP","r")){fclose(input);freopen("SP.INP","r",stdin);freopen("SP.OUT","w",stdout);}
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int a,b,c,s;cin>>a>>b>>c>>s;int width=c+1;
    vector<int> previous((b+1)*width),current(previous.size());
    for(int i=0;i<=a;++i){
        fill(current.begin(),current.end(),0);
        for(int j=0;j<=b;++j)for(int k=0;k<=c;++k){
            int index=j*width+k,best=0;
            if(i)best=advance(previous[index],1,s);
            if(j)best=max(best,advance(current[index-width],2,s));
            if(k)best=max(best,advance(current[index-1],3,s));
            current[index]=best;
        }
        previous.swap(current);
    }
    cout<<previous.back()/s<<'\n';
}
