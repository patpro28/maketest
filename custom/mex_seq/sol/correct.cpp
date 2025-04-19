// Problem: MEX Sequences
// Contest: CodeChef - STR84TST
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Author: abhidot

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
#define ll long long
#define IOS std::ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define pb push_back
#define mod 1000000007
#define mod2 998244353
#define lld long double
#define pii pair<int, int>
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define uniq(v) (v).erase(unique(all(v)),(v).end())
#define rep(i,x,y) for(int i=x; i<y; i++)
#define fill(a,b) memset(a, b, sizeof(a))
#define vi vector<int>
#define V vector
#define setbits(x) __builtin_popcountll(x)
#define w(x)  int x; cin>>x; while(x--)
using namespace std;
using namespace __gnu_pbds; 
template <typename num_t> using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;
const long long N=1000005, INF=2000000000000000000, inf = 2e9+5;
 
int power(int a, int b, int p){
	if(a==0)
	return 0;
	int res=1;
	a%=p;
	while(b>0)
	{
		if(b&1)
		res=(res*a)%p;
		b>>=1;
		a=(a*a)%p;
	}
	return res;
}
 
 
void print(bool n){
    if(n){
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }
}


int f[N], in[N]; 

int ncr(int n, int r){
	if(n<0) return 0; 
	if(n<r) return 0;
	return f[n]*in[r]%mod*in[n-r]%mod;
}

int ff(int n, int m){
	int ans=0;
	for(int i=0;i<=m;i++){
		ans = (ans + ncr(n-1, i))%mod;
	}
	return ans;
}
 
int32_t main()
{
    IOS;
    f[0]=1, in[0]=1;
    for(int i=1;i<N;i++){
    	f[i]=i*f[i-1]%mod;
    }
    in[N-1]=power(f[N-1], mod-2, mod);
    for(int i=N-2;i>=0;i--){
    	in[i]=(i+1)*in[i+1]%mod;
    }
    
		w(T){
			int n, m;
			cin>>n>>m;
			m = min(m, n);
			{
				int typ1 = ff(n, m);
				int typ2 = 0, prv = 0;
				for(int i=1;i<n&&m>=2;i++){
					if(i==1) prv = 1;
					else{
						int here = (2*prv%mod - ncr(i-2, min(i-2, m-2)))%mod;
						if(here<0) here+=mod;
						if(i-1<=m-2) here = (here + ncr(i-1, i-1))%mod;
						prv = here;
					}
					// cout<<prv<<" ";
					typ2 = (typ2 + prv*power(2, n-1-i, mod)%mod)%mod;
				}
				int typ3 = (m>0);
				// cout<<typ1<<" "<<typ2<<" "<<typ3<<"\n";
				int ans = (typ1 + typ2 + typ3)%mod;
				cout<<ans<<"\n";
			}
		}
}