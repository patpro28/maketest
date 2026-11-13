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
    long long opening, extension, replacement;
    cin >> n >> m >> a >> b >> opening >> extension >> replacement;
    using Cost = array<long long, 3>;
    const long long inf = 1LL << 60;
    const long long start = opening + extension;
    vector<Cost> previous(m + 1), current(m + 1);
    previous[0] = Cost{{0, inf, inf}};
    for (int j = 1; j <= m; ++j) previous[j] = Cost{{inf, opening + j * extension, inf}};
    for (int i = 1; i <= n; ++i) {
        current[0] = Cost{{inf, inf, opening + i * extension}};
        for (int j = 1; j <= m; ++j) {
            const Cost &diagonal = previous[j - 1], &left = current[j - 1], &above = previous[j];
            current[j][0] = min({diagonal[0], diagonal[1], diagonal[2]})
                           + (a[i - 1] == b[j - 1] ? 0 : replacement);
            current[j][1] = min({left[0] + start, left[1] + extension, left[2] + start});
            current[j][2] = min({above[0] + start, above[1] + start, above[2] + extension});
        }
        previous.swap(current);
    }
    cout << *min_element(previous[m].begin(), previous[m].end()) << '\n';
}
