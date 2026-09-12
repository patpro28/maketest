#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    cout << gen.lower_string(gen.uniform<int>(10000, 1e6), 'A', 'C') << '\n';
    return 0;
}
