#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int N = 100000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, N);
    vector<int> a = gen.gen_sum<int>(1000000, n, 1);
    int m = gen.uniform(1, N);
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
    cout << m << endl;
    while (m--) {
        cout << gen.uniform(1000000, 1000000) << endl;
    }
    return 0;
}
