#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];

    int position;
    long long target;
    cin >> position >> target;
    long long current = 0;
    for (int i = 1; i <= position; ++i) current += d[i];
    long long delta = target - current;
    d[position] += delta;
    if (position < n) d[position + 1] -= delta;

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
