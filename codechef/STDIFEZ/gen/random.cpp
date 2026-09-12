#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 10);
    cout << t << endl;
    auto N = gen.gen_sum<int>(300, t);
    for (int i = 0; i < t; i++) {
        cout << N[i] << endl;
        for (int j = 0; j < N[i]; j++) {
            cout << gen.uniform(1, 2) << (j == N[i] - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
