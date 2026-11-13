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
    const State impossible(n + m + 1, m + 1);
    vector<State> row(m + 1, impossible);
    for (int j = 1; j <= m; ++j) row[j] = State(1, j);
    for (int i = 1; i <= n; ++i) {
        State diagonal = row[0];
        for (int j = 1; j <= m; ++j) {
            State above = row[j];
            int mismatch = a[i - 1] != b[j - 1];
            row[j] = min({State(above.first + 1, above.second),
                          State(row[j - 1].first + 1, row[j - 1].second),
                          State(diagonal.first + mismatch, diagonal.second),
                          State(i - 1 + mismatch, j)});
            diagonal = above;
        }
    }
    tuple<int, int, int> answer(n + m + 1, m + 1, m + 1);
    for (int j = 1; j <= m; ++j)
        answer = min(answer, make_tuple(row[j].first, row[j].second, j));
    cout << get<0>(answer) << ' ' << get<1>(answer) << ' ' << get<2>(answer) << '\n';
}
