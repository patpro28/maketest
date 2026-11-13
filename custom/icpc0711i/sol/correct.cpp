#include <bits/stdc++.h>
using namespace std;
struct Point {
    long long x,y,w;
    int id,rank;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long X;
    cin>>n>>X;
    vector<Point>a(n);
    for(int i=0; i<n; i++) {
        cin>>a[i].x>>a[i].y>>a[i].w;
        a[i].id=i;
    }
    sort(a.begin(),a.end(),[&](const Point&u,const Point&v) {return (__int128)(u.x-X)*v.y<(__int128)(v.x-X)*u.y;});
    for(int i=0; i<n; i++)a[i].rank=i+1;
    sort(a.begin(),a.end(),[](const Point&u,const Point&v) {return (__int128)u.x*v.y>(__int128)v.x*u.y;});
    vector<long long>bit(n+1),ans(n);
    for(auto p:a) {
        for(int t=p.rank-1; t; t-=t&-t)ans[p.id]+=bit[t];
        for(int t=p.rank; t<=n; t+=t&-t)bit[t]+=p.w;
    }
    for(long long z:ans)cout<<z<<'\n';
}
