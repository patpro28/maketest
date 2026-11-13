#include <iostream>

using namespace std;

void solve() {
    int n;
    cin >> n;
    long long previous = 0;
    for (int i = 1; i <= n; ++i) {
        long long value;
        cin >> value;
        cout << value - previous << (i == n ? '\n' : ' ');
        previous = value;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
