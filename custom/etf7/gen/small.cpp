#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 2000;
    cout << t << endl;
    for (int i = 0; i < t; i++) {
        int l = gen.uniform(2, 2000);
        int r = gen.uniform(l, 2000);
        cout << l << " " << r << endl;
    }
    return 0;
}
