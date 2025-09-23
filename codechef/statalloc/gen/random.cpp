#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 10000);
    auto N = gen.gen_sum(200000, t, 2);
    auto Q = gen.gen_sum(200000, t, 2);
    cout << t << endl;
    while (t--) {
        cout << N[t] << endl;
        long long sum = 0;
        for (int i = 0; i < N[t]; ++i) {
            int x = gen.uniform(1, 10000);
            sum += x;
            cout << x << " ";
        }
        cout << endl;
        cout << Q[t] << endl;
        for (int i = 0; i < Q[t]; ++i) {
            cout << gen.uniform(1, 100000) << ' ' << gen.uniform(1ll, min(sum, 1000000000ll)) << endl;
        }
    }
    return 0;
}
