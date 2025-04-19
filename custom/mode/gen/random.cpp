#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, N_MAX);
    int q = gen.uniform<int>(1, Q_MAX);
    cout << n << " " << q << endl;
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform<int>(1, n) << " \n"[i == n - 1];
    }
    for (int i = 0; i < q; ++i) {
        cout << gen.uniform<int>(1, n) << " " << gen.uniform<int>(1, n) << endl;
    }
    return 0;
}
