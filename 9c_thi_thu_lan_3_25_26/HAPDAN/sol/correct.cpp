/*
Author: Tu Pham Anh
Date: 2026/05/09 - 14:32
*/
#include <bits/stdc++.h>

using namespace std;

vector<long long> num;
bool d[10];

void dq(int i, int n, long long val = 0) {
    if (i == n) {
        num.push_back(val);
        return;
    }
    for (int j = (i == 0); j < 10; j++) {
        if (!d[j]) {
            d[j] = true;
            dq(i + 1, n, val * 10 + j);
            d[j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    for (int n = 1; n <= 10; n++) {
        dq(0, n);
    }
    sort(num.begin(), num.end());
    int t; cin >> t;
    while (t--) {
        long long l, r; cin >> l >> r;
        int idx1 = upper_bound(num.begin(), num.end(), r) - num.begin();
        int idx2 = lower_bound(num.begin(), num.end(), l) - num.begin();
        cout << idx1 - idx2 << "\n";
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}