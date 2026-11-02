// Iterative merge sort, independently checked against generator witnesses.
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;vector<array<int,5>>position(n+1);
    for(int k=0;k<5;++k)for(int i=0;i<n;++i){int x;cin>>x;position[x][k]=i;}
    vector<int>a(n),temp(n);iota(a.begin(),a.end(),1);
    auto before=[&](int x,int y){int wins=0;for(int k=4;k>=0;--k)wins+=position[x][k]<position[y][k];return wins>2;};
    for(int width=1;width<n;width*=2){
        for(int l=0;l<n;l+=2*width){
            int mid=min(n,l+width),r=min(n,l+2*width),i=l,j=mid;
            for(int p=l;p<r;++p){
                if(i<mid && (j==r || before(a[i],a[j])))temp[p]=a[i++];else temp[p]=a[j++];
            }
        }
        a.swap(temp);
    }
    for(int i=0;i<n;++i)cout<<(i?" ":"")<<a[i];cout<<'\n';
}
