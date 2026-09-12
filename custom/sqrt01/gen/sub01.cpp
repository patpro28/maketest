#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int h = gen.uniform(300, 500);
    int w = gen.uniform(300, 500);
    cout << h << " " << w << "\n";
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (j > 0) cout << " ";
            cout << gen.uniform<int>(1, 1e6);
        }
        cout << "\n";
    }

    return 0;
}
