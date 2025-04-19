// Problem:

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e6 + 10;
int cnt[N];
int n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    for (int i = 1; i <= 1e6 + 1; i++)
        cnt[i] += cnt[i - 1];

    LL res = 0;
    for (int num = 1; num <= 1e6; num++) {
        int t = cnt[num] - cnt[num - 1];

        for (int k = 0; 1ll * k * num <= 1000000; k++) {
            int r = min(1000001, (k + 1) * num - 1);
            int l = k * num - 1;
            res += 1ll * k * (cnt[r] - cnt[l]) * t;
        }
        res -= 1ll * t * (t + 1) / 2;
    }

    cout << res << endl;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}