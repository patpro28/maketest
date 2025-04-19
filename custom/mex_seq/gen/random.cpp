#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1000;
    auto N = gen.gen_sum(2000000, t, 1, 1000000);
    auto M = gen.gen_sum(2000000, t, 0, 1000000);
    cout << t << '\n';
    for (int i = 0; i < t; i++) {
        cout << N[i] << ' ' << M[i] << '\n';
    }
    return 0;
}
