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
    long long replaceCost;
    cin >> replaceCost;
    vector<long long> deletion(n + 1), insertion(m + 1);
    for (int i = 1; i <= n; ++i) cin >> deletion[i];
    for (int j = 1; j <= m; ++j) cin >> insertion[j];
    vector<long long> distance(m + 1);
    for (int j = 1; j <= m; ++j) distance[j] = distance[j - 1] + insertion[j];
    for (int i = 1; i <= n; ++i) {
        long long diagonal = distance[0];
        distance[0] += deletion[i];
        for (int j = 1; j <= m; ++j) {
            long long above = distance[j];
            distance[j] = min({above + deletion[i], distance[j - 1] + insertion[j],
                               diagonal + (a[i - 1] == b[j - 1] ? 0 : replaceCost)});
            diagonal = above;
        }
    }
    cout << distance[m] << '\n';
}
