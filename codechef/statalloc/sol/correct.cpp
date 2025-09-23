#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

int sumn = 0;
int sumq = 0;

void Solve() 
{
    int n; cin >> n;
    
    sumn += n;

    
    vector <int> a(n);
    for (auto &x : a) cin >> x;
    
    // change the smallest < x to = x 
    // use the first >= x 
    sort(a.begin(), a.end());
    int sum = accumulate(a.begin(), a.end(), 0LL);

    // cout << sum << "\n";
    
    int q; cin >> q;
    sumq += q;
    
    vector <int> b(q), c(q);
    for (int i = 0; i < q; i++){
        cin >> b[i] >> c[i];
    }
    
    for (int i = 0; i < q; i++){
        auto id = lower_bound(a.begin(), a.end(), b[i]) - a.begin();
        
        int ans = INF;
        
        if (id != (int) a.size()){
            int x = a[id];
            int left = sum - x;
            
            ans = max(0LL, c[i] - left);
        }
        
        if (id > 0){
            id--;
            int x = a[id];
            int left = sum - x;
            
            ans = min(ans, b[i] - x + max(0LL, c[i] - left));
        }
        
        cout << ans << '\n';
    }
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}