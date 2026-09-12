#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll t,n,m,k,u,v,x,y,a[405][405],s[405][405],ans=0;
set<int> st;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=m;j++){
            cin>>a[i][j];
            st.insert(a[i][j]);
	    }
	}
	ans=1000000000;
	for(auto h:st){
	    ll cs=0;
	    for(int i=1;i<=n;i++){
	        for(int j=1;j<=m;j++){
	           if(abs(a[i][j]-h)%k==0)
	               cs+=abs(a[i][j]-h)/k;
	           else{
	               cout<<-1;
	               return 0;
	           }
	        }
	    }
	    ans=min(ans,cs);
	}
	cout<<ans;
	
}