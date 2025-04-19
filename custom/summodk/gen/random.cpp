#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100;
    cout << t << '\n';
    
    while (t--) {
        int n = gen.uniform<int>(1, 1000000000);
        int m = gen.uniform<int>(1, 1000000000);
        int k = gen.uniform(0, m - 1);
        cout << n << ' ' << k << ' ' << m << '\n';
    }
    return 0;
}
