#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 20);
    int q = 200000;
    auto l = gen.gen_sum(200000, n);
    cout << n << ' ' << q << endl;
    for (int i = 0; i < n; ++i) {
        cout << l[i] << ' ';
        for (int j = 0; j < l[i]; ++j)
            cout << gen.uniform(1, 1000000000) << ' ';
        cout << endl;
    }
    while (q--) {
        int x = gen.uniform(1, n);
        cout << x << ' ' << gen.uniform(1, l[x - 1]) << endl;
    }
    return 0;
}
