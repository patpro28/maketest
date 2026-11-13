#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    int k;
    long long anchor;
    cin >> k >> anchor;

    vector<long long> differences(n + 1), values(n + 1);
    for (int i = 2; i <= n; ++i) cin >> differences[i];

    values[k] = anchor;
    for (int i = k; i >= 2; --i) values[i - 1] = values[i] - differences[i];
    for (int i = k + 1; i <= n; ++i) values[i] = values[i - 1] + differences[i];

    for (int i = 1; i <= n; ++i) {
        cout << values[i] << (i == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
