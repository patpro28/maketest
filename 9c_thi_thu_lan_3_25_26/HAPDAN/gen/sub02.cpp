#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long MAX_L = 1e4;
const long long MAX_R = 1e18;
const long long MAX_R1 = 1e10;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1000, 200000);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        long long l = gen.uniform(0LL, MAX_L);
        bool ok = gen.uniform_bool();
        long long r = gen.uniform(l, MAX_R);
        if (ok) r = gen.uniform(l, MAX_R1);
        cout << l << " " << r << "\n";
    }
    return 0;
}
