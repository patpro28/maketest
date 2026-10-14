#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;
        int l = 1, r = s, ans = s;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            long long sum = 0;
            int cnt = 0;
            for (int i = 30; i >= 0; --i) {
                if ((mid >> i) & 1) {
                    sum += 1LL * (n - 1) * (1LL << i);
                    cnt = min(cnt + 1, n - 1);
                } else {
                    sum += 1LL * cnt * (1LL << i);
                }
            }
            if (sum >= s) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << '\n';
    }
}
