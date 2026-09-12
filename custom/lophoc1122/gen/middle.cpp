#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int p[] = {8, 64, 81};
const int MAX_N = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 1, x = 0;
    while (n * p[x] <= MAX_N) {
        n *= p[x];
        x = gen.uniform<int>(0, 1);
    }
    cout << n << endl;
    
    return 0;
}
