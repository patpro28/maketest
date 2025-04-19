#include <bits/stdc++.h>
using namespace std;



int main() {
    long long n, x;
    cin >> n >> x;
    vector<pair<long long, long long>> v(n);
    
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

   
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
    //dp[i][j]=can u reach jth coordinate after ith jump
    dp[1][v[0].first]=1 ;
    dp[1][v[0].second]=1 ;
    for(int i=2;i<=n;i++){
          for(int j=0;j<=x;j++){
              if(dp[i-1][j]==1){
                   if(j+v[i-1].first<=x) dp[i][j+v[i-1].first]=1 ;
                  if(j+v[i-1].second<=x) dp[i][j+v[i-1].second]=1 ;
              }
          }
    }
    if(dp[n][x]==1) cout<<"Yes"<<endl ;
    else cout<<"No"<<endl ;
    

    return 0;
}
