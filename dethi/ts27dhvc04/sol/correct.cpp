#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n = 0) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, long long val) {
        while (idx <= n) {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    long long query(int idx) {
        long long res = 0;
        while (idx > 0) {
            res = max(res, bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> p(n + 1), w(n + 1);

    vector<long long> vals;

    for (int i = 1; i <= n; i++) {
        cin >> p[i] >> w[i];
        vals.push_back(p[i]);
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    Fenwick bit(vals.size());

    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(vals.begin(), vals.end(), p[i]) - vals.begin() + 1;

        long long best = bit.query(pos - 1);

        long long dp = best + w[i];

        bit.update(pos, dp);

        ans = max(ans, dp);
    }

    cout << ans;
    return 0;
}