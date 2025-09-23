#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int h = gen.uniform<int>(2, 1e9);
    int w = gen.uniform<int>(2, 1e9);
    int k = gen.uniform<int>(1, 1e6);
    
    cout << h << " " << w << " " << k << endl;
    int x1 = gen.uniform<int>(1, h);
    int y1 = gen.uniform<int>(1, w);
    int x2 = gen.uniform<int>(1, h);
    int y2 = gen.uniform<int>(1, w);
    cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    return 0;
}
