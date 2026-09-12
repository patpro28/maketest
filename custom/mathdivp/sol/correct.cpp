#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, P;
    cin >> n >> P;
    string s;
    cin >> s;

    long long ans = 0;

    // Trường hợp đặc biệt
    if (P == 2 || P == 5) {
        for (int i = 0; i < n; i++) {
            int digit = s[i] - '0';
            if (digit % P == 0) {
                ans += i + 1;
            }
        }
        cout << ans;
        return 0;
    }

    vector<long long> cnt(P, 0);
    cnt[0] = 1;

    long long cur = 0;
    long long pow10 = 1;

    for (int i = n - 1; i >= 0; i--) {
        int digit = s[i] - '0';

        cur = (cur + digit * pow10) % P;

        ans += cnt[cur];
        cnt[cur]++;

        pow10 = (pow10 * 10) % P;
    }

    cout << ans;
}