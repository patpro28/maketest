#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define pb push_back
#define endl '\n'
#define sz(a) (int)a.size()
#define setbits(x) __builtin_popcountll(x)
#define ff first
#define ss second
#define conts continue
#define ceil2(x,y) ((x+y-1)/(y))
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define yes cout << "Yes" << endl
#define no cout << "No" << endl

#define rep(i,n) for(int i = 0; i < n; ++i)
#define rep1(i,n) for(int i = 1; i <= n; ++i)
#define rev(i,s,e) for(int i = s; i >= e; --i)
#define trav(i,a) for(auto &i : a)

template<typename T>
void amin(T &a, T b) {
    a = min(a,b);
}

template<typename T>
void amax(T &a, T b) {
    a = max(a,b);
}

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

/*



*/

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;
const int inf1 = int(1e9) + 5;
const ll inf2 = ll(1e18) + 5;

void solve(){
    ll n; cin >> n;
    vector<ll> a(n+5);
    rep1(i,n) cin >> a[i];
    
    auto go = [&](vector<ll> b) -> bool{
        ll siz = sz(b);
        b.insert(b.begin(),0);

        if(siz&1) return 1;
        if(siz == 2) return 1;

        rep1(i,siz){
            if(b[i] == b[siz-i+1]){
                return 1;
            }
        }

        if(b[1] == 2 and b[siz] == 1 and b[siz-1] == 1) return 1;
        if(b[siz] == 2 and b[1] == 1 and b[2] == 1) return 1;

        if(b[siz/2] == 2 and b[siz/2+2] == 1) return 1;
        if(b[siz/2+1] == 2 and b[siz/2-1] == 1) return 1;

        rep1(i,siz-3){
            if(b[i] == b[i+1] and b[i+2] == b[i+3] and b[i] != b[i+2]){
                return 1;
            }
        }

        ll curr_cnt = 0;
        b[1] = 1, b[siz] = 1;

        rep1(i,siz){
            if(b[i] == 1){
                curr_cnt++;
            }
            else{
                curr_cnt = 0;
            }

            if(curr_cnt >= 3){
                return 1;
            }
        }

        return 0;
    };

    ll ans = 0;

    rep1(l,n){
        vector<ll> b;
        for(int r = l; r <= n; ++r){
            b.pb(a[r]);
            ans += go(b);
        }
    }

    cout << ans << endl;
}

int main()
{
    fastio;

    int t = 1;
    cin >> t;

    rep1(i, t) {
        solve();
    }

    return 0;
}