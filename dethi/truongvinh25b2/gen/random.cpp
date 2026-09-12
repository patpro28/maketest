#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int a = gen.uniform(1, 1000);
    int b = gen.uniform(1, 1000);
    int c = gen.uniform(1, 1000);
    int d = gen.uniform(1, 1000);
    cout << a << ' ' << b << "\n";
    cout << c << ' ' << d << "\n";
    return 0;
}
