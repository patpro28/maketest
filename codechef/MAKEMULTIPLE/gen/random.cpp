#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(2, 100000);
    cout << t << endl;
    int k = gen.uniform(0, 1);
    if (k) {
        int b = gen.uniform<int>(1, 1e9);
        cout << b << ' ' << b << '\n';
        t--;
        cout << 100000 << ' ' << 1000000000 << '\n';
        t--;
    }
    while (t--) {
        int b = gen.uniform<int>(1, 1e9);
        int a = gen.uniform<int>(1, 2 * b / 3);
        cout << a << ' ' << b << '\n';
    }
    return 0;
}
