#include <iostream>

using namespace std;

void solve() {
    int n;
    cin >> n;
    long long value = 0;
    for (int i = 1; i <= n; ++i) {
        long long difference;
        cin >> difference;
        value += difference;
        cout << value << (i == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
