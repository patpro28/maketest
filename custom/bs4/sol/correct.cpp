#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll bs(vector<ll> &a, ll x){
    ll ans = LLONG_MAX;
    ll l = 0, r = a.size() - 1;
    while (l <= r){
        ll m = (l + r) / 2;
        ans = min(ans, abs(a[m] - x));
        if (x >= a[m]) l = m + 1;
        else r = m - 1;
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    ll t;   cin >> t;
    while(t--){
        ll x;   cin >> x;
        cout << bs(a, x) << '\n';
    }
    return 0;
}