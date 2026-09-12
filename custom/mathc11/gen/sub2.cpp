#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(10000, 100000);
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        int x = gen.uniform<int>(1, 1000);
        cout << x * x << " ";
    }
    return 0;
}
