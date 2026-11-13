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
    int n, low, high;
    string s;
    cin >> n >> low >> high >> s;
    vector<int> best(n + 1, n + 1);
    best[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (best[i] > n) continue;
        unsigned seen = 0;
        for (int j = i; j < n && j < i + high; ++j) {
            unsigned bit = 1u << (s[j] - 'a');
            if (seen & bit) break;
            seen |= bit;
            if (j - i + 1 >= low) best[j + 1] = min(best[j + 1], best[i] + 1);
        }
    }
    cout << (best[n] <= n ? best[n] : -1) << '\n';
}
