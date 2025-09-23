#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1 << 4;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    auto N = gen.gen_sum(100, t, 1);
    cout << t << endl;
    while (t--) {
        cout << N[t] << ' ';
        cout << gen.uniform(1, 100) << '\n';
        for (int i = 0; i < N[t]; ++i) {
            cout << gen.uniform(0, 1);
        }
        cout << '\n';
    }
    return 0;
}
