#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int l = gen.uniform<int>(-1e6, 1e6);
    int r = gen.uniform<int>(l, 1e6);
    int d = gen.uniform<int>(-1e6, 1e6);
    int u = gen.uniform<int>(d, 1e6);
    
    cout << l << ' ' << r << ' ' << d << ' ' << u << '\n';
    return 0;
}
