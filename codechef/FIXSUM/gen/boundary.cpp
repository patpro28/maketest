#include <iostream>
#include <vector>
#include <utility>
using namespace std;
int main() {
    vector<pair<int, int>> cases;
    for (int n : {2, 3, 4, 5, 10, 29, 30, 31, 32, 100, 999999999, 1000000000}) {
        for (int s : {1, 2, 3, 999999999, 1000000000}) cases.emplace_back(n, s);
        for (int k = 1; k < 30; ++k)
            for (int d = -1; d <= 1; ++d) cases.emplace_back(n, (1 << k) + d);
    }
    for (int n : {2, 3, 5, 10, 100, 10000})
        for (int k = 0; k < 30; ++k)
            for (int d = -2; d <= 2; ++d) {
                long long s = 1LL * (n - 1) * (1 << k) + d;
                if (1 <= s && s <= 1000000000) cases.emplace_back(n, s);
            }
    cout << cases.size() << '\n';
    for (auto [n, s] : cases) cout << n << ' ' << s << '\n';
}
