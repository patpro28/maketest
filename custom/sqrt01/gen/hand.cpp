#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int h = gen.uniform(10, 10);
    int w = 10;
    cout << h << " " << w << "\n";

    int a[h + 1][w + 1];

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            a[i][j] = ((i - 1) * w + j - 1);
        }
        // cout << "\n";
    }

    a[1][1] = 200;
    a[h][w] = 200;
    a[4][4] = a[6][5] = 200;
    a[7][1] = a[1][7] = 200;
    a[10][4] = 200;
    a[4][10] = 200;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cout << a[i][j] << ' ';
        }
        cout << "\n";
    }

    return 0;
}
