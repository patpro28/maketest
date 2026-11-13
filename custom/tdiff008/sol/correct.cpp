#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<long long> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];

    while (q--) {
        int left, right, position;
        long long delta;
        cin >> left >> right >> delta >> position;
        long long answer = d[position];
        if (position == left) answer += delta;
        if (position == right + 1) answer -= delta;
        cout << answer << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
