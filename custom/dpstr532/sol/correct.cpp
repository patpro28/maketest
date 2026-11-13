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
    using State = pair<int, int>;
    const int mod = 1000000007;
    vector<State> row(m + 1);
    for (int j = 0; j <= m; ++j) row[j] = State(j, 1);
    for (int i = 1; i <= n; ++i) {
        State diagonal = row[0];
        row[0] = State(i, 1);
        for (int j = 1; j <= m; ++j) {
            State above = row[j];
            int deletion = above.first + 1;
            int insertion = row[j - 1].first + 1;
            int pairing = diagonal.first + (a[i - 1] != b[j - 1]);
            int best = min({deletion, insertion, pairing});
            long long count = 0;
            if (deletion == best) count += above.second;
            if (insertion == best) count += row[j - 1].second;
            if (pairing == best) count += diagonal.second;
            row[j] = State(best, int(count % mod));
            diagonal = above;
        }
    }
    cout << row[m].first << ' ' << row[m].second << '\n';
}
