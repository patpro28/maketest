#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 5);
    cout << t << endl;
    auto N = gen.gen_sum(200000, t, 3);
    auto Q = gen.gen_sum(200000, t, 1);
    for (int i = 0; i < t; ++i) {
        cout << N[i] << " " << Q[i] << endl;
        int a;
        for (int j = 0; j < N[i]; ++j) {
            a = gen.uniform(1ll, A_AND_B_MAX);
            cout << a  << " \n"[j + 1 == N[i]];
        }
        for (int j = 0; j < Q[i]; ++j) {
            int l = gen.uniform(1, N[i] - 1);
            int r = gen.uniform(l + 1, N[i]);
            cout << l << " " << r << endl;
        }
    }
    return 0;
}
