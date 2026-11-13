#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int bestInterval(const vector<int>& sums, int first, int last) {
    int best = sums[first], ending = 0;
    for (int i = first; i < last; ++i) {
        ending = max(ending, 0) + sums[i];
        best = max(best, ending);
    }
    return best;
}

int main() {
    if (FILE* input = fopen("ORCHARD.INP", "r")) {
        fclose(input);
        freopen("ORCHARD.INP", "r", stdin);
        freopen("ORCHARD.OUT", "w", stdout);
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> garden(min(n, m), vector<int>(max(n, m)));
    int bananas = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char cell;
            cin >> cell;
            int value = cell - '0';
            bananas += value;
            if (n <= m) garden[i][j] = 2 * value - 1;
            else garden[j][i] = 2 * value - 1;
        }
    }
    if (n > m) swap(n, m);

    vector<int> sums(m);
    int best = 1;
    for (int top = 0; top < n; ++top) {
        fill(sums.begin(), sums.end(), 0);
        for (int bottom = top; bottom < n; ++bottom) {
            bool fullHeight = top == 0 && bottom == n - 1;
            int ending = 0;
            // When using every row, exclude the last column in this pass.
            int limit = m - fullHeight;
            for (int j = 0; j < limit; ++j) {
                sums[j] += garden[bottom][j];
                ending = max(ending, 0) + sums[j];
                best = max(best, ending);
            }
            if (fullHeight) {
                sums[m - 1] += garden[bottom][m - 1];
                best = max(best, bestInterval(sums, 1, m));
            }
        }
    }
    cout << bananas - best << '\n';
}
