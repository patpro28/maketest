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

int main(){
    if(FILE* input=fopen("ROBOT.INP","r")){fclose(input);freopen("ROBOT.INP","r",stdin);freopen("ROBOT.OUT","w",stdout);}
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;int x,y;cin>>x>>y;int dx=0,dy=0,right=0,left=0;
    for(int i=1;i<n;++i){
        int nx,ny;cin>>nx>>ny;int ex=nx-x,ey=ny-y;
        if(i>1){int cross=dx*ey-dy*ex;right+=cross<0;left+=cross>0;}
        dx=ex;dy=ey;x=nx;y=ny;
    }
    cout<<right<<' '<<left<<'\n';
}
