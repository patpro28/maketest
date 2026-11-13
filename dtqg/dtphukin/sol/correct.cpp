#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        int previousOne = 0, latestPairStart = 0;
        long long answer = 0;
        for (int right = 1; right <= n; ++right) {
            int value;
            cin >> value;
            if (value == 1) {
                if (previousOne > 0 && right - previousOne <= 2) {
                    latestPairStart = previousOne;
                }
                previousOne = right;
            }
            answer += latestPairStart + value;
        }
        cout << answer << '\n';
    }
}
