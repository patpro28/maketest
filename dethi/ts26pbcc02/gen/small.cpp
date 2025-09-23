#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int k = gen.uniform<int>(1, 300);
    for (int i = 0; i < k; ++i)
        cout << gen.uniform<int>(0, 9);
    return 0;
}
