#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    
    int t = gen.uniform(500, 1000);
    cout << t << "\n";
    for (int i = 0; i < t; ++i) {
        int l = gen.uniform(1, 10000);
        int r = gen.uniform(l, 2000000);
        cout << l << " " << r << "\n";
    }
    return 0;
}
