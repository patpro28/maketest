#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];

    int left;
    long long delta;
    cin >> left >> delta;
    d[left] += delta;

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
