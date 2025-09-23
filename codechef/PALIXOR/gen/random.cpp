#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(2, 100);
    auto N = gen.gen_sum(200000, t, 1, 100000);
    cout << t << '\n';
    while (t--) {
        cout << N[t] << '\n';
        for (int i = 0; i < N[t]; ++i) {
            cout << gen.uniform(1, 1 << 15) - 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}
