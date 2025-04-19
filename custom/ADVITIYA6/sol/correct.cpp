#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int N=2*1e5+1,M=1e9+7,B=32;
typedef long long ll;
int a[N],xx[N];

typedef pair<int,int> pii;
pii dp[N][B];
int dc[N];

int main() {
	int t; scanf("%d",&t);
	while(t--){
	    int n;scanf("%d",&n);
	    unordered_map<int,vector<pii>> x;
	    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	    x[0].push_back({0,1});
	    for(int i=1;i<=n;++i){
	        int v=a[i]; xx[i]=xx[i-1]^v;
	        dp[i][0]={i-1,v}; dc[i]=1;
	        for(int j=0;j<dc[i-1];++j){
	            int vp=v;v&=dp[i-1][j].second;
	            if(v==vp){
	                dp[i][dc[i]-1].first=dp[i-1][j].first;
	            }
	            else{
	                dp[i][dc[i]++]={dp[i-1][j].first,v};
	            }
	            
	        }
	        
	        int pr=0;
	        auto& xi=x[xx[i]];
	        if(xi.size()){
	            pr=xi.rbegin()->second;
	        }
	        else{
	            xi.push_back({0,0});
	        }
	        xi.push_back({i,pr+1});
	        
	    }
	    
	    ll ans=0;
	    for(int i=1;i<=n;++i){
	        int r=i;
	        for(int j=0;j<dc[i];++j){
	            int v=xx[i]^dp[i][j].second;
	            int l=dp[i][j].first;
	            //cerr<<l<<" "<<r<<" "<<v<<endl;
	            if(x.count(v)){
	                auto ir =prev(lower_bound(x[v].begin(),x[v].end(),(pii){r,0}));
	                auto il=lower_bound(x[v].begin(),x[v].end(),(pii){l,0});
	                ans+=ir->second;
	                if(il!=x[v].begin())
	                    ans-=prev(il)->second;
	                //cerr<<ans-ap<<endl;
	                
	            }
	            r=l;
	        }
	    }
	    //cerr<<"-"<<endl;
	    printf("%lld\n",ans);
	}
	return 0;
}
