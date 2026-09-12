#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 200000);
    long long l = gen.uniform<long long>(1, 1e18);
    
    cout << n << " " << l << "\n";
    for (int i = 2; i <= n; i++) {
        int p = gen.uniform<int>(1, i - 1);
        long long dist = gen.uniform<long long>(1, 1e12);
        cout << p << " " << dist << "\n";
    }

    return 0;
}
