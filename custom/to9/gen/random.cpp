#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 50000);
    n = n * 2;
    cout << n << '\n';
    vector<int> a(n);
    for (int i = 0; i + i < n; ++i) {
        a[i] = gen.uniform<int>(1, 1e5);
        a[i + i + 1] = a[i] + gen.uniform<int>(1, 1e5);
    }
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }
    return 0;
}
