#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int HMAX = 1000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100000);
    auto N = gen.gen_sum(1000000, t, 1);
    
    cout << t << endl;
    for (int i = 0; i < t; i++) {
        cout << N[i] << ' ' << gen.uniform(1, N[i]) << endl;
        for (int j = 0; j < N[i]; ++j)
            cout << gen.uniform(1, HMAX) << " \n"[j == N[i] - 1];
    }
    return 0;
}
