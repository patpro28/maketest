#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

#define lf '\n'
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define repk(i,n,k) for(int i=0;i<(int)n;i+=k)

/* ABC331 C Sum of Numbers Greater Than Me */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<i64> a(n), b(n), c(n);
    rep(i, n) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b.begin(), b.end());
    rep(i, n) {
        if (i == 0) c[i] = b[i];
        else c[i] = c[i-1] + b[i];
    }
    rep(i, n) {
        int d = distance(b.begin(), upper_bound(b.begin(), b.end(), a[i]));
        if (i != n-1) cout << c[n-1]-c[d-1] << " ";
        else cout << c[n-1]-c[d-1] << lf;
    }
    return 0;
}
