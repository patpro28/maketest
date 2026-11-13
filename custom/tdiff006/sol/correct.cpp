#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];

    int left, right;
    long long delta;
    cin >> left >> right >> delta;
    d[left] += delta;
    if (right < n) d[right + 1] -= delta;

    for (int i = 1; i <= n; ++i) {
        cout << d[i] << (i == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
