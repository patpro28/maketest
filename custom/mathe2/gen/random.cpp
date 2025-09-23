#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100000);
    while (t--) {
        cout << gen.uniform<int>(1, 1e9) << '\n';
    }
    return 0;
}
