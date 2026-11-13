#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, divisor;
    string s;
    cin >> n >> k >> divisor >> s;
    const int mod = 1000000007;
    vector<int> residue(n + 1), previous(n + 1), current(n + 1), totals(divisor);
    for (int i = 1; i <= n; ++i) residue[i] = (residue[i - 1] + s[i - 1] - '0') % divisor;
    previous[0] = 1;
    for (int parts = 1; parts <= k; ++parts) {
        fill(totals.begin(), totals.end(), 0);
        current[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int &total = totals[residue[i - 1]];
            total += previous[i - 1];
            if (total >= mod) total -= mod;
            current[i] = totals[residue[i]];
        }
        previous.swap(current);
    }
    cout << previous[n] << '\n';
}
