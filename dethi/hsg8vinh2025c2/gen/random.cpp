#include <iostream>
#include <vector>
#include <string>
#include "random.h"
#include "../params.h"
using namespace std;

char COLORS[] = {'D', 'V', 'X'};
const int S_MAX = 10000;
const int Q_MAX = 10000;
int cnt[3];

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, S_MAX);
    int m = n / 3;
    cnt[0] = max(0, m - gen.uniform<int>(0, 10));
    cnt[1] = max(0, m - gen.uniform<int>(0, 10));
    cnt[2] = n - cnt[0] - cnt[1];
    string s(n, ' ');
    for (int i = 0; i < cnt[0]; i++) s[i] = COLORS[0];
    for (int i = cnt[0]; i < cnt[0] + cnt[1]; i++) s[i] = COLORS[1];
    for (int i = cnt[0] + cnt[1]; i < n; i++) s[i] = COLORS[2];
    gen.shuffle(s.begin(), s.end());
    cout << s << endl;

    int q = gen.uniform<int>(1000, Q_MAX);
    cout << q << endl;
    for (int i = 0; i < q; i++) {
        string t = "";
        bool ok = gen.uniform<int>(0, 1);
        if (ok) {
            int n = max({cnt[0], cnt[1], cnt[2]}) + gen.uniform<int>(1, 10);
            for (int i = cnt[0]; i < n; i++) t += COLORS[0];
            for (int i = cnt[1]; i < n; i++) t += COLORS[1];
            for (int i = cnt[2]; i < n; i++) t += COLORS[2];
            gen.shuffle(t.begin(), t.end());
        } else {
            int n = gen.uniform<int>(1, 100);
            for (int j = 0; j < n; j++) {
                t += COLORS[gen.uniform<int>(0, 2)];
            }
        }
        cout << t << endl;
    }
    return 0;
}
