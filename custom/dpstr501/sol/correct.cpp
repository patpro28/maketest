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
    int n, m;
    string a, b;
    cin >> n >> m >> a >> b;
    if (m > n) {
        cout << "-1\n";
        return 0;
    }
    vector<int> distance(m + 1, n + 1);
    distance[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int diagonal = distance[0]++;
        for (int j = 1; j <= min(i, m); ++j) {
            int above = distance[j];
            distance[j] = min(above + 1, diagonal + (a[i - 1] != b[j - 1]));
            diagonal = above;
        }
    }
    cout << distance[m] << '\n';
}
