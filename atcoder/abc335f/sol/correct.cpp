#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define FOR(i , a , b) for(int i = a ; i <= b; i++)
#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define maxn 200005
#define REVERSE(i , a , b) for(int i = a ; i >= b ; i--)
#define B 450

ll dp[maxn] , a[maxn] , dp_2[B + 5][B + 5];

const ll MOD = 998244353;

int main(){
    FAST;
    int n;
    cin >> n;
   
    dp[1] = 1;
    FOR(i , 1 , n){
        cin >> a[i];
        FOR(v , 1 , B){
            dp[i] += dp_2[v][i % v];
            if(dp[i] >= MOD) dp[i] -= MOD;
        }

        int v = a[i];
        if(v <= B){
            dp_2[v][i % v] += dp[i];
            if(dp_2[v][i % v] >= MOD) dp_2[v][i % v] -= MOD;
        }

        else{
            for(int j = i + v ; j <= n ; j += v){
                dp[j] += dp[i];
                if(dp[j] >= MOD) dp[j] -= MOD;
            }
        }
    }

    ll ans = 0;
    FOR(i , 1 , n){
        ans += dp[i];
        if(ans >= MOD) ans -= MOD;
    }

    cout << ans % MOD;
}