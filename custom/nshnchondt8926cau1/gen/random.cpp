#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(100000, 200000);
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << gen.uniform<long long>(-1e18, 1e18) << ' ';
    }
    return 0;
}
