#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int h = 500;
    int w = 500;
    cout << h << " " << w << "\n";
    int a[h + 1][w + 1];
    for (int i = 1; i <= h; i++) {
        auto p = gen.perm<int>(w / 2);
        for (int j = 1; j <= w / 2; j++) {
            a[i][j] = p[j] + 1;
        }
        p = gen.perm<int>(w / 2);
        for (int j = 1; j <= w / 2; j++) {
            a[i][j + w / 2] = p[j] + 1;
        }
    }

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (a[i][j] == a[i - 1][j] || a[i][j] == a[i][j - 1]) {
                a[i][j] = max(a[i - 1][j], a[i][j - 1]) + 1;
            }
            cout << a[i][j] << ' ';
        }
        cout << "\n";
    }

    return 0;
}
