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
    string s;
    cin >> n >> s;
    vector<int> ways(n + 1);
    ways[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] != '0') ways[i] = ways[i - 1];
        if (i >= 2) {
            int value = 10 * (s[i - 2] - '0') + s[i - 1] - '0';
            if (10 <= value && value <= 26) {
                ways[i] += ways[i - 2];
                if (ways[i] >= 1000000007) ways[i] -= 1000000007;
            }
        }
    }
    cout << ways[n] << '\n';
}
