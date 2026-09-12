#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 5;
pair<int, int> a[N];

int bs(int l, int r, int x) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid].first == x) return mid;
        if (a[mid].first < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(a + 1, a + n + 1);

    int q; cin >> q;

    while(q--) {
        int x; cin >> x;
        int b = bs(1, n, x);
        if(b != -1) cout << a[b].second << '\n';
        else cout << 0 << '\n';
    }

    return 0;

}