#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int cur = 1;
        ans = max(ans, 1);

        for (int j = 1; j < (int)s.size(); j++) {
            if (s[j] == s[j - 1])
                cur++;
            else
                cur = 1;

            ans = max(ans, cur);
        }
    }

    cout << ans;
    return 0;
}