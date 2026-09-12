#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> f(MAXN + 1, 0), pref(MAXN + 1, 0);

    // Tính f(n): tổng ước lẻ
    for (int d = 1; d <= MAXN; d += 2) { // chỉ duyệt d lẻ
        for (int j = d; j <= MAXN; j += d) {
            f[j] += d;
        }
    }

    // prefix sum
    for (int i = 1; i <= MAXN; i++) {
        pref[i] = pref[i - 1] + f[i];
    }

    int T;
    cin >> T;
    while (T--) {
        int L, R;
        cin >> L >> R;
        cout << pref[R] - pref[L - 1] << '\n';
    }

    return 0;
}