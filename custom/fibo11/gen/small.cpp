#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 1000000);
    int k = gen.uniform(1, 1000000);
    cout << n << " " << k << endl;
    return 0;
}
