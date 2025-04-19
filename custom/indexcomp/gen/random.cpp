#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100;
    auto N = gen.gen_sum(5000, t, 1);
    cout << t << endl;
    for (int i = 0; i < t; i++) {
        cout << N[i] << ' ';
        cout << gen.uniform(1, 1000000000) << ' ' << gen.uniform(1, 1000000000) << endl;
    }
    return 0;
}
