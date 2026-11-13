#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int first = 0, second = 0, changes = 0;
    long long delta = 0, second_change = 0, previous = 0;
    for (int i = 1; i <= n + 1; ++i) {
        long long current = 0;
        if (i <= n) {
            long long b;
            cin >> b;
            current = b - a[i];
        }
        long long change = current - previous;
        if (change != 0) {
            ++changes;
            if (changes == 1) {
                first = i;
                delta = change;
            } else if (changes == 2) {
                second = i;
                second_change = change;
            }
        }
        previous = current;
    }

    if (changes == 2 && delta == -second_change) {
        cout << first << ' ' << second - 1 << ' ' << delta << '\n';
    } else {
        cout << -1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
