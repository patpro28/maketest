#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 200;
    cout << t << endl;
    while (t--) {
        int n = gen.uniform(1, 1000);
        cout << n << endl;
    }
    return 0;
}
