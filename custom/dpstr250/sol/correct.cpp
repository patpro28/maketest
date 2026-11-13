#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    int p; string d; cin>>n>>m>>p>>a>>b>>d;
    int stride=p+1;
    vector<int> previous((m+1)*stride,0),current((m+1)*stride,0);
    int answer=0;
    for(int i=0;i<n;++i) {
        for(int j=1;j<=m;++j) for(int h=1;h<=p;++h) {
            int index=j*stride+h;
            current[index]=(a[i]==b[j-1] && a[i]==d[h-1]) ? previous[(j-1)*stride+h-1]+1 : 0;
            answer=max(answer,current[index]);
        }
        previous.swap(current);
    }
    cout<<answer<<'\n';
}
