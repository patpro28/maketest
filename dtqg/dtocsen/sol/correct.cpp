#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long target;
    int n;
    cin >> target >> n;
    vector<long long> moves(n);
    for (auto& move : moves) cin >> move;

    long long height = 0, sum = 0, maxPrefix = 0;
    for (int i = 0; i < n; ++i) {
        sum += moves[i];
        maxPrefix = max(maxPrefix, sum);
        height = max(0LL, height + moves[i]);
        if (height >= target) {
            cout << 0 << ' ' << i << '\n';
            return 0;
        }
    }

    // After day 0, the starting height grows by max(0, sum) per day.
    long long day = 1;
    long long gap = target - maxPrefix - height;
    if (gap > 0) {
        if (sum <= 0) {
            cout << "-1 -1\n";
            return 0;
        }
        long long skip = (gap + sum - 1) / sum;
        day += skip;
        height += skip * sum;
    }
    for (int i = 0; i < n; ++i) {
        height = max(0LL, height + moves[i]);
        if (height >= target) {
            cout << day << ' ' << i << '\n';
            return 0;
        }
    }
}
