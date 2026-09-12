#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int h = gen.uniform(1, 10);
    int w = gen.uniform(1, 10);
    cout << h << " " << w << "\n";
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (j > 0) cout << " ";
            cout << gen.uniform<int>(1, 100);
        }
        cout << "\n";
    }

    return 0;
}
