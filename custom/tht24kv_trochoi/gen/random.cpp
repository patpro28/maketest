#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    cout << gen.uniform<int>(2, 1e8) << endl;
    cout << gen.uniform<int>(0, 15) << endl;
    return 0;
}
