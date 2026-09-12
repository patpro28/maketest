#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
#define endl '\n'
using namespace std;

const long long MAX_L = 1e3;
const long long MAX_R = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100);
    cout << t << endl;
    while (t--) {
        long long l = gen.uniform(1LL, MAX_L);
        long long r = gen.uniform(l, MAX_R);
        cout << l << " " << r << endl;
    }
    return 0;
}
