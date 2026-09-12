#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int h = gen.uniform(499, 499);
    int w = 499;
    cout << h << " " << w << "\n";

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cout << ((i - 1) * w + j) % 2 + 1 << ' ';
        }
        cout << "\n";
    }

    return 0;
}
