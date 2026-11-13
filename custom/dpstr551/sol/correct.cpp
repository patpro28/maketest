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
    int n, m, k;
    string a, b;
    cin >> n >> m >> k >> a >> b;
    if (abs(n - m) > k) {
        cout << "-1\n";
        return 0;
    }
    const int inf = k + 1;
    vector<int> previous(m + 2, inf), current(m + 2, inf);
    for (int j = 0; j <= min(m, k); ++j) previous[j] = j;
    for (int i = 1; i <= n; ++i) {
        int left = max(0, i - k), right = min(m, i + k);
        if (left == 0) current[0] = i;
        else current[left - 1] = inf;
        current[right + 1] = inf;
        for (int j = max(1, left); j <= right; ++j)
            current[j] = min({inf, previous[j] + 1, current[j - 1] + 1,
                             previous[j - 1] + (a[i - 1] != b[j - 1])});
        previous.swap(current);
    }
    cout << (previous[m] <= k ? previous[m] : -1) << '\n';
}
