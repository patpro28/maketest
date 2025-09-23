#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAXT = 10;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, MAXT);
    auto N = gen.gen_sum(2000, t);
    cout << t << "\n";
    while (t--) {
        int n = N[t];
        for (int i = 0; i < n; i++) {
            cout << gen.uniform(0, 1);
        }
        cout << "\n";
    }
    return 0;
}
