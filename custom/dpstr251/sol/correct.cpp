#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    cin>>n>>m>>a>>b;
    int stride=m+1;
    vector<uint16_t> prefix((n+1)*stride,0);
    vector<int> row(m+2,0);
    for(int i=1;i<=n;++i) {
        int diagonal=0;
        for(int j=1;j<=m;++j) {
            int old=row[j]; row[j]=a[i-1]==b[j-1] ? diagonal+1 : 0; diagonal=old;
            prefix[i*stride+j]=max(row[j],max((int)prefix[(i-1)*stride+j],(int)prefix[i*stride+j-1]));
        }
    }
    fill(row.begin(),row.end(),0); int answer=-1;
    for(int i=n-1;i>=0;--i) {
        int diagonal=0;
        for(int j=m-1;j>=0;--j) {
            int old=row[j]; row[j]=a[i]==b[j] ? diagonal+1 : 0; diagonal=old;
            int first=prefix[i*stride+j];
            if(first>0 && row[j]>0) answer=max(answer,first+row[j]);
        }
    }
    cout<<answer<<'\n';
}
