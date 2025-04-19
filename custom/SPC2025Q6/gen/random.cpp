#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 1000);
    cout << t << endl;
    auto N = gen.gen_sum(2000, t, 1, 2000);
    while (t--) {
        int n = N[t];
        cout << n << endl;
        for (int i = 0; i < n; ++i) {
            cout << gen.uniform(1, 1000000000) << ' ' << gen.uniform(1, 1000000000) << endl;
        }
    }
    return 0;
}
