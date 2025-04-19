#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    auto N = gen.gen_sum(100, t, 1);
    cout << t << endl;
    for (int i = 0; i < t; i++) {
        cout << N[i] << ' ';
        cout << gen.uniform(1, 100) << ' ' << gen.uniform(1, 100) << endl;
    }
    return 0;
}
