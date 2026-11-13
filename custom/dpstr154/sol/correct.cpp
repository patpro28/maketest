#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; string a, b;
    cin >> n >> m >> a >> b;
    const int inf = m + 1;
    vector<array<int, 26> > next(m + 1);
    next[m].fill(inf);
    for (int p = m - 1; p >= 0; --p) {
        next[p] = next[p + 1];
        next[p][b[p] - 'a'] = p + 1;
    }
    int bound = min(n, m);
    vector<int> f(bound + 1, inf);
    f[0] = 0;
    for (int i = 0; i < n; ++i) {
        int c = a[i] - 'a';
        for (int length = min(i + 1, bound); length >= 1; --length) {
            if (f[length - 1] <= m)
                f[length] = min(f[length], next[f[length - 1]][c]);
        }
    }
    int answer = bound;
    while (f[answer] > m) --answer;
    cout << answer << '\n';
}
