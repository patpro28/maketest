#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100000);
    cout << t << '\n';
    while (t--) {
        int ans = gen.uniform(0, 1);
        if (ans == 0) {
            int k = gen.uniform(1, 29);
            cout << (1 << k) << '\n';
        } else {
            int n = gen.uniform<int>(1, 1e9);
            cout << n << '\n';
        }
    }
    return 0;
}
