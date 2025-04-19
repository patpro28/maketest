#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 10);
    auto N = gen.gen_sum(100000, t, 2);

    cout << t << endl;
    while (t--) {
        int n = N[t];
        cout << n << endl;
        for (int i = 0; i < n; i++) {
            cout << gen.uniform(1, 2) << " \n"[i == n - 1];
        }
        for (int i = 1; i < n; ++i)
            cout << gen.uniform(1, i) << " \n"[i == n - 1];
    }

    return 0;
}
