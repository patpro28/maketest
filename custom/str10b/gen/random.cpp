#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 99);
    cout << gen.uniform(1, 9);
    cout << gen.lower_string(n, '0', '0' + gen.uniform(1, 9)) << endl;
    return 0;
}
