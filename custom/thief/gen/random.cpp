#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100;
    int w = gen.uniform<int>(1000000, 1000000000);
    int h = gen.uniform<int>(1000000, 1000000000);
    cout << n << " " << w << " " << h << endl;
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform<int>(1, 100000000) << " " << gen.uniform<int>(1, 1000) << endl;
    }
    return 0;
}
