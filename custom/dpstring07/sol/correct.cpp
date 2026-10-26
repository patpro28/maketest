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
    vector<long long> w(n); for (auto &v : w) cin >> v;
    long long even = 0, pending[2] = {NEG, NEG};
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a'; long long old = even;
        if (pending[1-c] != NEG) even = max(even, pending[1-c] + w[i]);
        pending[c] = max(pending[c], old + w[i]);
    }
    cout << even << '\n';
}
