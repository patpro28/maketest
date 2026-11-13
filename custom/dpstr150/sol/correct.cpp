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
    char c; cin >> c;
    const int NEG = -1000000;
    vector<int> unrestricted(m + 1, 0), required(m + 1, NEG);
    for (int i = 0; i < n; ++i) {
        int old_any = 0, old_required = NEG;
        for (int j = 1; j <= m; ++j) {
            int next_any = unrestricted[j], next_required = required[j];
            unrestricted[j] = max(unrestricted[j], unrestricted[j-1]);
            required[j] = max(required[j], required[j-1]);
            if (a[i] == b[j-1]) {
                unrestricted[j] = max(unrestricted[j], old_any + 1);
                if (a[i] == c) required[j] = max(required[j], old_any + 1);
                else if (old_required != NEG) required[j] = max(required[j], old_required + 1);
            }
            old_any = next_any; old_required = next_required;
        }
    }
    cout << (required[m] == NEG ? -1 : required[m]) << '\n';
}
