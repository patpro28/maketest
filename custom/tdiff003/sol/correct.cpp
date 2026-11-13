#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    long long first_value;
    cin >> first_value;
    vector<int> starts{1};
    for (int i = 2; i <= n; ++i) {
        long long difference;
        cin >> difference;
        if (difference != 0) starts.push_back(i);
    }
    starts.push_back(n + 1);
    cout << starts.size() - 1 << '\n';
    for (size_t i = 1; i < starts.size(); ++i) {
        cout << starts[i - 1] << ' ' << starts[i] - 1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
