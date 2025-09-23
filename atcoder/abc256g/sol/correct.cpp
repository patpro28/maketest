#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll N=1e12+9,D=1e4+9,mod=998244353;
ll n,d;
ll c[D],inv[D],finv[D],f[D];
ll tmp[2][2];

void move(ll a[2][2],ll b[2][2]){
	for(ll i=0;i<=1;i++)
		for(ll j=0;j<=1;j++)
			b[i][j]=a[i][j];
	return;
}
void mul(ll a[2][2],ll b[2][2]){
	ll c[2][2];
	for(ll i=0;i<=1;i++)
		for(ll j=0;j<=1;j++){
			c[i][j]=0;
			for(ll k=0;k<=1;k++){
				c[i][j]+=(a[i][k]*b[k][j])%mod;
				c[i][j]%=mod;
			}
		}
	move(c,a);
	return;
}
void fstmpow(ll a[2][2],ll k){
	if(k==0){
		a[0][0]=a[1][1]=1;
		a[0][1]=a[1][0]=0;
		return;
	}
	if(k%2==0){
		fstmpow(a,k/2);
		mul(a,a);
	}
	else{
		move(a,tmp);
		fstmpow(a,k-1);
		mul(a,tmp);
	}
	return;
}
ll C(ll x){
	if(x<0||x>d-1)return 0;
	return c[x];
}
int main(){
	cin>>n>>d;
	inv[1]=1,finv[1]=1,f[1]=1;
	finv[0]=1; 
	for(ll i=2;i<=d;i++){
		inv[i]=(-(mod/i)*inv[mod%i]%mod+mod)%mod;
		finv[i]=finv[i-1]*inv[i]%mod;
		f[i]=f[i-1]*i%mod;
	}
	c[0]=1;
	for(ll i=1;i<=d-1;i++){
		//c[i]=c(d-1,i)
		c[i]=f[d-1]*finv[d-i-1]%mod*finv[i]%mod;
//		cout<<i<<" "<<c[i]<<endl; 
	}
	ll ans=0;
	for(ll k=0;k<=d+1;k++){
		ll a[2][2]={{C(k),C(k-1)},{C(k-1),C(k-2)}};
		fstmpow(a,n);
		ans+=(a[0][0]+a[1][1])%mod;
		ans%=mod;
//		cout<<k<<" "<<ans<<endl; 
	}
	cout<<ans<<endl;
	return 0;
}