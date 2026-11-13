#pragma once
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include "random.h"
using namespace std;
string plus_small(string a,int x){int i=int(a.size())-1;while(x && i>=0){int value=a[i]-'0'+x;a[i]=char('0'+value%10);x=value/10;--i;}if(x)a=to_string(x)+a;return a;}
string add_decimal(string a,string b){int n=max(a.size(),b.size()),carry=0;string c;for(int i=0;i<n;++i){int x=i<int(a.size())?a[a.size()-1-i]-'0':0,y=i<int(b.size())?b[b.size()-1-i]-'0':0;int v=x+y+carry;c+=char('0'+v%10);carry=v/10;}if(carry)c+='1';reverse(c.begin(),c.end());return c;}
int main(int argc,char**argv){
 int seed=argc>1?atoi(argv[1]):0;Random rng(2026110400ULL+TASK_ID*1000+seed);
 if(TASK_ID==0){
  if(seed==0){cout<<"2\n0 0\n1 0\n";return 0;}
  if(seed==1){cout<<"5\n0 0\n1 0\n0 0\n-1 0\n0 0\n";return 0;}
  int n=seed<4?20:seed<8?200:seed<12?10000:70000;
  const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};int x=0,y=0,dir=0;
  cout<<n<<'\n'<<"0 0\n";
  for(int i=1;i<n;++i){if(seed==14){if(i<n/3)dir=2;else if(i<2*n/3)dir=3;else dir=i%2?0:2;}else if(seed==2 || seed==13)dir=(dir+1)%4;else if(seed==3)dir=(dir+3)%4;else if(seed==12)dir=0;else dir=rng.uniform(0,3);x+=dx[dir];y+=dy[dir];cout<<x<<' '<<y<<'\n';}
 }else if(TASK_ID==2){
  vector<array<string,3>> edge={{{"1","1","2"}},{{"9","9","1*"}},{{"*","*","1"}},{{"0","1","1"}}};
  if(seed<4){for(auto& s:edge[seed])cout<<s<<'\n';return 0;}
  int n=seed<8?3:seed<12?200:100000;
  if(seed==12){cout<<string(n,'*')<<'\n'<<string(n,'*')<<'\n'<<string(n,'*')<<'\n';return 0;}
  if(seed==13){cout<<string(n-1,'9')<<"\n1\n1"<<string(n-1,'0')<<'\n';return 0;}
  string a(n,'0'),b(n,'0');for(int i=0;i<n;++i){a[i]=char('0'+rng.uniform(i?0:1,9));b[i]=char('0'+rng.uniform(i?0:1,9));}
  if(seed==14)a[0]=b[0]='1';
  string c=add_decimal(a,b);if(c.size()>100000){a[0]=b[0]='1';c=add_decimal(a,b);}
  for(string* s:{&a,&b,&c})for(char& ch:*s)if(rng.uniform(0,3)!=0)ch='*';
  if(seed==15)c="0"+c.substr(1);
  cout<<a<<'\n'<<b<<'\n'<<c<<'\n';
 }else if(TASK_ID==3){
  vector<array<int,4>> edge={{{0,0,0,1}},{{0,0,4,4}},{{1,1,1,7}},{{1,1,1,1}}};
  int a,b,c,s;
  if(seed<4){auto t=edge[seed];a=t[0];b=t[1];c=t[2];s=t[3];}
  else if(seed<8){a=rng.uniform(0,5);b=rng.uniform(0,5);c=rng.uniform(0,5);s=rng.uniform(1,15);}
  else{a=b=c=seed<12?80:270;s=seed<12?seed-2:seed==12?4:seed==13?3:seed==14?1000000:5;}
  cout<<a<<' '<<b<<' '<<c<<' '<<s<<'\n';
 }else if(TASK_ID==5){
  vector<long long> values;
  const vector<long long> small={2,4,8,16,30,36,64,100,216,900,2310};
  if(seed<4){values={small[seed],small[seed+4]};}
  else if(seed<8){for(int i=0;i<15;++i)values.push_back(small[rng.uniform(0,int(small.size())-1)]);}
  else if(seed==12){values.assign(150,999999999989LL);}
  else{
   const int primes[]={2,3,5,7,11,13,17,19,23,29,31};long long product=1;
   for(int m=1;m<=11;++m){product*=primes[m-1];long long value=product;while(value<=1000000000000LL){values.push_back(value);if(value>1000000000000LL/product)break;value*=product;}}
   values.push_back(999999999989LL);values.push_back(9999999967LL);
   if(seed==13)values.assign(150,260620460100LL);
   else while(values.size()<150)values.push_back(values[rng.uniform(0,int(values.size())-1)]);
   rng.shuffle(values.begin(),values.end());
  }
  cout<<values.size()<<'\n';for(auto x:values)cout<<x<<'\n';
 }else if(TASK_ID==6){
  vector<pair<string,int>> edge={{"()",1},{"))((",1},{"()()",1},{"((()))",2}};
  if(seed<4){cout<<edge[seed].first<<'\n'<<edge[seed].second<<'\n';return 0;}
  int n=seed<8?16:seed<12?200:4000;string s(n,'(');int k=1;
  if(seed==12){s=string(n/2,'(')+string(n/2,')');k=n/2;}
  else if(seed==13){for(int i=0;i<n;++i)s[i]=i%2?')':'(';k=1;}
  else if(seed==14){for(char& c:s)c=rng.uniform_bool()?'(':')';k=n/2;}
  else if(seed==15){s=string(n/2,')')+string(n/2,'(');k=n/2;}
  else{for(char& c:s)c=rng.uniform_bool()?'(':')';k=rng.uniform(1,n/2);}
  cout<<s<<'\n'<<k<<'\n';
 }else if(TASK_ID==8){
  vector<pair<string,string>> edge={{"A","A"},{"A","D"},{"ADGT","TGDA"},{"AAAADDDDGGGGTTTT","ADGTADGTADGTADGT"}};
  if(seed<4){cout<<edge[seed].first<<'\n'<<edge[seed].second<<'\n';return 0;}
  int n=seed<8?7:seed<12?30:45;string a(n,'A'),alphabet="ADGT";
  for(char& c:a)c=alphabet[rng.uniform(0,3)];string b=a;
  if(seed==12){for(int i=0;i<n;++i)a[i]=alphabet[i/12];b=a;rng.shuffle(b.begin(),b.end());}
  else if(seed==13){a=string(n,'A');b=a;}
  else if(seed==14){for(int i=0;i<n;++i)a[i]=alphabet[i/12];for(int i=0;i<n;++i)b[i]=alphabet[i%4];b=a;rng.shuffle(b.begin(),b.end());}
  else if(seed==15){for(int t=0;t<4;++t){int l=rng.uniform(0,n-1),r=rng.uniform(l,n-1);reverse(b.begin()+l,b.begin()+r+1);}}
  else if(seed%2){rng.shuffle(b.begin(),b.end());}
  else for(int t=0;t<seed%5;++t){int l=rng.uniform(0,n-1),r=rng.uniform(l,n-1);reverse(b.begin()+l,b.begin()+r+1);}
  cout<<a<<'\n'<<b<<'\n';
 }else if(TASK_ID==9){
  vector<array<string,3>> edge={{{"0","0","0"}},{{"111","0","111"}},{{"1000","0","1000"}},{{"101","101","101"}}};
  if(seed<4){for(auto& x:edge[seed])cout<<x<<'\n';return 0;}
  if(seed<8){string s(14,'0');s[0]='1';for(int i=1;i<14;++i)s[i]=char('0'+rng.uniform(0,3));int A=rng.uniform(0,200),B=A+rng.uniform(0,200);cout<<s<<'\n'<<A<<'\n'<<B<<'\n';return 0;}
  if(seed<12 || seed==12 || seed==13){
   int n=seed<12?200:1000;string s(n,'0');s[0]='1';for(int i=1;i<n;++i)s[i]=seed==13?char('0'+i%2):char('0'+rng.uniform(0,9));
   string a=seed==13?string(n,'1'):"0",b(n,'9');cout<<s<<'\n'<<a<<'\n'<<b<<'\n';return 0;
  }
  int n=200000;string a,b,s;
  if(seed==14){a="1"+string(n-11,'0');b=plus_small(a,1000000);s="1"+string(n-21,'0')+"01234567890123456789";}
  else{a=string(n-1,'9');b="1"+string(n-1,'0');s=b;}
  cout<<s<<'\n'<<a<<'\n'<<b<<'\n';
 }
}
