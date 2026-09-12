#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
#define endl '\n'
using namespace std;

const long long MAX_L = 1e9;
const long long MAX_R = 1e12;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100000;
    cout << t << endl;
    while (t--) {
        long long l = gen.uniform(1LL, MAX_L);
        long long r = gen.uniform(l, MAX_R);
        cout << l << " " << r << endl;
    }
    return 0;
}
