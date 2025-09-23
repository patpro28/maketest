#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100000;
    int k = gen.uniform<int>(1, 99);
    cout << t << ' ' << k << '\n';
    while (t--) {
        int a = gen.uniform<int>(100, 1000);
        int b = gen.uniform<int>(a + 10000, 1000000);
        cout << a << ' ' << b << '\n';
    }
    return 0;
}
