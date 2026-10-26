#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const long long INF = 1LL << 60, NEG = -INF;
    (void) INF; (void) NEG;
    int n; string s;
    cin >> n >> s;
    int best[2] = {0, 0};
    for (char c : s) { int t = c - 'a'; best[t] = max(best[t], best[1-t] + 1); }
    cout << n - max(best[0], best[1]) << '\n';
}
