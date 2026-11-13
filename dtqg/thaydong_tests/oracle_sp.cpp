#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
// Independent remaining-stock recurrence: remove one minimal complete group.
int main(){
 int A,B,C,S;cin>>A>>B>>C>>S;
 int width=C+1,plane=(B+1)*width;vector<int> f((A+1)*plane);
 struct Group{int a,b,c;};vector<Group> groups;
 for(int a=0;a<=A;++a)for(int b=0;b<=B;++b)for(int c=0;c<=C;++c){
  int total=a+2*b+3*c;if(total<S)continue;
  int minimum=a?1:b?2:3;
  if(total-minimum<S)groups.push_back({a,b,c});
 }
 for(int a=0;a<=A;++a)for(int b=0;b<=B;++b)for(int c=0;c<=C;++c){
  int& best=f[a*plane+b*width+c];
  for(auto g:groups)if(g.a<=a && g.b<=b && g.c<=c)best=max(best,1+f[(a-g.a)*plane+(b-g.b)*width+c-g.c]);
 }
 cout<<f.back()<<'\n';
}
