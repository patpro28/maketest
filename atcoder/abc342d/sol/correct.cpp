#include <iostream>
#include <cmath>
using namespace std;
int a[200005],t[200005];
void f(int x){
	int i=2;
	while(i*i<=a[x]){
		if(a[x]%(i*i)==0) a[x]/=(i*i);
		else i++;
	}
	return ;
}
int zhao(int i){
	int ans=0;
	if(!a[i]) ans=i-1;
	else{
		ans+=t[a[i]];
		ans+=t[0];
	}
	t[a[i]]++;
	return ans;
}
int main(){
	long long n,ans=0;
	cin >>n;
	for(int i=1;i<=n;i++) cin >>a[i],f(i);
	for(int i=1;i<=n;i++){
		ans+=zhao(i);
	}
	cout <<ans;
	return 0;
}