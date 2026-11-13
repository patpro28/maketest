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
    int n;
    string a, b;
    cin >> n >> a >> b;
    vector<int> best(n + 1);
    for (int i = 1; i <= n; ++i) {
        best[i] = best[i - 1] + (a[i - 1] != b[i - 1]);
        if (i >= 2 && a[i - 2] == b[i - 1] && a[i - 1] == b[i - 2])
            best[i] = min(best[i], best[i - 2] + 1);
    }
    cout << best[n] << '\n';
}
