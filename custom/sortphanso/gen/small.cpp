#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX_N = 10;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, MAX_N);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int tu = gen.uniform(1, 10);
        int mau = gen.uniform(1, 10);
        cout << tu << " " << mau << "\n";
    }
    return 0;
}
