#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<bool> present(n + 1, false);
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        if (a <= n) present[a] = true;
    }
    int have = 0, answer = 0;
    for (int k = 1; k <= n; ++k) {
        have += present[k];
        if (2 * (k - have) <= n - have) answer = k;
        else break;
    }
    cout << answer << '\n';
}
