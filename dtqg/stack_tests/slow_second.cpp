// Correct but quadratic: repeatedly follows fixed nearest-greater links.
// Kept outside sol/ for the optional performance regression check.
#include <iostream>
using namespace std;
using ll = long long;
int n, a[200005], l[200005], r[200005];
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        int it = i - 1;
        while (it > 0 && a[it] < a[i]) it = l[it];
        l[i] = it;
    }
    for (int i = n; i >= 1; --i) {
        int it = i + 1;
        while (it <= n && a[it] < a[i]) it = r[it];
        r[i] = it;
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (r[i] != n + 1) {
            int it = r[i] + 1;
            while (it <= n && a[it] < a[i]) it = r[it];
            ans += 1LL * a[i] * (it - r[i]) * (i - l[i]);
        }
        if (l[i] != 0) {
            int it = l[i] - 1;
            while (it > 0 && a[it] < a[i]) it = l[it];
            ans += 1LL * a[i] * (l[i] - it) * (r[i] - i);
        }
    }
    cout << ans << '\n';
}
