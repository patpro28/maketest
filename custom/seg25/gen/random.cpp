#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int N = 200000;
const int Q = 200000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, N);
    int q = Q;
    cout << n << " " << q << endl;
    while (q--) {
        int type = gen.uniform(1, 5);
        if (type <= 3) {
            int l = gen.uniform(1, n);
            int r = gen.uniform(1, n);
            if (l > r) swap(l, r);
            cout << type << " " << l << " " << r << " " << gen.uniform(1, N) << endl;
        } else {
            int l = gen.uniform(1, n);
            int r = gen.uniform(1, n);
            if (l > r) swap(l, r);
            cout << type << " " << l << " " << r << endl;
        }
    }
    return 0;
}
