#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100000);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int x = gen.uniform(1, 10000);
        cout << x << ' ';
    }
    cout << '\n';
    return 0;
}
