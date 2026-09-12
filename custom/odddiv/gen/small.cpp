#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    cout << t << '\n';
    for (int i = 0; i < t; ++i) {
        int l = gen.uniform<int>(1, 1e5);
        int r = gen.uniform<int>(l, 1e5);
        cout << l << ' ' << r << '\n';
    }
    return 0;
}
