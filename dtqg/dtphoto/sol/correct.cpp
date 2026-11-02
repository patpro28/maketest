#include <algorithm>
#include <array>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
int main(){
    if(FILE* file=fopen("PHOTO.INP","r")){
        fclose(file);
        if(!freopen("PHOTO.INP","r",stdin))return 1;
        if(!freopen("PHOTO.OUT","w",stdout))return 1;
    }
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;vector<array<int,5>>pos(n+1);
    for(int k=0;k<5;++k)for(int i=0;i<n;++i){int x;cin>>x;pos[x][k]=i;}
    vector<int>answer(n);iota(answer.begin(),answer.end(),1);
    sort(answer.begin(),answer.end(),[&](int x,int y){
        int votes=0;for(int k=0;k<5;++k)votes+=pos[x][k]<pos[y][k];return votes>=3;
    });
    for(int i=0;i<n;++i)cout<<(i?" ":"")<<answer[i];cout<<'\n';
}
