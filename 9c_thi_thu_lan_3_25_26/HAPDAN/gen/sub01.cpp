#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long MAX_L = 100;
const long long MAX_R = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        long long l = gen.uniform(0LL, MAX_L);
        long long r = gen.uniform(l, MAX_R);
        cout << l << " " << r << "\n";
    }
    return 0;
}
