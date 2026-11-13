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
    vector<char> possible(n + 1);
    possible[0] = true;
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] == 'a') possible[i] = possible[i - 1];
        if (i >= 2 && (s[i - 2] != 'a' || s[i - 1] != 'a'))
            possible[i] = possible[i] || possible[i - 2];
    }
    cout << int(possible[n]) << '\n';
}
