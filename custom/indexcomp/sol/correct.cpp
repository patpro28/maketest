#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

const int facN = 1e6 + 5;
const int mod = 998244353;
int ff[facN], iff[facN];
bool facinit = false;

int power(int x, int y){
    if (y == 0) return 1;

    int v = power(x, y / 2);
    v = 1LL * v * v % mod;

    if (y & 1) return 1LL * v * x % mod;
    else return v;
}

void factorialinit(){
    facinit = true;
    ff[0] = iff[0] = 1;

    for (int i = 1; i < facN; i++){
        ff[i] = 1LL * ff[i - 1] * i % mod;
    }

    iff[facN - 1] = power(ff[facN - 1], mod - 2);
    for (int i = facN - 2; i >= 1; i--){
        iff[i] = 1LL * iff[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int r){
    if (!facinit) factorialinit();

    if (n == r) return 1;

    if (r < 0 || r > n) return 0;
    return 1LL * ff[n] * iff[r] % mod * iff[n - r] % mod;
}

int P(int n, int r){
    if (!facinit) factorialinit();

    assert(0 <= r && r <= n);
    return 1LL * ff[n] * iff[n - r] % mod;
}

int Solutions(int n, int r){
    //solutions to x1 + ... + xn = r 
    //xi >= 0

    return C(n + r - 1, n - 1);
}

void Solve() 
{
    int n, m, k; cin >> n >> m >> k;
    
    vector <int> dp(n + 1, 0);
    dp[0] = 1;
    
    for (int i = 1; i <= n; i++){
        vector <int> ndp(n + 1, 0);
        for (int j = 0; j < i; j++){
            ndp[j] += dp[j] * j;
            ndp[j + 1] += dp[j] * (k - j);
        }
        
        dp = ndp;
        for (auto &x : dp) x %= mod;
    }
    
    int ans = 0;
    vector <int> p(n + 1);
    for (int i = 1; i <= n; i++){
        p[i] = power(i, m);
        p[i] += p[i - 1];
        p[i] %= mod;
    }
    
    for (int i = 1; i <= n; i++){
        p[i] *= power(i, mod - 2);
        p[i] %= mod;
        p[i] *= n;
        p[i] %= mod;
        
        ans += dp[i] * p[i];
        ans %= mod;
    }
    
    cout << ans << "\n";
}

int32_t main() 
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);
    
    cin >> t;
    for(int i = 1; i <= t; i++) 
    {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    return 0;
}